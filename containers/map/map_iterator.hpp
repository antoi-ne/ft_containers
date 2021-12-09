#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <iterator>

namespace ft
{
	template <typename T>
	class map_iterator
	{
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;
	};
}

#endif
