#include "Renderer.h"

#include "Sort.h"
#include "Timer.h"
#include "Utils.h"

Renderer::Renderer(const char *title, int width, int height) : mWindowInformation({title, width, height}) {
}

Renderer::~Renderer() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    TTF_Quit();
}

bool Renderer::Init() {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(mWindowInformation.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               mWindowInformation.width, mWindowInformation.height, SDL_WINDOW_SHOWN);

    if (mWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Renderer::Run() {
    SDL_Event e;
    ResetScreen();

    while (isRunning) {
        RenderOptions();
        SDL_PollEvent(&e);
        HandleEvents(e);
    }
}

void Renderer::HandleEvents(const SDL_Event &e) {
    switch (e.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_b:
                    Render(SortType::BubbleSort);
                    break;
                case SDLK_r:
                    ResetScreen();
                    RenderOptions();
                    break;
            }
    }
}


void Renderer::Render(SortType type) {
    ResetScreen();
    auto vec = Utils::RandomVector(Utils::RandomInt(10, 500));

    switch (type) {
        case SortType::None:
            break;
        case SortType::BubbleSort:
            RenderText("Bubble Sort!", {0, 0}, 14);
            RenderText("Element count: " + std::to_string(vec.size()), {0, 25}, 14);
            SDL_Delay(2000);
            RenderVec(vec);
            BubbleSort(vec);
            break;
    }
}

void Renderer::RenderOptions() {
    const static std::vector<std::string> options{
            "Press ESC to exit",
            "Press B to start Bubble Sort",
            "Press R to reset screen"};

    for (std::size_t i = 0; i < options.size(); ++i) {
        RenderText(options[i], {mWindowInformation.width / 4, static_cast<int>(0 + i * 24)}, 16);
    }
}


void Renderer::ResetScreen() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void Renderer::RenderVec(const std::vector<Element> &vector) {
    int w = mWindowInformation.width / (int) vector.size();
    for (std::size_t i = 0; i < vector.size(); ++i) {
        int h = -(int) (vector[i].value * mWindowInformation.height);
        int x = (w + 1) * (int) i;
        int y = mWindowInformation.height - 5;
        RenderRect({x, y}, {w, h}, vector[i].color);
    }
    SDL_RenderPresent(mRenderer);
    SDL_UpdateWindowSurface(mWindow);
}

void Renderer::RenderRect(const Position &pos, const Size &size, const Color &color) {
    SDL_Rect rect{pos.x, pos.y, size.w, size.h};
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(mRenderer, &rect);
}

void Renderer::RenderText(const std::string &text, const Position &pos, uint32_t size) {
    TTF_Font *font = TTF_OpenFont("Roboto-Regular.ttf", (int) size);
    if (font == nullptr) {
        printf("Font couldn't be opened!\n");
        return;
    }

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);

    int w = 0;
    int h = 0;
    SDL_QueryTexture(texture, nullptr, 0, &w, &h);
    SDL_Rect rect = {pos.x, pos.y, w, h};

    SDL_RenderCopy(mRenderer, texture, 0, &rect);
    SDL_RenderPresent(mRenderer);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Renderer::BubbleSort(std::vector<Element> vec) {
    Timer timer;
    for (std::size_t i = 0; i < vec.size() - 1; ++i) {
        for (std::size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (Sort::BubbleSortElement(vec[j], vec[j + 1])) {
                ResetScreen();

                Utils::SetElementColor(vec[j], Colors::Red);
                Utils::SetElementColor(vec[j + 1], Colors::Green);

                RenderVec(vec);

                Utils::ResetElementColor(vec[j]);
                Utils::ResetElementColor(vec[j + 1]);
            }
        }
    }
    timer.stop();
    RenderVec(vec);
    RenderText("Finished!", {0, 0}, 14);
    RenderText("Sorting and rendering took: " + std::to_string(timer.GetElapsed()) + "ms", {0, 25}, 14);
}
