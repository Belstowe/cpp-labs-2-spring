#pragma once

namespace libcsc::smartptr {
template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* count;

    void dereference()
    {
        if (count != nullptr) {
            if (--(*count) == 0) {
                delete count;
                if (ptr != nullptr) {
                    delete ptr;
                }
            }
        }
    }

public:
    SharedPtr() : ptr{nullptr}, count{nullptr}
    {
    }

    SharedPtr(T* const ptr) : ptr{ptr}, count{new size_t(1)}
    {
    }

    SharedPtr(const SharedPtr& copied) : ptr{copied.ptr}, count{copied.count}
    {
        if (count != nullptr) {
            (*count)++;
        }
    }

    SharedPtr(SharedPtr&& moved) : ptr{moved.ptr}, count{moved.count}
    {
        moved.ptr = nullptr;
        moved.count = nullptr;
    }

    ~SharedPtr()
    {
        dereference();
    }

    SharedPtr& operator=(const SharedPtr& copied)
    {
        if (this == &copied) {
            return *this;
        }

        dereference();

        ptr = copied.ptr;
        count = copied.count;
        if (count != nullptr) {
            (*count)++;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& moved)
    {
        if (this == &moved) {
            return *this;
        }

        dereference();

        ptr = copied.ptr;
        count = copied.count;
        moved.ptr = nullptr;
        moved.count = nullptr;
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
        dereference();

        ptr = p;
        if (p != nullptr) {
            count = new size_t(1);
        } else {
            count = nullptr;
        }
    }

    std::size_t use_count() const
    {
        return (count == nullptr) ? 0 : *count;
    }
};
}