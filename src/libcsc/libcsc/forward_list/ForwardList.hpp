#pragma once

#include <initializer_list>
#include <memory>

namespace libcsc::forward_list
{
    template<typename T>
    class ForwardIterator;

    template<typename T>
    class ForwardList
    {
        friend class ForwardIterator;
        
        public:
            typedef ForwardIterator<T> iterator;
            typedef ForwardIterator<const T> const_iterator;

            ForwardList()
            : data{nullptr}, next{nullptr}
            {}

            ForwardList(T data)
            : data{make_unique<T>(data)}, next{new ForwardList()}
            {}

            ForwardList(std::initializer_list<T> val_list)
            : ForwardList(val_list.begin(), val_list.end())
            {}

            void chain(const ForwardList& node)
            {
                if (next != nullptr) {
                    delete next;
                }

                next = &node;
            }

            iterator begin()
            {
                return iterator<T>(this);
            }

            iterator end()
            {
                return (next == nullptr) ? iterator<T>(this) : next->end();
            }

            const_iterator begin() const
            {
                return const_iterator<T>(this);
            }

            const_iterator end() const
            {
                return (next == nullptr) ? const_iterator<T>(this) : next->end();
            }

        private:
            ForwardList(const T* begin, const T* end)
            {
                if (begin != end)
                {
                    next = new ForwardList<T>(std::next(begin), end);
                    data = make_unique<T>(*begin);
                }
                else
                {
                    data = nullptr;
                    next = nullptr;
                }
            }

            std::unique_ptr<T> data;
            ForwardList* next;
    };
}