#pragma once

#include "ForwardList.hpp"

#include <iterator>

namespace libcsc::forward_list {
template <typename T>
struct ForwardIterator {
    template <typename T>
    friend class ForwardList;

    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = ForwardList<value_type>*;
    using reference = value_type&;

    ForwardIterator(const ForwardIterator& it) : p{it.p}
    {
    }

    friend bool operator!=(const ForwardIterator& lhs, const ForwardIterator& rhs)
    {
        return lhs.p != rhs.p;
    }

    friend bool operator==(const ForwardIterator& lhs, const ForwardIterator& rhs)
    {
        return lhs.p == rhs.p;
    }

    reference operator*() const
    {
        return *(p->data);
    }

    pointer operator->()
    {
        return p;
    }

    ForwardIterator& operator++()
    {
        p = p->next;
        return *this;
    }

    ForwardIterator operator++(T)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

private:
    ForwardIterator(pointer p) : p{p}
    {
    }

    pointer p;
};
}