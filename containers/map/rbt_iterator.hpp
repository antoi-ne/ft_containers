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



	};

}


#endif
