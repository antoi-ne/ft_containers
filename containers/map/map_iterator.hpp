#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <iterator>
#include <map.hpp>
#include <_tree.hpp>

namespace ft
{

	template <typename T>
	class map_iterator
	{
	public:

		// member types

		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef _node<T> node_type;

		// constructors

		map_iterator()
			: _root(nullptr), _ptr(nullptr)
		{}

		map_iterator(node_type * root, node_type * ptr)
			: _root(root), _ptr(ptr)
		{}

		// destructor

		~map_iterator()
		{}

		// assignation operator

		map_iterator & operator=(const map_iterator& rhs)
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
			return (this->_ptr->value);
		}

		pointer operator->()
		{
			return &(this->_ptr->value);
		}

		map_iterator& operator++()
		{
			this->_ptr = this->_forward(this->_ptr);
			return *this;
		}

		map_iterator operator++(int)
		{
			map_iterator<T> tmp(*this);
			this->operator++();
			return tmp;
		}

		map_iterator& operator--()
		{
			this->_ptr = this->_backward(this->_ptr);
			return *this;
		}

		map_iterator operator--(int)
		{
			map_iterator<T> tmp(*this);
			this->operator--();
			return tmp;
		}

		// nom-member operators overloads

		friend bool operator!=(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value != b._ptr.value);
		}

		friend bool operator==(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value == b._ptr.value);
		}

		friend bool operator<=(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value <= b._ptr.value);
		}

		friend bool operator>=(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value >= b._ptr.value);
		}

		friend bool operator<(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value < b._ptr.value);
		}

		friend bool operator>(const map_iterator& a, const map_iterator& b)
		{
			return (a._ptr.value > b._ptr.value);
		}

	private:

		node_type * _root;
		node_type * _ptr;

		node_type * _forward(node_type * ptr)
		{
			
			if (this->_ptr->right)
			{
				this->_ptr = this->_ptr->right;
				while (this->_ptr->left)
				{
					this->_ptr = this->_ptr->left;
				}
				return this->_ptr;
			}
			else
			{
				node_type *n = this->_ptr;
				this->_ptr = n->_parent;
				while (this->_ptr->left != n)
				{
					n = this->_ptr;
					this->_ptr = this->_ptr->parent;
				}
				return this->_ptr;
			}
		}

		node_type * _backward(node_type * ptr)
		{
			if (this->_ptr)
				{
					if (this->_ptr->left)
					{
						this->_ptr = this->_ptr->left;
						while (this->_ptr && this->_ptr->right)
						{
							this->_ptr = this->_ptr->right;
						}
					}
					else
					{
						node_type *n = this->_ptr;
						while (this->_ptr && this->_ptr->right != n)
						{
							n = this->_ptr;
							this->_ptr = this->_ptr->parent;
						}
					}
				}
				else
				{
					this->_ptr = this->_root;
					while (this->_ptr && this->_ptr->right)
					{
						this->_ptr = this->_ptr->right;
					}
				}
				return this->_ptr;
		}

	};

}

#endif
