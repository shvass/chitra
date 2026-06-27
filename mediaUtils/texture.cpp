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

#include "texture.hpp"

#include <glad/glad.h>
#include <libavformat/avformat.h>
#include <exception>

AVFrame* texture::operator=(AVFrame* frm){
    width = frm->linesize[0];
    height = frm->height;

    data = frm->data;
    p_fmt = frm->format;
    load();
    return frm;
};



texture::texture()
{
    glGenTextures(MAX_TEX_COUNT, texIds);

    for(int i = 0; i < MAX_TEX_COUNT; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texIds[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};

void texture::load(){
    switch(p_fmt){

    case AV_PIX_FMT_GBR24P:
        fmt = textureFormat::RGB;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texIds[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data[2]);

        glBindTexture(GL_TEXTURE_2D, texIds[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_GREEN, GL_UNSIGNED_BYTE, data[0]);

        glBindTexture(GL_TEXTURE_2D, texIds[2]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BLUE, GL_UNSIGNED_BYTE, data[1]);
        break;

    case AV_PIX_FMT_RGB24:
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texIds[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data[0]);

        glBindTexture(GL_TEXTURE_2D, texIds[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data[0]);

        glBindTexture(GL_TEXTURE_2D, texIds[2]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data[0]);
        break;

    default:
        fmt = textureFormat::UNKNOWN;
        throw std::runtime_error("unsupported pixel format ");
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data[0]);
        return;
    }
};

void texture::bind()
{
    for(int i = 0; i < MAX_TEX_COUNT; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texIds[i]);
    }
};

texture::~texture(){
    glDeleteTextures(MAX_TEX_COUNT, texIds);
};
