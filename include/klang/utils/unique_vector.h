#pragma once

#include <array>
#include <cstddef>

#include "klang_context.h"

template <typename T>
class UniqueVector : private klang::Context {
   private:
    constexpr static std::size_t kmax_stack_alloc = 128;
    std::size_t size;
    std::array<T, kmax_stack_alloc> data_{};

   public:
    UniqueVector();
    UniqueVector(const size_t size);
    ~UniqueVector();
    std::size_t get_size() const { return size; }
    void push();
    void pop_back();
    int& operator[](const std::size_t index) const { return data_[index]; }
};
