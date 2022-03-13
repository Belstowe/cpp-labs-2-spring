#pragma once

#include "ForwardList.hpp"

#include <iterator>

namespace libcsc::forward_list
{
    template<typename T>
    class ForwardIterator : public std::iterator<std::input_iterator_tag, T>
    {
        friend class ForwardList;

        private:
            ForwardIterator(ForwardList<T>* p)
                : p{p}
            {}

            ForwardList<T>* p;

        public:
            ForwardIterator(const ForwardIterator& it)
                : p{it.p}
            {}

            bool operator!=(ForwardIterator const& other) const
            {
                return p != other.p;
            }

            bool operator==(ForwardIterator const& other) const
            {
                return p == other.p;
            }

            T ForwardIterator::reference operator*() const
            {
                return *(p->data);
            }

            OwnIterator& operator++()
            {
                p = p->next;
                return *this;
            }
    };
}