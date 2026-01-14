#include "arena.h"
#include <cstring>

// does not zero memory
Arena::Arena(const MemSize& size) {
    size_t bufsize = size.getSizeInBytes();
    baseptr_ = new std::byte[bufsize];
    curr_ = baseptr_;
    endptr_ = baseptr_ + bufsize;
}

Arena::Arena(const Arena& other) {
    baseptr_ = other.baseptr_;  
    curr_ = other.curr_;
    endptr_ = other.endptr_;  
}

Arena::Arena(Arena&& other) {
    baseptr_ = other.baseptr_;  
    curr_ = other.curr_;
    endptr_ = other.endptr_;  

    other.baseptr_ = nullptr;
    other.curr_ = nullptr;
    endptr_ = nullptr;
}

Arena& Arena::operator=(const Arena& other) {
    if (this != &other) {
        delete[] baseptr_;
        baseptr_ = other.baseptr_;
        curr_ = other.curr_;
        endptr_ = other.endptr_;
    }
    return *this;
}

Arena& Arena::operator=(Arena&& other) {
    if (this != &other) {
        delete[] baseptr_;
        baseptr_ = other.baseptr_;
        curr_ = other.curr_;
        endptr_ = other.endptr_;

        other.baseptr_ = nullptr;
        other.curr_ = nullptr;
        other.endptr_ = nullptr;
    }
    return *this;
}

void Arena::reset() {
    curr_ = baseptr_;(
    std::memset(baseptr_, 0, (size_t)(endptr_ - baseptr_)));
}

void* Arena::allocate(size_t size, size_t alignment) {
    if (!(alignment > 0)) throw std::logic_error("Alignment must be greater than 0!");
    int64_t remaining_space = (int64_t) (endptr_ - curr_);
    if (remaining_space <= 0) return nullptr;
    size_t total_space = (size_t) (endptr_ - baseptr_);
    size_t curr = total_space - remaining_space;
    size_t padding = (curr % alignment == 0) ? 0 : alignment - (curr % alignment);
    if (size + padding > remaining_space) return nullptr;
    std::byte* result = curr_ + padding;
    // pushes to the stack before curr_ is moved
    stack.push(curr_);
    curr_ = result + size;
    return result;
}

void Arena::pop() {
    std::byte* last_pos = stack.top();
    size_t size = (size_t)(curr_ - last_pos);
    std::memset(last_pos, 0, size);
    curr_ = last_pos;
    stack.pop();
}
