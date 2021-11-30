#ifndef FT_RBTREE_HPP
#define FT_RBTREE_HPP

#include <functional>
#include <memory>
#include <iostream>
#include <string>
#include "rbnode.hpp"

namespace ft
{

	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class rbtree
	{

	public:

		// constructors

		rbtree()
			: _alloc(), _compare()
		{
			this->_leaf = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_leaf, rbnode<T>());
			this->_root = this->_leaf;
		}

		// destructors

		~rbtree()
		{}

		// modifiers

		void insert(T key)
		{
			rbnode<T> * new_node;
			rbnode<T> * ptr;
			rbnode<T> * parent;

			new_node = this->_make_node(key);

			ptr = this->_root;
			parent = nullptr;
			while (ptr != nullptr)
			{
				parent = ptr;
				if (new_node->data < parent->data)
					ptr = ptr->left_child;
				else
					ptr = ptr->right_child;
			}

			new_node->parent = parent;
			if (parent == nullptr)
				this->_root = new_node;
			else if (new_node->data < parent->data)
				parent->left_child = new_node;
			else
				parent->right_child = new_node;

			if (new_node->parent == nullptr)
			{
				new_node->color = rbnode<T>::BLACK;
				return;
			}

			if (new_node->parent->parent == nullptr)
				return;

			this->_fix_inserted(new_node);
		}

		//void remove(T key)
		//{}

		//// accessors

		//T & search(T key)
		//{

		//}

		void print()
		{
			this->_print_helper(this->_root, "", true);
		}

	private:

		typename Alloc::template rebind<rbnode<T> >::other _node_alloc;
		ft::rbnode<T> * _leaf;
		ft::rbnode<T> * _root;
		Alloc _alloc;
		Compare _compare;

		rbnode<T> * _make_node(T key)
		{
			rbnode<T> * node;

			node = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(node, rbnode<T>(key));

			return node;
		}

		void _print_helper(rbnode<T> * node, std::string ident, bool last)
		{
			if (node != this->_leaf)
			{
				std::cout << ident;
				if (last)
				{
					std::cout<<"R----";
					ident += "     ";
				}
				else
				{
					std::cout<<"L----";
					ident += "|    ";
				}

				std::string color_str = node->color == rbnode<T>::RED ? "RED" : "BLACK";
				std::cout << node->data << "(" << color_str << ")" << std::endl;
				this->_print_helper(node->left_child, ident, false);
				this->_print_helper(node->right_child, ident, true);
			}
		}

		void _left_rotate(rbnode<T> * node)
		{
			rbnode<T> * rc;

			rc = node->right_child;
			node->right_child = rc->left_child;
			if (rc->left_child != this->_leaf)
				rc->left_child->parent = node;
			rc->parent = node->parent;
			if (node->parent == nullptr)
				this->_root = rc;
			else if (node == node->parent->left_child)
				node->parent->left_child = rc;
			else
				node->parent->right_child = rc;
			rc->left_child = node;
			node->parent = rc;
		}

		void _right_rotate(rbnode<T> * node)
		{
			rbnode<T> * lc;

			lc = node->left_child;
			node->left_child = lc->right_child;
			if (lc->right_child != this->_leaf)
				lc->right_child->parent = node;
			lc->parent = node->parent;
			if (node->parent == nullptr)
				this->_root = lc;
			else if (node == node->parent->right_child)
				node->parent->right_child = lc;
			else
				node->parent->left_child = lc;
			lc->right_child = node;
			node->parent = lc;
		}

		void _fix_inserted(rbnode<T> * node)
		{
			rbnode<T> * uncle;

			while (node->parent->color == rbnode<T>::RED)
			{
				if (node->parent == node->parent->parent->right_child)
				{
					uncle = node->parent->left_child;

					if (uncle->color == rbnode<T>::RED)
					{
						uncle->color = rbnode<T>::BLACK;
						node->parent->color = rbnode<T>::BLACK;
						node->parent->parent->color = rbnode<T>::RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left_child)
						{
							node = node->parent;
							_right_rotate(node);
						}
						node->parent->color = rbnode<T>::BLACK;
						node->parent->parent->color = rbnode<T>::RED;
						_left_rotate(node->parent->parent);
					}
				}
				else
				{
					uncle = node->parent->right_child;

					if (uncle->color == rbnode<T>::RED)
					{
						uncle->color = rbnode<T>::BLACK;
						node->parent->color = rbnode<T>::BLACK;
						node->parent->parent->color = rbnode<T>::RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right_child)
						{
							node = node->parent;
							_left_rotate(node);
						}
						node->parent->color = rbnode<T>::BLACK;
						node->parent->parent->color = rbnode<T>::RED;
						_right_rotate(node->parent->parent);
					}
				}

				if (node == this->_root)
					break;
			}
			this->_root->color = rbnode<T>::BLACK;
		}

	};

}

#endif
