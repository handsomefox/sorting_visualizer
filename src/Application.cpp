#include "Application.h"

#include "Renderer.h"

int Application::run(const char *title, const int width, const int height) {
    Renderer renderer(title, width, height);
    if (renderer.Init()) {
        renderer.Run();
    } else {
        return -1;
    }
    return 0;
}
