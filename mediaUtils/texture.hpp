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


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define MAX_TEX_COUNT 4

struct AVFrame;

// video memory loaded image

class texture
{
public:

    enum textureFormat {
        RGB = 0,
        YUV420 = 1,
        UNKNOWN
    };

    texture();

    texture(AVFrame* frm) { operator=(frm); };

    AVFrame* operator=(AVFrame* frm);

    void load();

    textureFormat getFormat() { return fmt;}
    
    inline int getTexIdAt(int index = 0) { return texIds[index];}

    void bind();

    ~texture();

private:
    unsigned int texIds[MAX_TEX_COUNT], p_fmt = -1;

    unsigned char** data=0;
    unsigned int height, width;
    textureFormat fmt = textureFormat::UNKNOWN;
};


#endif // TEXTURE_HPP
