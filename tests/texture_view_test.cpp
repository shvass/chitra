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
 
#include <thread>

#include <glad/glad.h>

#include "mediaUtils/textureView.hpp"
#include "mediaUtils/decoder.hpp"
#include "window.hpp"

class handler : public window::inputHandler {

    void updateTexture(){
        if(!dec) return;
        AVFrame* frm = dec->getFrame();
        if(!frm) return;

        // update texture
        tex = frm;
        dec->dumpFrame(frm);
        if(initial) { view.setTexture(tex); initial=false; }
    };

public:
    void renderloop(){
        while (run)
        {
            // 24 fps frame limiting
            std::this_thread::sleep_for(std::chrono::milliseconds(41));
            processEvents();

            glClear(GL_COLOR_BUFFER_BIT);
            updateTexture();
            view.draw();

            swapBuffer();
        }
    };

    // drop media files to update sources
    void dropInput(const char* path) override{

        if(src) delete src;
        if(dec) delete dec;

        const char* errstr;
        try{
        src = new loader(path);
        errstr = src->getErrStr();
        if(src->err()) throw std::exception();

        dec = new decoder(src->getDefaultVideoStream());
        errstr = dec->getErrStr();
        if(dec->err()) throw std::exception();

        } catch(...){
            printf("error reading media: %s\n", errstr);
            delete src;
            delete dec;
            src = 0;
            dec = 0;
        }
    };
    
    void close() override { run = false; }
    void resized() override { glViewport(0, 0, width, height); }


private:

    bool run=true, initial=true;
    textureView view;
    texture tex;

    decoder* dec =0;
    loader* src=0;
};



int main(){
    window::windowConfig cfg;
    cfg.title = "texture view test - drop media files to play";

    window* win = new window(cfg);
    handler hand;
    win->setActive();
    win->switchHandler(&hand);

    hand.renderloop();

    return 0;
};
