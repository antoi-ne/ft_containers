#ifndef FT_RBTREE_HPP
#define FT_RBTREE_HPP

#include <functional>
#include <memory>
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
			this->_node_alloc.construct(this->_leaf);
			this->_root = this->_leaf;
		}

		// destructors

		~rbtree()
		{}

		// modifiers

		void insert(T key)
		{}

		void remove(T key)
		{}

		// accessors

		T & find(T key)
		{}

	private:

		typename Alloc::template rebind<rbnode>::other _node_alloc;
		ft::rbnode<T> * _leaf;
		ft::rbnode<T> * _root;
		Alloc _alloc;
		Compare _compare;

	};

}

#endif
