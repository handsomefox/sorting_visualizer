#pragma once

#include <iostream>
#include <random>
#include <vector>

#include "Structs.h"

namespace Utils {
    static void SetElementColor(Element &element, const Color &color) {
        element.color = {color.r, color.g, color.b, color.a};
    }

    static void ResetElementColor(Element &e) {
        e.color = Colors::White;
    }

    static int RandomInt(const int min, const int max) {
        std::random_device device;
        std::default_random_engine engine(device());
        const std::uniform_int_distribution dist(min, max);
        return dist(engine);
    }

    static double RandomReal(const double min, const double max) {
        std::random_device device;
        std::default_random_engine engine(device());
        const std::uniform_real_distribution dist(min, max);
        return dist(engine);
    }

    static std::vector<Element> RandomVector(const std::size_t size) {
        std::vector<Element> vector;
        vector.reserve(size);

        for (std::size_t i = 0; i < size; ++i) {
            vector.push_back({RandomReal(0.0, 1.0), Colors::White});
        }
        return vector;
    }

    [[maybe_unused]] static void PrintVector(const std::vector<Element> &vector) {
        std::for_each(vector.begin(), vector.end(), [&](const Element &e) { std::cout << e.value << ' '; });
        std::cout << '\n';
    }
}// namespace Utils
