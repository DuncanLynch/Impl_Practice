#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstdint>
#include <stack>

#include "memsize.h"

class Arena {
private: 
    std::byte* baseptr_{};
    std::byte* endptr_{};
    std::byte* curr_{};
    std::stack<std::byte*> stack;
public:
    Arena(const MemSize& size);
    ~Arena() { delete[] baseptr_; }
    Arena(const Arena& other);
    Arena& operator=(const Arena& other);
    Arena(Arena&& other);
    Arena& operator=(Arena&& other);

    void  reset();
    void* allocate(size_t size, size_t alignment);
    void  pop();
};