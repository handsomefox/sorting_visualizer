#include "Application.h"

int Application::run(const char *title, int width, int height) {
    Renderer renderer(title, width, height);
    if (renderer.Init()) {
        renderer.Run();
    } else {
        return -1;
    }
    return 0;
}
