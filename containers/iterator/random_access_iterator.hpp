#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "./iterator.hpp"
#include "./iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator: public ft::iterator<ft::random_access_iterator_tag, T>
	{
	
	public:

		// member types

		typedef typename ft::iterator_traits< ft::iterator<ft::random_access_iterator_tag, T> >::difference_type difference_type;
		typedef typename ft::iterator_traits< ft::iterator<ft::random_access_iterator_tag, T> >::value_typevalue_type;
		typedef typename ft::iterator_traits< ft::iterator<ft::random_access_iterator_tag, T> >::pointer pointer;
		typedef typename ft::iterator_traits< ft::iterator<ft::random_access_iterator_tag, T> >::reference reference;
		typedef typename ft::iterator_traits< ft::iterator<ft::random_access_iterator_tag, T> >::iterator_category iterator_category;

		// constructors

		random_access_iterator();

		random_access_iterator(const random_access_iterator & x);

		// destructor

		~random_access_iterator();

		// operators

		random_access_iterator & operator=(const random_access_iterator & x);

		random_access_iterator & operator+=(difference_type n);

		random_access_iterator & operator-=(difference_type n);

		reference operator*() const;

		pointer operator->();

		reference operator[](int i);

		random_access_iterator& operator++();

		random_access_iterator operator++(int);

		random_access_iterator& operator--();

		random_access_iterator operator--(int);

	private:

		pointer _ptr;

	};
}


#endif
