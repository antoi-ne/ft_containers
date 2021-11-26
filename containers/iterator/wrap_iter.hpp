#ifndef FT_ITERATOR_WRAPPER_HPP
#define FT_ITERATOR_WRAPPER_HPP

#include "./iterator.hpp"
#include "./iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	class wrap_iter
	{
	
	public:

		// member types

		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;

		// constructors

		wrap_iter()
			: _it()
		{}

		wrap_iter(iterator_type it)
			: _it(it)
		{}

		wrap_iter(const wrap_iter & x)
			: _it(x.base())
		{}

		template <class U>
		wrap_iter(const wrap_iter<U>& it)
			: _it(it.base())
		{}

		// destructor

		~wrap_iter()
		{}

		// member functions

		iterator_type base() const
		{
			return this->_it;
		}

		// operators

		template< class U >
		wrap_iter& operator=( const wrap_iter<U>& other )
		{
			this->_it = other.base();
			return *this;
		}

		reference operator*() const
		{
			return *this->_it;
		}

		pointer operator->()
		{
			return this->_it;
		}

		wrap_iter& operator++()
		{
			++this->_it;
			return *this;
		}

		wrap_iter operator++(int)
		{
			wrap_iter tmp(*this);
			++(*this);
			return tmp;
		}

		wrap_iter& operator--()
		{
			--this->_it;
			return *this;
		}

		wrap_iter operator--(int)
		{
			wrap_iter tmp(*this);
			--(*this);
			return tmp;
		}

		wrap_iter operator+(difference_type n) const
		{
			wrap_iter w(*this);
			w += n;
			return w;
		}

		wrap_iter & operator+=(difference_type n)
		{
			this->_it += n;
			return *this;
		}

		wrap_iter operator-(difference_type n) const
		{
			return *this + (-n);
		}

		wrap_iter & operator-=(difference_type n)
		{
			this->_it -= n;
			return *this;
		}

		reference operator[](int i)
		{
			return this->_it[i];
		}

		// non-member arithmetic operators

		//friend bool operator==(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() == b.base();
		//}

		//friend bool operator<(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() < b.base();
		//}

		//friend bool operator!=(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() != b.base();
		//}

		//friend bool operator>(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() > b.base();
		//}

		//friend bool operator>=(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() >= b.base();
		//}

		//friend bool operator<=(const wrap_iter & a, const wrap_iter & b)
		//{
		//	return a.base() <= b.base();
		//}

		//// non-member relational operators

		//friend difference_type operator-(const wrap_iter &a, const wrap_iter &b)
		//{
		//	return a.base() - b.base();
		//}

		//friend wrap_iter operator+(difference_type n, wrap_iter x)
		//{
		//	x += n;
		//	return x;
		//}

	private:

		iterator_type _it;

	};

	template<typename T>
	inline bool
	operator==(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator==(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T>
	inline bool
	operator!=(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator!=(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T>
	inline bool
	operator<(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator<(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename T>
	inline bool
	operator>(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator>(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T>
	inline bool
	operator<=(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator<=(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T>
	inline bool
	operator>=(const wrap_iter<T> &lhs, const wrap_iter<T> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T, typename U>
	inline bool
	operator>=(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	inline wrap_iter<T>
	operator+(typename wrap_iter<T>::difference_type n, const wrap_iter<T> &it)
	{
		return (wrap_iter<T>(it.base() + n));
	}

	template<typename T, typename U>
	inline typename wrap_iter<T>::difference_type
	operator-(const wrap_iter<T> &lhs, const wrap_iter<U> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

}

#endif
