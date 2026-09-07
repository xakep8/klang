#pragma once

#include <array>
#include <cstddef>

#include "klang_context.hpp"

template <typename T>
class SmallVector : private klang::Context {
   private:
    constexpr static std::size_t kmax_stack_alloc = 128;
    std::size_t m_allocation_size = kmax_stack_alloc;
    std::array<T, kmax_stack_alloc> m_data{};
    std::int64_t m_back = -1;

   public:
    SmallVector() = default;

    SmallVector(const std::size_t size) {
        if (size > m_allocation_size) {
            m_data = std::array<T, 2 * m_allocation_size>{};
            m_allocation_size = 2 * m_allocation_size;
        }
    }

    ~SmallVector() = default;

    std::size_t get_size() const { return m_back + 1; }

    void push(T value) {
        m_back++;
        m_data[m_back] = value;
    }

    void pop_back() {
        if (m_back >= 0) {
            m_back--;
            return;
        }
        // should not be reachable
        throw std::out_of_range("Vector already Empty!");
    }

    const T& operator[](const std::size_t index) const {
        if (m_back == -1)
            throw std::out_of_range("Out of bounds access vector empty!");

        if (index > m_back) throw std::out_of_range("Out of bounds access");
        return m_data[index];
    }
};
