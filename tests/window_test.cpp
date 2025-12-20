#include <windowing/window.hpp>
#include <unistd.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h>


class inputLogger : public window::inputHandler
{
public:

    void close() override {
        display->run = false;
    };

    void resized() override {

    };
    void cursorUpdate() override {

    };
    void scrollUpdate() override {

    };
    void dropInput(const char* str) override {

    };
    void keyStateUpdate(int keyCode, bool down) override {

    };
    void mouseButtonUpdate(int keyCode, bool down) override {

    };
};

class dummyRenderer : public window::layer
{
    void render() override
    {
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };
};


int main()
{

    inputLogger lg;
    window::windowConfig cfg = {
        .width = 500,
        .height = 500,
        .monitorIndex = 0,
        .title = "dummy",
        .resizable = true,
        .handler = &lg,
    };

    window w(cfg);
    w.layers.push_back(new dummyRenderer());

    while (w.run)
    {
        lg.processEvents();
        usleep(1000);
    }
    

    return 0;
};