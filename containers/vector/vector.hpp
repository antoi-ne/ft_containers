#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include "../iterator/iterator.hpp"

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
		// member types

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		// constructors

		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _size(0)
		{
			this->_sequence = this->_alloc.allocate(this->_capacity);
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(n), _size(n)
		{
			this->_sequence = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&(this->_sequence[i]), val);
		}

		//template <class InputIterator>
		//vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());

		vector(const vector &x)
			: _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
		{
			this->_sequence = this->alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&(this->_sequence[i]), x._sequence[i]);
		}

		// destructor

		~vector()
		{}

		// assignation operator

		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;
			return *this;
		}

		// Capacity

		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return this->_alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type());

		size_type capacity() const
		{
			return this->_capacity;
		}

		bool empty() const
		{
			return this->_size == 0;
		}

		void reserve(size_type n);

		// element access

		reference operator[](size_type n);
		const_reference operator[](size_type n) const;

		reference at(size_type n);
		const_reference at(size_type n) const;

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

	private:
		allocator_type _alloc;
		size_type _size;
		size_type _capacity;
		pointer _sequence;
	};

}

#endif
