#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{

	template <class Iterator>
	class reverse_iterator
	{

	public:

		// member types

		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		// constructors

		reverse_iterator()
			: _iter()
		{}

		explicit reverse_iterator(iterator_type it);

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it);

		// member functions

		iterator_type base() const
		{
			return this->_iter;
		}

		// member operators

		reference operator*() const;

		reverse_iterator operator+(difference_type n) const;

		reverse_iterator& operator++();

		reverse_iterator operator++(int);

		reverse_iterator& operator+=(difference_type n);

		reverse_iterator operator-(difference_type n) const;

		reverse_iterator& operator--();

		reverse_iterator operator--(int);

		reverse_iterator& operator-= (difference_type n);

		pointer operator->() const;

		reference operator[] (difference_type n) const;

	private:

		iterator_type _iter;

	};

}

#endif
