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

// later- add colored rendering
// float yuvToRgb[] = {
//     0.2126f, -0.09991f, 0.615f,
//     0.7152f, -0.33609f, -0.55861f,
//     0.0722f,  0.436f, -0.05639f 
// };


// float yuvToRgb[] = {
//     1.0f, 0.0f, 1.13983f,
//     1.0f, -0.39465f, -0.58060f,
//     1.0f,  2.03211f, 0.0f 
// };


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
uniform sampler2D uvTex;
uniform bool isyuv=false;
uniform mat3 yuvToRgb;

void main()
{
    color = texture(tex, voTexCords);
    if(isyuv){
        color.yz = texture(uvTex, voTexCords).xy;
        // color.xyz = yuvToRgb * color.xyz;

        float R, G, B, Y, U, V;
        Y = color.x;
        U = color.y;
        V = color.z;

        R = Y + 1.140 * V;
        G = Y - 0.395 * U - 0.581 * V;
        B = Y + 2.032 * U;

        color.xyz = vec3(R, G, B);
    };
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


    // later -add colored rendering
    // glUseProgram(programId);
    // yuvId = glGetUniformLocation(programId, "isyuv");
    // glUniformMatrix3fv(glGetUniformLocation(programId, "yuvToRgb"), 1, GL_TRUE, yuvToRgb);


    // later -add colored rendering
    // // bind uv texture to slot 1
    // glUniform1i(glGetUniformLocation(programId, "uvTex"), 1);

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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.texId);

    // later- add colored rendering
    // if(tex.isYUV()){
    //     glUniform1i(yuvId, tex.isYUV());

    //     glActiveTexture(GL_TEXTURE1);
    //     glBindTexture(GL_TEXTURE_2D, tex.uvTexId);
    // }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
};
