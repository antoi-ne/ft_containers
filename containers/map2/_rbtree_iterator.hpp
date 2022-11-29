#pragma once

#include <functional>
#include <memory>

#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utils/pair.hpp"
#include "./_rbtree.hpp"

namespace ft
{
    template <class Type, class Compare = std::less<Type> >
    class _rbtree_iterator: ft::iterator<std::bidirectional_iterator_tag, Type>
    {
    public:

        typedef typename ft::iterator_traits<T>::difference_type    difference_type;
        typedef typename ft::iterator_traits<T>::value_type         value_type;
        typedef typename ft::iterator_traits<T>::pointer            pointer;
        typedef typename ft::iterator_traits<T>::reference          reference;
        typedef std::bidirectional_iterator_tag                     iterator_category;

        typedef _node<T>                                            node_type;

    private:

        node_type   *_ptr;

    public:

        _rbtree_iterator(node_type *node = NULL)
            : _ptr(node)
        {}

        ~_rbtree_iterator()
        {}

    };
}
