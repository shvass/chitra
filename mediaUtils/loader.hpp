// This file is a part of  chitra (चित्र)
// Copyright (C) 2022  akshay bansod <aksh.bansod@yahoo.com>

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

#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <queue>
#include <vector>
#include <list>

#include "decoder.hpp"
#include "texture.hpp"

extern "C"{
    #include <libavformat/avformat.h>
}

class packetStream;
class loader{
public:

    loader(){};
    loader(std::string& path) : loader(path.c_str()) {};
    loader(const char* path);


    // returns audio/video stream 
    //         null if no stream found
    packetStream* getDefaultVideoStream();
    packetStream* getDefaultAudioStream();

    packetStream& getStream(unsigned int index=0) {return streams[index];};


    // error reporting
    // return true if error else false
    bool err() { return avErr; }
    // return error string with null termination
    const char* getErrStr() { return errBuffer; }


    // load 'count' no of packets of particular stream
    // other stream packets found also will be loaded
    void load(int streamIndex = -1, int count=1);

    // clear all loaded packets in all the stream
    void clear();

    // seek to a particular timeStamp 
    // 0 = beginning
    void seek(double time=0);

    ~loader();

    // return used packet for reuse
    static void returnPacket(AVPacket*);

private:
    static AVPacket* getPacket();

private:
    static std::list<AVPacket*> emptyPackets;
    std::vector<packetStream> streams;
    AVFormatContext* fmtCtx=0;
    
    // backend error code
    int avErr=0;
    char errBuffer[100];
};


class packetStream : public std::queue<AVPacket*>
{
public:
    packetStream(loader& ld, int index, AVCodecParameters* param): pktSrc(ld), index(index), codecParams(param) {};

    void pull(int count=1) {pktSrc.load(index, count); };

    int getIndex(){ return index; };
    
    AVCodecParameters* getCodecParam(){ return codecParams; };

private:
    AVCodecParameters* codecParams;
    loader& pktSrc;
    int index;
};


#endif // LOADER_HPP
