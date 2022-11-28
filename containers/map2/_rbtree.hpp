// Red Black Tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
// Adapted by: Antoine Coulon

#pragma once

#include <iostream>

namespace ft {

    template <class Type>
    struct _node
    {
        typedef Type                    value_type;
        typedef _node<Type>             node_type;
        typedef enum {BLACK, RED, LEAF} node_color;

        value_type                      data;
        node_color                      color;

        node_type                       *parent;
        node_type                       *left;
        node_type                       *right;
    };

    template <class Type, class Compare = std::less<Type>, class Allocator = std::allocator<Type> >
    class _rbtree
    {
    public: // member types

        typedef Type                value_type;
        typedef Compare             value_compare;
        typedef Allocator           allocator_type;

    private: // attributes

        typedef _node<value_type>                                   _node_type;

        value_compare                                               _comp;
        allocator_type                                              _alloc;
        typename allocator_type::template rebind<_node_type>::other _node_alloc;

        _node_type                                                   *_root;
        _node_type                                                   *_leaf;

    public: // contructor const

        _rbtree(value_compare comp = value_compare(), allocator_type alloc = allocator_type())
            : _comp(comp), _alloc(alloc)
        {
            this->_leaf = this->_make_node();
            this->_leaf->color = _node_type::LEAF;
            this->_root = this->_leaf;
        }

        ~_rbtree()
        {}

    private: // helpers

        void printHelper(_node_type *root, std::string indent, bool last) {
        if (root != this->_leaf) {
           std::cout << indent;
           if (last) {
              std::cout << "R----";
              indent += "     ";
           } else {
              std::cout << "L----";
              indent += "|    ";
           }
            
           std::string sColor = root->color?"RED":"BLACK";
           std::cout << root->data << "(" << sColor << ")" << std::endl;
           printHelper(root->left, indent, false);
           printHelper(root->right, indent, true);
        }
    }

        _node_type *_make_node()
        {
            _node_type *n = this->_node_alloc.allocate(1);
            n->parent = NULL;
            n->left = NULL;
            n->right = NULL;
            return n;
        }

        void _left_rotate(_node_type *x)
        {
            _node_type * y = x->right;
            x->right = y->left;
            if (y->left != this->_leaf)
                y->left->parent = x;
            y->parent= x->parent;
            if (x->parent == NULL)
                this->_root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y; 
        }

        void _right_rotate(_node_type *x)
        {
            _node_type * y = x->left;
            x->left = y->right;
            if (y->right != this->_leaf)
                y->right->parent = x;
            y->parent= x->parent;
            if (x->parent == NULL)
                this->_root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y; 
        }

        void _fix_insert(_node_type *k)
        {
            _node_type *u;
            while (k->parent->color == _node_type::RED)
            {
                if (k->parent == k->parent->parent->right)
                {
                    u = k->parent->parent->left;
                    if (u->color == _node_type::RED)
                    {
                        u->color = _node_type::BLACK;
                        k->parent->color = _node_type::BLACK;
                        k->parent->parent->color = _node_type::RED;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->left)
                        {
                            k = k->parent;
                            this->_right_rotate(k);
                        }
                        k->parent->color = _node_type::BLACK;
                        k->parent->parent->color = _node_type::RED;
                        this->_left_rotate(k->parent->parent);
                    }
                }
                else
                {
                    u = k->parent->parent->right;
                    if (u->color == _node_type::RED)
                    {
                        u->color = _node_type::BLACK;
                        k->parent->color = _node_type::BLACK;
                        k->parent->parent->color = _node_type::RED;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->right)
                        {
                            k = k->parent;
                            this->_left_rotate(k);
                        }
                        k->parent->color = _node_type::BLACK;
                        k->parent->parent->color = _node_type::RED;
                        this->_right_rotate(k->parent->parent);
                    }
                }
                if (k == this->_root)
                    break;
            }
            this->_root->color = _node_type::BLACK;
        }

    public:

        void prettyPrint() {
            if (this->_root)
                this->printHelper(this->_root, "", true);
        }

        void insert(value_type value)
        {
            _node_type *n = this->_make_node();
            n->data = value;
            n->color = _node_type::RED;
            n->parent = NULL;
            n->left = this->_leaf;
            n->right = this->_leaf;

            _node_type *y = NULL;
            _node_type *x = this->_root;

            while (x != this->_leaf)
            {
                y = x;
                if (this->_comp(n->data, x->data))
                    x = x->left;
                else
                    x = x->right;
            }

            n->parent = y;
            if (y == NULL)
                this->_root = n;
            else if (this->_comp(n->data, y->data))
                y->left = n;
            else
                y->right = n;

            if (n->parent == NULL)
            {
                n->color = _node_type::BLACK;
                return;
            }

            if (n->parent->parent == NULL)
                return;

            this->_fix_insert(n);
        }
    };

};
