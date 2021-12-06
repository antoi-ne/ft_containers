#ifndef FT_RB_TREE_ITERATOR_HPP
#define FT_RB_TREE_ITERATOR_HPP

#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "rbnode.hpp"
#include "rbtree.hpp"

namespace ft
{

	template <class T>
	class rbt_iterator: public ft::iterator<std::bidirectional_iterator_tag, T>
	{

	public:

		// member types

		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		// constructors

		rbt_iterator()
			: _root(nullptr), _ptr(nullptr)
		{}

		rbt_iterator(rbnode<T> * root, rbnode<T> * ptr)
			: _root(root), _ptr(ptr)
		{}

		// destructor

		~rbt_iterator()
		{}

		// assignation operator

		rbt_iterator & operator=(const rbt_iterator& rhs)
		{
			if (this != &rhs)
			{
				this->_root = rhs._root;
				this->_ptr = rhs._ptr;
			}
			return *this;
		}

		// member operators overloads

		reference operator*()
		{
			return (this->_ptr->data);
		}

		pointer operator->()
		{
			return &(this->_ptr->data);
		}

		rbt_iterator& operator++()
		{
			this->_ptr = this->_forward(this->_ptr);
			return *this;
		}

		rbt_iterator operator++(int)
		{
			rbt_iterator<T> tmp(*this);
			this->operator++();
			return tmp;
		}

		rbt_iterator& operator--()
		{
			this->_ptr = this->_backward(this->_ptr);
			return *this;
		}

		rbt_iterator operator--(int)
		{
			rbt_iterator<T> tmp(*this);
			this->operator--();
			return tmp;
		}

		// nom-member operators overloads

		friend bool operator!= (const TreeIterator& a, const TreeIterator& b)
		{
			return (a._ptr != b._ptr);
		}

		friend bool operator== (const TreeIterator& a, const TreeIterator& b)
		{
			return (a._ptr == b._ptr);
		}

		friend bool operator<= (const TreeIterator& a, const TreeIterator& b)
		{
			return (a._ptr <= b._ptr);
		}

		friend bool operator>= (const TreeIterator& a, const TreeIterator& b)
		{
			return (a._ptr >= b._ptr);
		}

		friend bool operator< (const TreeIterator& a, const TreeIterator& b)
		{
			return (a.getNode() < b.getNode()); 
		}

		friend bool operator> (const TreeIterator& a, const TreeIterator& b)
		{
			return (a._ptr > b._ptr); 
		}

	private:

		rbnode<T> * _root;
		rbnode<T> * _ptr;

		rbnode<T> * _forward(rbnode<T> * ptr)
		{
			if (ptr && ptr->right_child && !ptr->right_child->is_leaf())
			{
				while (ptr->left_child && !ptr->left_child->is_leaf())
					ptr = ptr->left_child;
			}
			else
			{
				rbnode<T> * leaf = ptr->right_child;
				rbnode<T> * p = ptr->parent;
				while (p && !p->is_leaf() && ptr == p->right_child)
				{
					ptr = p;
					p = p->parent;
				}
				ptr = p;
				if (ptr == nullptr)
					return leaf;
			}
			return ptr;
		}

		rbnode<T> * _backward(rbnode<T> * ptr)
		{
			if (ptr->is_leaf())
			{
				if (!this->_root->is_leaf())
				{
					while (ptr->right_child && !ptr->right_child->is_leaf())
						ptr = ptr->right_child;
				}
			}
			else if (ptr->left_child && !ptr->left_child->is_leaf())
			{
				while (ptr->right_child && !ptr->right_child->is_leaf())
					ptr = ptr->right_child;
			}
			else
			{
				rbnode<T> * leaf = ptr->left_child;
				rbnode<T> * p = ptr->parent;
				while (p && !p->is_leaf() && ptr == p->left_child)
				{
					ptr = p;
					p = p->parent;
				}
				ptr = p;
				if (ptr == nullptr)
					return leaf;
			}
			return ptr;
		}

	};

}

#endif
