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
    int r, g, b, a;
};

namespace Colors {
    static Color Red{255, 0, 0, 255};
    static Color Green{0, 255, 0, 255};
    static Color Blue{0, 0, 255, 255};
    static Color White{255, 255, 255, 255};
    static Color Black{0, 0, 0, 255};
}// namespace Colors

struct Element {
    double value;
    Color color;
};
