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

#ifndef DECODER_HPP
#define DECODER_HPP

#include "loader.hpp"

extern "C"{
    #include <libavcodec/avcodec.h>
}

class packetStream;

class decoder
{
public:
    decoder(packetStream* stream);

    // error reporting
    // return true if error else false
    bool err() { return avErr; }

    // return error string with null termination
    const char* getErrStr() { return errStr; }

    void decode(int count=1);

    AVFrame* getFrame();
    void dumpFrame(AVFrame* frm);
    
    void clear();
    void setSource(packetStream* src);

    ~decoder();
private:

    AVFrame* getEmptyFrame();
private:
    AVCodecContext* Ctx=0;
    packetStream* source=0;
    std::queue<AVFrame*> frames, dump;
    int avErr=0;
    char errStr[100];

};


#endif //DECODER_HPP
