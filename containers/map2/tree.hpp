#ifndef FT_MAP_TREE_HPP
#define FT_MAP_TREE_HPP

#include <functional>
#include <memory>

#include "../utils/pair.hpp"

namespace ft
{
    template <typename Type>
    struct node
    {
        typedef Type value_type;

        value_type key_value;
        node *left;
        node *right;
        node *parent;
    };

    template <class Type, class Compare = std::less<Type>, class Alloc = std::allocator<Type> >
    class tree
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
