// This file is a part of  chitra (चित्र)
// Copyright (C) 2022  akshay bansod <akshay.bnsod@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "decoder.hpp"


void decoder::setSource(packetStream* stream){

    source = stream;
    if(Ctx) avcodec_free_context(&Ctx);
    AVCodecParameters* param = stream->getCodecParam();
    const AVCodec* codec = avcodec_find_decoder(param->codec_id);
    Ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(Ctx, param);
    
    if(avErr = avcodec_open2(Ctx, codec, NULL)){
        av_strerror(avErr, errStr, 100);
        avcodec_free_context(&Ctx);
        return;
    };
};

decoder::decoder(packetStream* stream) : source(stream){
    setSource(stream);
};


decoder::~decoder(){
    avcodec_free_context(&Ctx);
};


void decoder::decode(int count){
    AVPacket* pkt=0;
    AVFrame* frm=0;
    while(count){
        if(!source->size()) source->pull(count);
        pkt = source->front();
        source->pop();
        
        // end of stream or error
        if(!pkt) { frames.push(nullptr); return; }

        avcodec_send_packet(Ctx, pkt);
        loader::returnPacket(pkt);

        if(!frm) frm = getEmptyFrame();
        if(avErr = avcodec_receive_frame(Ctx, frm)){
            if(avErr = AVERROR(EAGAIN)) continue;
        }
        else{
            // found a frame
            frames.push(frm);
            frm = 0;
            count--;
        }
    };
};


AVFrame* decoder::getFrame(){
    if(!frames.size()) decode(1);
    AVFrame* frm = frames.front();
    frames.pop();
    return frm;
}

AVFrame* decoder::getEmptyFrame(){
    if(!dump.size()) return av_frame_alloc();
    AVFrame* frm = dump.front();
    dump.pop();
    return frm;
};

void  decoder::dumpFrame(AVFrame* frm){
    av_frame_unref(frm);
    dump.push(frm);
}
