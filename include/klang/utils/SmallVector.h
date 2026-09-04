#pragma once

#include <array>
#include <cstddef>

#include "klang_context.hpp"

template <typename T>
class SmallVector : private klang::Context {
   private:
    constexpr static std::size_t kmax_stack_alloc = 128;
    std::size_t m_size = kmax_stack_alloc;
    std::array<T, kmax_stack_alloc> m_data{};
    std::size_t m_back = 0;

   public:
    SmallVector();
    SmallVector(const size_t size);
    ~SmallVector();
    std::size_t get_size() const { return m_size; }
    void push(T value);
    void pop_back();
    T& operator[](const std::size_t index) const;
};
