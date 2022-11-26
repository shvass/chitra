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

// test for imgui
// program displays imgui demo window

#include <iostream>

#include <glad/glad.h>

#include "windowing/window.hpp"
#include "layers/imguiLayer.hpp"


class inputLogger : public window::inputHandler, public window::layer{

public:

    void render() override{
        glClearColor(0.4f, 0.7f, 0.2f, 1.0f);
    };

    void inputLoop(){
        while(display->run)
            processEvents();
    };
};  


int main(){
    window* win = new window();
    inputLogger lgr;
    win->switchHandler(&lgr);

    imguiLayer imgLyr;
    win->layers.push_front(&imgLyr);
    win->layers.push_back(&lgr);

    lgr.inputLoop();
    return 0;
}
