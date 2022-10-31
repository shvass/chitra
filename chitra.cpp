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


#include <iostream>
#include "window.hpp"

#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// log all input events to stdout
class inputLogger : public window::inputHandler{

public:
    bool run = true;

    void renderLoop(){
        display->setActive();
        while (run)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            glClear(GL_COLOR_BUFFER_BIT);
            swapBuffer();
            processEvents();
        }
        
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
        run = false;
        delete display;
    };
};  



int main(){
    std::cout << "chitra is currently under dev \n";
    inputLogger logger;
    window::windowConfig cfg{
        .width = 800,
        .height = 600,
        .title = "chitra is currently under dev",
        .setFullscreen = false,
        .handler = &logger,
    };

    window* win = new window(cfg);
    logger.renderLoop();
    return 0;
};
