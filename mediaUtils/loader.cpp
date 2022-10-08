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

#include "loader.hpp"

// defination of static members
std::list<AVPacket*> loader::emptyPackets;


loader::loader(const char* path){

    // allocate context
    fmtCtx = avformat_alloc_context();
    AVPacket* pkt = av_packet_alloc();

    // open input file
    if(avErr = avformat_open_input(&fmtCtx, path, NULL, NULL)){
        av_strerror(avErr, errBuffer, 100);
        avformat_free_context(fmtCtx);
        fmtCtx=0;
        return;
    }

    // fillup streams buffer
    streams.reserve(fmtCtx->nb_streams);
    for(int i=0; i < fmtCtx->nb_streams; i++) streams.push_back(packetStream(*this, i, fmtCtx->streams[i]->codecpar));
};



void loader::load(int streamIndex, int count){
    AVPacket* pkt;
    while (count)
    {
        pkt = getPacket();
        if(avErr = av_read_frame(fmtCtx, pkt)){
            av_strerror(avErr, errBuffer, 100);
            streams[streamIndex].push(nullptr);
            returnPacket(pkt);
            return;
        };

        if(pkt->stream_index == streamIndex) count--;
        streams[pkt->stream_index].push(pkt);
    }
};


void loader::clear(){
    for(auto& stream : streams){

        for(int i=0; i < stream.size(); i++){
            returnPacket(stream.front());
            stream.pop();
        }
    };
};

void loader::seek(double time){
    // later
};

loader::~loader(){
    clear();
    avformat_close_input(&fmtCtx);
};


packetStream* loader::getDefaultVideoStream(){
    int index = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if(index < 0) return nullptr;
    return &streams[index];
}


packetStream* loader::getDefaultAudioStream(){
    int index = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if(index < 0) return nullptr;
    return &streams[index];
}


AVPacket* loader::getPacket(){
    if(!emptyPackets.size()) return av_packet_alloc();
    AVPacket* pkt = emptyPackets.front();
    emptyPackets.pop_front();
    return pkt;
};


void loader::returnPacket(AVPacket* pkt){
    av_packet_unref(pkt);
    emptyPackets.push_back(pkt);
};
