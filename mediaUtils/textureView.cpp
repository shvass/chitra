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

#include <iostream>
#include <string>
#include <cstring>
#include <glad/glad.h>
#include "textureView.hpp"

unsigned int programId=0, arrayId=0;

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

const char* fragmentSrc=R"(
#version 330 core
in vec2 voTexCords;
out vec4 color;

uniform sampler2D tex;
void main()
{
    color= texture(tex, voTexCords);
}
)";



void compileProgram(){
    int vertexShaderId=0, fragmentShaderId=0,
    length=0, status=0;
    char buffer[100];

    // compile vertex shader
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    length = strlen(vertexSrc);
    glShaderSource(vertexShaderId, 1, &vertexSrc, &length);
    glCompileShader(vertexShaderId);

    // compilation check
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);
    if(!status){
        glGetShaderInfoLog(vertexShaderId, 100, NULL, buffer);
        printf("VERTEX SHADER COMPILATION_FAILED\n %s \n", buffer);
        return;
    }

    // compile fragment shader
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    length = strlen(fragmentSrc);
    glShaderSource(fragmentShaderId, 1, &fragmentSrc, &length);
    glCompileShader(fragmentShaderId);

    // compilation check
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);
    if(!status){
        glGetShaderInfoLog(fragmentShaderId, 100, NULL, buffer);
        printf("FRAGMENT SHADER COMPILATION_FAILED\n %s \n", buffer);
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
        glGetProgramInfoLog(programId, 100, NULL, buffer);
        printf("shader linking failed\n %s", buffer);
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


textureView::textureView(){
    if(!programId) compileProgram();
    if(!arrayId) loadArray();
};

void textureView::setTexture(texture& tex){
    texId = tex.texId;
};

void textureView::draw(){
    glUseProgram(programId);
    glBindVertexArray(arrayId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
};
