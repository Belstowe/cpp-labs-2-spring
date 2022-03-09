#pragma once

namespace libcsc::smartptr {
template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr(T* const ptr = nullptr) : ptr{ptr}
    {
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& moved)
    {
        ptr = moved.ptr;
        moved.ptr = nullptr;
    }

    ~UniquePtr()
    {
        if (ptr != nullptr) {
            delete ptr;
        }
    }

    UniquePtr operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& obj)
    {
        if (this == &obj) {
            return *this;
        }
        if (ptr != nullptr) {
            delete ptr;
        }

        ptr = obj.ptr;
        obj.ptr = nullptr;
        return *this;
    }

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    T* get() const
    {
        return ptr;
    }

    void reset(T* const p = nullptr)
    {
        if (ptr != nullptr) {
            delete ptr;
        }
        ptr = p;
    }
};
}