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

			while (ptr != this->_leaf)
			{
				parent = ptr;
				if (this->_compare(new_node->data, ptr->data))
					ptr = ptr->left_child;
				else
					ptr = ptr->right_child;
			}

			new_node->parent = parent;
			if (parent == nullptr)
				this->_root = new_node;
			else if (this->_compare(new_node->data, parent->data))
				parent->left_child = new_node;
			else
				parent->right_child = new_node;

			if (new_node->parent == nullptr)
			{
				new_node->color = BLACK;
				return;
			}

			if (new_node->parent->parent == nullptr)
				return;

			this->_fix_inserted(new_node);
		}

		void remove(T key)
		{
			rbnode<T> * node;
			rbnode<T> * ptr;
			rbnode<T> * x, * y;
			rbcolor yc;

			node = this->_root;
			ptr = this->_leaf;
			
			while (node != this->_leaf)
			{
				if (node->data == key)
					ptr = node;
				
				if (node->data <= key)
					node = node->right_child;
				else
					node = node->left_child;
			}

			if (ptr == this->_leaf)
				return;

			y = ptr;
			yc = y->color;
			if (ptr->left_child == this->_leaf)
			{
				x = ptr->right_child;
				this->_transplant(ptr, ptr->right_child);
			}
			else if (ptr->right_child == this->_leaf)
			{
				x = ptr->left_child;
				this->_transplant(ptr, ptr->left_child);
			}
			else
			{
				y = this->minimum(ptr->right_child);
				yc = y->color;
				x = y->right_child;
				if (y->parent == ptr)
					x->parent = y;
				else
				{
					this->_transplant(y, y->right_child);
					y->right_child = ptr->right_child;
					y->right_child->parent = y;
				}

				this->_transplant(ptr, y);
				y->left_child = ptr->left_child;
				y->left_child->parent = y;
				y->color = ptr->color;
			}
			delete ptr;
			if (yc == BLACK)
				this->_fix_remove(x);
			
		}

		// accessors

		rbnode<T> * minimum(rbnode<T> * node)
		{
			while (node->left_child != this->_leaf)
				node = node->left_child;
			return node;
		}

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
			node->left_child = this->_leaf;
			node->right_child = this->_leaf;

			return node;
		}

		void _print_helper(rbnode<T> * node, std::string ident, bool last)
		{
			if (node != this->_leaf)
			{
				std::cout << ident;
				if (last)
				{
					std::cout << "R----";
					ident += "     ";
				}
				else
				{
					std::cout << "L----";
					ident += "|    ";
				}

				std::string color_str = node->color == RED ? "RED" : "BLACK";
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

			while (node->parent->color == RED)
			{
				if (node->parent == node->parent->parent->right_child)
				{
					uncle = node->parent->parent->left_child;

					if (uncle->color == RED)
					{
						uncle->color = BLACK;
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left_child)
						{
							node = node->parent;
							_right_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_left_rotate(node->parent->parent);
					}
				}
				else
				{
					uncle = node->parent->parent->right_child;

					if (uncle->color == RED)
					{
						uncle->color = BLACK;
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right_child)
						{
							node = node->parent;
							_left_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_right_rotate(node->parent->parent);
					}
				}

				if (node == this->_root)
					break;
			}
			this->_root->color = BLACK;
		}

		void _transplant(rbnode<T> * u, rbnode<T> * v)
		{
			if (u->parent == nullptr)
				this->_root = v;
			else if (u == u->parent->left_child)
				u->parent->left_child = v;
			else
				u->parent->right_child = v;
			v->parent = u->parent;
		}

		void _fix_remove(rbnode<T> * node)
		{
			rbnode<T> * s;

			while (node != this->_root && node->color == BLACK)
			{
				if (node == node->parent->left_child)
				{
					s = node->parent->right_child;
					if (s->color == RED)
					{
						s->color = BLACK;
						node->parent->color = RED;
						this->_left_rotate(node->parent);
						s = node->parent->right_child;
					}

					if (s->left_child->color == BLACK && s->right_child->color == BLACK)
					{
						s->color = RED;
						node = node->parent;
					}
					else
					{
						if (s->right_child->color == 0)
						{
							s->left_child->color = BLACK;
							s->color = RED;
							this->_right_rotate(s);
							s = node->parent->right_child;
						}

						s->color = node->parent->color;
						node->parent->color = BLACK;
						s->right_child->color = BLACK;
						this->_left_rotate(node->parent);
						node = this->_root;
					}
				}
				else
				{
					s = node->parent->left_child;
					if (s->color == RED)
					{
						s->color = BLACK;
						node->parent->color = RED;
						this->_right_rotate(node->parent);
						s = node->parent->left_child;
					}

					if (s->right_child->color == BLACK && s->right_child->color == BLACK)
					{
						s->color = RED;
						node = node->parent;
					}
					else
					{
						if (s->left_child->color == BLACK)
						{
							s->right_child->color = BLACK;
							s->color = RED;
							this->_left_rotate(s);
							s = node->parent->left_child;
						}

						s->color = node->parent->color;
						node->parent->color = BLACK;
						s->left_child->color = BLACK;
						this->_right_rotate(node->parent);
						node = this->_root;
					}
				}
			}
			node->color = BLACK;
		}

	};

}

#endif
