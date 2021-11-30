#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "rbtree.hpp"
#include "pair.hpp"

namespace ft
{

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map
	{

	};

}

#endif
