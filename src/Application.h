#pragma once

class Application {
public:
    Application() = delete;
    static int run(const char *title, int width, int height);
};
