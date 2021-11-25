#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{

	template <class Iterator>
	class reverse_iterator
		: ft::iterator<	typename ft::iterator_traits<Iterator>::iterator_category,
						typename ft::iterator_traits<Iterator>::value_type,
						typename ft::iterator_traits<Iterator>::difference_type,
						typename ft::iterator_traits<Iterator>::pointer,
						typename ft::iterator_traits<Iterator>::reference>
	{

	public:

		// member types

		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;

		// constructors

		reverse_iterator()
			: _it()
		{}

		explicit reverse_iterator(iterator_type it)
			: _it(it)
		{}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it)
			: _it(rev_it.base())
		{}

		// member functions

		iterator_type base() const
		{
			return this->_iter;
		}

		// member operators

		reference operator*() const
		{
			iterator_type tmp = this->_it;
			return *(--tmp);
		}

		pointer operator->() const
		{
			return &this->operator*();
		}

		reverse_iterator& operator++()
		{
			--(this->_it);
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--(this->_it);
			return tmp;
		}

		reverse_iterator& operator--()
		{
			++(this->_it);
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++(this->_it);
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->_it - n);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->_it -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_it + n);
		}

		reverse_iterator& operator-=(difference_type n)
		{
			this->_it += n;
			return *this;
		}

		reference operator[] (difference_type n) const
		{
			return *(*this + n);
		}

	private:

		iterator_type _it;

	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() == rhs.base();
	}


	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() != rhs.base();
	}


	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() > rhs.base();
	}


	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() >= rhs.base();
	}


	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

}

#endif
