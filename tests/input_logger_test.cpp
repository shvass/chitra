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

/**
 * logs all window inputs to stdout
*/

#include <iostream>
#include <glad/glad.h>

#include "windowing/window.hpp"
#include "layers/imguiLayer.hpp"




// log all input events to stdout
class inputLogger : public window::inputHandler{

public:

    void inputLoop(){
        while(display->run)
            processEvents();
    };

    void cursorUpdate() override{
        printf("cursor pos: %lf %lf  delta: %lf %lf\n", posX, posY, dposX, dposY);
    };

    void keyStateUpdate(int key, bool down) override{
        printf("key %c was %s\n", key, (down) ? "pressed" : "released");
    };

    void mouseButtonUpdate(int key, bool down) override{
        printf("mouse key %s was %s\n", (key) ? "right" : "left", (down) ? "pressed" : "released");
    };

    void scrollUpdate() override{
        printf("scroll: %lf  %lf  delta: %lf  %lf\n", scrollX, scrollY, dScrollX, dScrollY);
    };


    void resized() override{
        printf("window size %d x %d\n", width, height);
    };

    void dropInput(const char* path){
        printf("dropped %s\n", path);
    };

    void close() override {
        printf("window closed\n");
    };
};  



int main(int argn, const char ** argv){

    std::cout << "chitra is currently under dev \n";
    inputLogger logger;
    window::windowConfig cfg{
        .title = "imgui test",
        .handler = &logger,
    };

    window* win = new window(cfg);
    imguiLayer imgLyr;
    win->layers.push_back(&imgLyr);

    logger.inputLoop();
    return 0;
};
