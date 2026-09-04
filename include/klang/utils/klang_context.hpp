#pragma once

#include <allocator_slab.h>

#include <new>

namespace klang {
class Context {
   private:
    SlabAllocator m_allocator;

   public:
    template <typename T, typename... Args>
    T* create(Args&&... args) {
        void* memory = m_allocator.allocate(sizeof(T));
        if (!memory) {
            throw std::bad_alloc();
        }
        return new (memory) T(std::forward<Args>(args)...);
    }

    template <typename T, typename... Args>
    void destroy(T* ptr) {
        if (!ptr) return;

        ptr->T();
        m_allocator.free(ptr, sizeof(T));
    }
};
}  // namespace klang
