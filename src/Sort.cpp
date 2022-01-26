#include "Sort.h"
#include "Timer.h"

bool Sort::BubbleSortElement(Element &e1, Element &e2) {
    if (e1.value > e2.value) {
        std::swap(e1, e2);
        return true;
    }
    return false;
}
