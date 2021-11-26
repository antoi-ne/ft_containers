#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "../iterator/wrap_iter.hpp"
#include "../iterator/reverse_iterator.hpp"


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
		typedef typename ft::wrap_iter<pointer> iterator;
		typedef typename ft::wrap_iter<const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// constructors

		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0), _sequence(nullptr)
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

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: _sequence(nullptr), _capacity(last - first), _size(last - first), _alloc(alloc)
		{
			this->_sequence = this->_alloc.allocate(this->_capacity);
			difference_type i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				this->_alloc.construct(&(this->_sequence[i]), *it);
				i++;
			}
		}

		vector(const vector &x)
			: _alloc(x._alloc), _capacity(x._capacity), _size(x._size)
		{
			this->_sequence = this->alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&(this->_sequence[i]), x._sequence[i]);
		}

		// destructor

		~vector()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&(this->_sequence[i]));
			this->_alloc.deallocate(this->_sequence, this->_capacity);
		}

		// iterators

		iterator begin()
		{
			return iterator(this->_sequence);
		}

		const_iterator begin() const
		{
			return const_iterator(this->_sequence);
		}

		iterator end()
		{
			return iterator(this->_sequence + this->_size);
		}

		const_iterator end() const
		{
			return const_iterator(this->_sequence + this->_size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->begin());
		}

		// assignation operator

		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				// TODO
			}
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

		void resize(size_type n, value_type val = value_type())
		{
			(void)val;
			if (n < this->size())
			{
				// TODO
			}
			else if (n > this->size() && n <= this->capacity())
			{
				// TODO
			}
			else if (n > this->size() && n > this->capacity())
			{
				// TODO
			}
		}

		size_type capacity() const
		{
			return this->_capacity;
		}

		bool empty() const
		{
			return this->_size == 0;
		}

		void reserve(size_type n)
		{
			if (n > this->size())
			{
				this->_realloc(n);
				this->_capacity = n;
			}
		}

		// element access

		reference operator[](size_type n)
		{
			return this->_sequence[n];
		}

		const_reference operator[](size_type n) const
		{
			return this->_sequence[n];
		}

		reference at(size_type n)
		{
			if (n >=0 && n < this->size())
				return this->_sequence[n];
			else
				throw std::out_of_range("vector");
		}

		const_reference at(size_type n) const
		{
			if (n >=0 && n < this->size())
				return this->_sequence[n];
			else
				throw std::out_of_range("vector");
		}

		reference front()
		{
			return this->_sequence[0];
		}
	
		const_reference front() const
		{
			return this->_sequence[0];
		}

		reference back()
		{
			return this->_sequence[this->size() - 1];
		}

		const_reference back() const
		{
			return this->_sequence[this->size() - 1];
		}

		// modifiers

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);

		void assign(size_type n, const value_type& val);

		void push_back(const value_type& val)
		{
			if (this->size() == this->capacity())
				this->reserve(this->size() == 0 ? 1 : this->size() * 2);
			++(this->_size);
			this->back() = val;
		}

		void pop_back()
		{
			if (this->size > 0)
			{
				_alloc.destroy(&(this->back()));
				--(this->size);
			}
		}

		iterator insert(iterator position, const value_type& val)
		{
			if (this->size() == this->capacity())
				this->reserve(this->size() == 0 ? 1 : this->size() * 2);

			iterator it = this->end();
			for (; it != position; it--)
			{
				*it = *(it - 1);
			}
			*it = val;
		}

		void insert(iterator position, size_type n, const value_type& val);

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last)
		{
			if (first != last)
			{
				//pointer start = this->_sequence + (first - this->begin());

			}
			return iterator(first);
		}

		void swap(vector& x)
		{
			allocator_type tmp_alloc = this->_alloc;
			size_type tmp_size = this->_size;
			size_type tmp_capacity = this->_capacity;
			pointer tmp_sequence = this->_sequence;

			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_sequence = x._sequence;

			x._alloc = tmp_alloc;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
			x._sequence = tmp_sequence;
		}

		void clear()
		{
			while (this->_size > 0)
				this->pop_back();
		}

		// allocator

		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

	private:
		allocator_type _alloc;
		size_type _size;
		size_type _capacity;
		pointer _sequence;

		void _realloc(size_type n)
		{
			pointer new_seq = this->_alloc.allocate(n);

			for (size_type i = 0; i < this->size(); i++)
				_alloc.construct(&(new_seq[i]), this->_sequence[i]);

			this->~vector();
			this->_sequence = new_seq;
			this->capacity = n;
		}
	};

}

#endif
