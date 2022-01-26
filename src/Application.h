#pragma once
#include "Renderer.h"

class Application {
public:
    Application() = delete;
    static int run(const char *title, int width, int height);
};
