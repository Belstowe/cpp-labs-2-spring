#pragma once

#include <initializer_list>
#include <memory>

namespace libcsc::forward_list {
template <typename T>
struct ForwardIterator;

template <typename T>
class ForwardList {
    template <typename T>
    friend struct ForwardIterator;

public:
    typedef ForwardIterator<T> iterator;

    ForwardList() : data{nullptr}, next{nullptr}
    {
    }

    ForwardList(T data) : data{std::make_unique<T>(data)}, next{new ForwardList<T>()}
    {
    }

    ForwardList(std::initializer_list<T> val_list) : ForwardList(val_list.begin(), val_list.end())
    {
    }

    void chain(ForwardList& node)
    {
        if (next != nullptr) {
            delete next;
        }

        next = &node;
    }

    iterator begin()
    {
        return iterator(this);
    }

    iterator end()
    {
        return (next == nullptr) ? iterator(this) : next->end();
    }

    std::size_t size()
    {
        return std::distance(begin(), end());
    }

private:
    ForwardList(const T* begin, const T* end)
    {
        if (begin != end) {
            next = new ForwardList<T>(std::next(begin), end);
            data = std::make_unique<T>(*begin);
        } else {
            next = nullptr;
            data = nullptr;
        }
    }

    std::unique_ptr<T> data;
    ForwardList<T>* next;
};
}