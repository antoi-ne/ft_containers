#ifndef FT_RBTREE_HPP
#define FT_RBTREE_HPP

#include <functional>
#include <memory>
#include "pair.hpp"
#include "rbnode.hpp"

namespace ft
{

	template <class T, class Compare = std::less<T>, class Alloc = std::all >
	class RBTree
	{

	public:

	private:

		rbnode<T> * _root;

	}

}

#endif
