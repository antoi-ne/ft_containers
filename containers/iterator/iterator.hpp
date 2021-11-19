#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <cstddef> // std::ptrdiff_t

namespace ft
{

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{

	public:
		typedef iterator_category Category;
		typedef value_type T;
		typedef difference_type Distance;
		typedef pointer Pointer;
		typedef reference Reference;
	};

}

#endif
