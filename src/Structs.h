#pragma once

enum class SortType {
    None,
    BubbleSort,
};

struct WindowInformation {
    [[maybe_unused]] const char *title;
    int width;
    int height;
};

struct Position {
    int x, y;
};
struct Size {
    int w, h;
};

struct Color {
    unsigned char r, g, b, a;
};

namespace Colors {
    static constexpr Color Red{255, 0, 0, 255};
    static constexpr Color Green{0, 255, 0, 255};
    static constexpr Color Blue{0, 0, 255, 255};
    static constexpr Color White{255, 255, 255, 255};
    static constexpr Color Black{0, 0, 0, 255};
}// namespace Colors

struct Element {
    double value;
    Color color;
};
