#pragma once

#include <initializer_list>
#include <memory>

namespace libcsc::forward_list {
template <typename T, bool IsConst>
struct ForwardIterator;

template <typename T, bool IsConst = true>
class ForwardList {
    template <typename T, bool IsConst>
    friend struct ForwardIterator;

public:
    typedef ForwardIterator<T, false> iterator;
    typedef ForwardIterator<T, true> const_iterator;

    using value_type = std::conditional_t<IsConst, const ForwardList<T, true>, ForwardList<T, false>>;

    ForwardList() : data{nullptr}, next{nullptr}
    {
    }

    ForwardList(T data) : data{std::make_unique<T>(data)}, next{new ForwardList<T>()}
    {
    }

    ForwardList(std::initializer_list<T> val_list) : ForwardList(val_list.begin(), val_list.end())
    {
    }

    void chain(const ForwardList& node)
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

    const_iterator begin() const
    {
        return const_iterator(this);
    }

    const_iterator end() const
    {
        return (next == nullptr) ? const_iterator(this) : next->end();
    }

    std::size_t size() const
    {
        return std::distance(begin(), end());
    }

private:
    ForwardList(const T* begin, const T* end)
    {
        if (begin != end) {
            next = new value_type(std::next(begin), end);
            data = std::make_unique<T>(*begin);
        } else {
            next = nullptr;
            data = nullptr;
        }
    }

    std::unique_ptr<T> data;
    value_type* next;
};
}