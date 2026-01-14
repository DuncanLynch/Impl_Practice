#include "arena.h"
#include <iostream>

int main() {
    Arena arena(GiB(1));

    int* arr = static_cast<int*>(arena.allocate(sizeof(int) * 10, alignof(int)));

    // Use it like a normal array
    for (int i = 0; i < 10; ++i) {
        arr[i] = i * 2;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    arena.reset();
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
}
