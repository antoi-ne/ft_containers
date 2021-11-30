#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <iterator>
#include "../iterator/wrap_iter.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/compare.hpp"


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
			: _alloc(alloc), _size(n), _capacity(n)
		{
			this->_sequence = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&(this->_sequence[i]), val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			: _alloc(alloc), _size(0), _capacity(0), _sequence(nullptr)
		{
			this->_realloc(std::distance(first, last));
			this->_size = std::distance(first, last);
			difference_type i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				this->_alloc.construct(&(this->_sequence[i]), (*it));
				i++;
			}
		}

		vector(const vector &x)
			: _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			this->_sequence = this->_alloc.allocate(this->_capacity);
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
				this->clear();
				this->_alloc.deallocate(this->_sequence, this->capacity());
				this->_capacity = x.capacity();
				this->_size = x.size();
				this->_sequence = this->_alloc.allocate(x.capacity());

				for (size_type i = 0; i < this->size(); i++)
					this->_alloc.construct(&(this->_sequence[i]), x[i]);
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
			if (n < this->size())
			{
				while (n < this->size())
					this->pop_back();
			}
			else
			{
				for (size_type i = this->size(); i < n; i++)
					this->push_back(val);
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
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}

		void assign(size_type n, const value_type& val)
		{
			this->clear();
			while (n--)
				this->push_back(val);
		}

		void push_back(const value_type& val)
		{
			if (this->size() == this->capacity())
				this->reserve(this->size() == 0 ? 1 : this->size() * 2);
			++(this->_size);
			this->back() = val;
		}

		void pop_back()
		{
			if (this->size() > 0)
			{
				_alloc.destroy(&(this->back()));
				--(this->_size);
			}
		}

		iterator insert(iterator position, const value_type& val)
		{

			difference_type index = std::distance(this->begin(), position);

			if (this->size() == this->capacity())
				this->reserve(this->size() == 0 ? 1 : this->size() * 2);

			for (difference_type i = this->size(); i != index ; i--)
				this->_sequence[i] = this->_sequence[i - 1];
			this->_sequence[index] = val;
			++(this->_size);
			return iterator(&(this->_sequence[index]));
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			while (n--)
				position = insert(position, val) + 1;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			ft::vector<value_type> tmp(first, last);
			for (iterator it = tmp.begin(); it != tmp.end(); it++)
			{
				position = insert(position, *it) + 1;
			}
		}

		iterator erase(iterator position)
		{
			return (this->erase(position, position + 1));
		}

		iterator erase(iterator first, iterator last)
		{

			if (first != last)
			{
				iterator it = this->begin();
				size_type idx = 0;
				difference_type n = last - first;

				while (it + idx != first)
					idx++;
				while (it + idx != this->end() - n)
				{
					this->_sequence[idx] = this->_sequence[idx + n];
					idx++;
				}
				while (it + idx != this->end())
					this->_alloc.destroy(_sequence + idx++);
				this->_size -= n;
			}
			return (iterator(first));
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
			this->_capacity = n;
		}
	};

	// non-member operator overloads

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		size_t i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return (false);
			i++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return(!(lhs==rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ((lhs == rhs) || (lhs < rhs));
	}
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs) && !(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	// non-member functions

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif
