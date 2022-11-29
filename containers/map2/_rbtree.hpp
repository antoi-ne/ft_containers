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

        typedef _node<value_type>   node_type;

    private: // attributes

        value_compare                                               _comp;
        allocator_type                                              _alloc;
        typename allocator_type::template rebind<node_type>::other  _node_alloc;

        node_type                                                   *_root;
        node_type                                                   *_leaf;

    public: // contructors & destructors

        _rbtree(value_compare comp = value_compare(), allocator_type alloc = allocator_type())
            : _comp(comp), _alloc(alloc), _node_alloc()
        {
            this->_leaf = this->_make_node();
            this->_leaf->color = node_type::LEAF;
            this->_root = this->_leaf;
        }

        ~_rbtree()
        {}

    public: // methods

        void prettyPrint() {
            if (this->_root)
                this->printHelper(this->_root, "", true);
        }

        void insert(value_type value)
        {
            node_type *n = this->_make_node();
            n->data = value;
            n->color = node_type::RED;
            n->parent = NULL;
            n->left = this->_leaf;
            n->right = this->_leaf;

            node_type *y = NULL;
            node_type *x = this->_root;

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
                n->color = node_type::BLACK;
                return;
            }

            if (n->parent->parent == NULL)
                return;

            this->_fix_insert(n);
        }

        node_type *search(value_type key)
        {
            return this->_seach_helper(this->_root, key);
        }



    private: // helpers

        void printHelper(node_type *root, std::string indent, bool last) {
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

        node_type *_seach_helper(node_type *n, value_type key)
        {
            if (n == this->_leaf || (!this->_comp(key, n->data) && !this->_comp(n->data, key)))
                return n;
            else if (this->_comp(key, n->data))
                return this->_seach_helper(n->left, key);
            else
                return this->_seach_helper(n->right, key);
        }

        node_type *_make_node()
        {
            node_type *n = this->_node_alloc.allocate(1);
            n->parent = NULL;
            n->left = NULL;
            n->right = NULL;
            return n;
        }

        void _left_rotate(node_type *x)
        {
            node_type * y = x->right;
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

        void _right_rotate(node_type *x)
        {
            node_type * y = x->left;
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

        void _fix_insert(node_type *k)
        {
            node_type *u;
            while (k->parent->color == node_type::RED)
            {
                if (k->parent == k->parent->parent->right)
                {
                    u = k->parent->parent->left;
                    if (u->color == node_type::RED)
                    {
                        u->color = node_type::BLACK;
                        k->parent->color = node_type::BLACK;
                        k->parent->parent->color = node_type::RED;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->left)
                        {
                            k = k->parent;
                            this->_right_rotate(k);
                        }
                        k->parent->color = node_type::BLACK;
                        k->parent->parent->color = node_type::RED;
                        this->_left_rotate(k->parent->parent);
                    }
                }
                else
                {
                    u = k->parent->parent->right;
                    if (u->color == node_type::RED)
                    {
                        u->color = node_type::BLACK;
                        k->parent->color = node_type::BLACK;
                        k->parent->parent->color = node_type::RED;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->right)
                        {
                            k = k->parent;
                            this->_left_rotate(k);
                        }
                        k->parent->color = node_type::BLACK;
                        k->parent->parent->color = node_type::RED;
                        this->_right_rotate(k->parent->parent);
                    }
                }
                if (k == this->_root)
                    break;
            }
            this->_root->color = node_type::BLACK;
        }

        void _transplant(node_type *u, node_type *v)
        {
            if (u->parent == NULL)
                this->_root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            v->parent = u->parent;
        }

        node_type *_minimum(node_type *n)
        {
            while (n->left != this->_leaf) {
                n = n->left;
            }
            return n;
        }

        node_type *_maximum(node_type *n)
        {
            while (n->right != this->_leaf) {
                n = n->right;
            }
            return n;
        }

        void _fix_delete(node_type *x)
        {
            node_type *s;
            while (x != this->_root && x->color == node_type::BLACK)
            {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == node_type::RED)
                    {
                        s->color = node_type::BLACK;
                        x->parent->color = node_type::RED;
                        this->_left_rotate(x->parent);
                        s = x->parent->right;
                    }
                    if (s->left->color == node_type::BLACK && s->right->color == node_type::BLACK)
                    {
                        s->color = node_type::RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->right->color == node_type::BLACK)
                        {
                            s->left->color = node_type::BLACK;
                            s->color = node_type::RED;
                            this->_right_rotate(s);
                            s = x->parent->right;
                        }
                        s->color = x->parent->color;
                        x->parent->color = node_type::BLACK;
                        s->right->color = node_type::BLACK;
                        this->_left_rotate(x->parent);
                        x = this->_root;
                    }
                }
                else
                {
                    s = x->parent->left;
                    if (s->color == node_type::RED)
                    {
                        s->color = node_type::BLACK;
                        x->parent->color = node_type::RED;
                        this->_right_rotate(x->parent);
                        s = x->parent->left;
                    }
                    if (s->right->color == node_type::BLACK && s->right->color == node_type::BLACK)
                    {
                        s->color = node_type::RED;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->left->color == node_type::BLACK)
                        {
                            s->right->color = node_type::BLACK;
                            s->color = node_type::RED;
                            this->_left_rotate(s);
                            s = x->parent->left;
                        }
                        s->color = x->parent->color;
                        x->parent->color = node_type::BLACK;
                        s->left->color = node_type::BLACK;
                        this->_right_rotate(x->parent);
                        x = this->_root;
                    }
                }
            }
            x->color = node_type::BLACK;
        }

    };

};
