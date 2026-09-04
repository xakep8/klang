#include "klang/utils/SmallVector.h"

#include <stdexcept>

template <typename T>
SmallVector<T>::SmallVector(const std::size_t size) {
    if (size > m_size) {
        m_data = std::array<T, 2 * m_size>{};
        m_size = 2 * m_size;
    }
}

template <typename T>
void SmallVector<T>::push(T value) {
    m_data[m_back] = value;
    m_back++;
}

template <typename T>
void SmallVector<T>::pop_back() {
    if (m_back > 0) {
        m_back--;
    }
}

template <typename T>
T& SmallVector<T>::operator[](const std::size_t index) const {
    if (m_back == 0) throw std::out_of_range("Out of bounds access");

    if (index >= m_back) throw std::out_of_range("Out of bounds access");
    return m_data[index];
}
