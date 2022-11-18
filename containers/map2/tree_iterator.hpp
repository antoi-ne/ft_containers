#ifndef FT_MAP_TREE_ITERATOR_HPP
#define FT_MAP_TREE_ITERATOR_HPP

#include <functional>
#include <memory>

#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utils/pair.hpp"

namespace ft
{
    template <class Type, class Compare = std::less<Type> >
    class tree_iterator: ft::iterator<std::bidirectional_iterator_tag, Type>
    {
    public:

        typedef node node_type;
        typedef node_type *node_pointer;
        typedef typename Alloc::template rebind<node<Type> >::other node_alloc;

        tree();
        ~tree();

        ft::pair<int, bool> insert(Type value);
    };
}

#endif
