#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"
#undef SDL_MAIN_HANDLED

#include <string>
#include <vector>

#include "Structs.h"

class Renderer {
public:
    Renderer(const char *title, int width, int height);
    ~Renderer();

    bool Init();
    void Run();

private:
    void ResetScreen() const;
    void Render(SortType) const;
    void RenderVec(const std::vector<Element> &) const;
    void RenderRect(const Position &, const Size &, const Color &) const;
    void RenderText(const std::string &, const Position &, unsigned int size) const;
    void RenderOptions() const;
    void BubbleSort(std::vector<Element>) const;
    void HandleEvents(const SDL_Event &);

private:
    bool isRunning = true;
    WindowInformation mWindowInformation{"Window", 640, 480};
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};
