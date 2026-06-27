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

#include "pch.hpp"
#include <cstring>

#include <glad/glad.h>

#include "textureViewLayer.hpp"

#define SHADER_TEX_IDENTIFIER "tex"

unsigned int programId=0, arrayId=0, yuvId=0;

float vertices[] = {
    // cords       tex-cords
    -1.0f, 1.0f,  0.0f, 0.0f,
    1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


const char* vertexSrc = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texCords;
out vec2 voTexCords;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);
    voTexCords = texCords;
}
)";

const char* RgbFragmentSrc=R"(
#version 330 core
in vec2 voTexCords;
out vec4 color;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;


void main()
{
    color = vec4(texture(tex0, voTexCords).x,
                 texture(tex1, voTexCords).y,
                 texture(tex2, voTexCords).z,
                 1.0);
}
)";



void compileProgram(){
    int vertexShaderId=0, fragmentShaderId=0,
    length=0, status=0;

    // compile vertex shader
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    length = strlen(vertexSrc);
    glShaderSource(vertexShaderId, 1, &vertexSrc, &length);
    glCompileShader(vertexShaderId);

    // compilation check
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);
    if(!status){
        GLint logLength = 0;
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetShaderInfoLog(vertexShaderId, logLength, nullptr, log.data());

        printf("VERTEX SHADER COMPILATION_FAILED\n%s\n", log.data());
        return;
    }

    // compile fragment shader
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    length = strlen(RgbFragmentSrc);
    glShaderSource(fragmentShaderId, 1, &RgbFragmentSrc, &length);
    glCompileShader(fragmentShaderId);

    // compilation check
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);
    if(!status){
        GLint logLength = 0;
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetShaderInfoLog(fragmentShaderId, logLength, nullptr, log.data());

        printf("FRAGEMENT SHADER COMPILATION_FAILED\n%s\n", log.data());
        return;
    }


    // generate program
    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    // link check
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if(!status) {
        GLint logLength = 0;
        glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<char> log(logLength);
        glGetProgramInfoLog(programId, logLength, nullptr, log.data());
        printf("shader linking failed\n %s", log.data());
    }

    glUseProgram(programId);
    
    // bind texture units with shader uniform identifiers
    for(int i = 0; i < MAX_TEX_COUNT; i++)
    {   
        std::string identifier = std::string(SHADER_TEX_IDENTIFIER) + char{'0' + i};
        unsigned int texAdd = glGetUniformLocation(programId, identifier.c_str());
        glUniform1i(texAdd, i);
    }
};


void loadArray(){

    unsigned int vertexId=0, indexId=0;
    glGenVertexArrays(1, &arrayId);
    glBindVertexArray(arrayId);
    
    // setup vertex buffer
    glGenBuffers(1, &vertexId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // index array
    glGenBuffers(1, &indexId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
};


textureViewLayer::textureViewLayer(){
    if(!programId) compileProgram();
    if(!arrayId) loadArray();
};

void textureViewLayer::draw(){
    glUseProgram(programId);
    glBindVertexArray(arrayId);
    tex.bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
};
