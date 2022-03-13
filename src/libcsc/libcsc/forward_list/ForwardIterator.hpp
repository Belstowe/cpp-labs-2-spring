#pragma once

#include "ForwardList.hpp"

#include <iterator>

namespace libcsc::forward_list {
template <typename T, bool IsConst>
struct ForwardIterator
{
    template <typename T, bool IsConst>
    friend class ForwardList;

    using iterator_category = std::input_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = std::conditional_t<IsConst, const ForwardList<value_type, true>*, ForwardList<value_type, false>*>;
    using reference         = std::conditional_t<IsConst, const value_type&, value_type&>;

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
    {}

    pointer p;
};
}