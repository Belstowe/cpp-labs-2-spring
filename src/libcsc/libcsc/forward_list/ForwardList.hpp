#pragma once

#include <initializer_list>
#include <memory>

namespace libcsc::forward_list {
template <typename T>
struct ForwardIterator;

template <typename TypeName>
class ForwardList {
    template <typename T>
    friend struct ForwardIterator;

public:
    typedef ForwardIterator<TypeName> iterator;

    ForwardList() : data{nullptr}, next{nullptr}
    {
    }

    ForwardList(TypeName data) : data{std::make_unique<TypeName>(data)}, next{new ForwardList<TypeName>()}
    {
    }

    ForwardList(std::initializer_list<TypeName> val_list) : ForwardList(val_list.begin(), val_list.end())
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
    ForwardList(const TypeName* begin, const TypeName* end)
    {
        if (begin != end) {
            next = new ForwardList<TypeName>(std::next(begin), end);
            data = std::make_unique<TypeName>(*begin);
        } else {
            next = nullptr;
            data = nullptr;
        }
    }

    std::unique_ptr<TypeName> data;
    ForwardList<TypeName>* next;
};
}