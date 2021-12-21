#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include "pair.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "_tree.hpp"
#include "map_iterator.hpp"

namespace ft
{



	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map
	{

	public:

		// member types

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::map_iterator<value_type> iterator;
		typedef typename ft::map_iterator<const value_type> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// member class

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{

		protected:

			key_compare comp;

			value_compare(key_compare c)
				: comp(c)
			{}

		public:

			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return this->comp(lhs.first, rhs.first);
			}

		};

		// constructors
		
		explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _alloc(alloc), _comp(comp), _tree(value_compare(comp), alloc)
		{}

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _alloc(alloc), _comp(comp), _tree(value_compare(comp), alloc)
		{}

		map(const map& other)
		{
			*this = other;
		}

		// destructor

		~map()
		{}

		// assignationn operator

		map& operator=(const map& other)
		{
			if (*this != other)
			{
				this->_alloc = other._alloc;
				this->_comp = other._comp;
				this->_tree = other._tree;
			}
			return *this;
		}

		// allocator

		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

		// element access

		T& at(const Key& key)
		{
			return this->_tree.search(key);
		}

		const T& at(const Key& key) const
		{
			return this->_tree.search(key);
		}

		T& operator[](const Key& key)
		{
			return this->_tree.search(key);
		}

		// iterators

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		reverse_iterator rbegin();

		const_reverse_iterator rbegin() const;

		reverse_iterator rend();

		const_reverse_iterator rend() const;

		// capacity

		bool empty() const
		{
			return this->_tree.size() == 0;
		}

		size_type size() const
		{
			return this->_tree.size();
		}

		size_type max_size() const
		{
			return this->_alloc.max_size();
		}

		// modifiers

		void clear();

		ft::pair<iterator, bool> insert(const value_type& value);

		iterator insert(iterator hint, const value_type& value);

		template<class InputIt>
		void insert(InputIt first, InputIt last);

		void erase(iterator pos);

		void erase(iterator first, iterator last);

		size_type erase(const Key& key);

		void swap(map& other);

		// lookup

		size_type count(const Key& key) const
		{
			return (this->_tree.search(key) == nullptr) ? 0 : 1;
		}

		iterator find(const Key& key);

		const_iterator find(const Key& key) const;

		ft::pair<iterator,iterator> equal_range(const Key& key);

		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const;

		iterator lower_bound(const Key& key);

		const_iterator lower_bound(const Key& key) const;

		iterator upper_bound(const Key& key);

		const_iterator upper_bound(const Key& key) const;

		// observers

		key_compare key_comp() const
		{
			return this->_comp;
		}
	
		value_compare value_comp() const
		{
			return value_compare(this->_comp);
		}
	
	private:

		allocator_type _alloc;
		key_compare _comp;
		_tree<value_type, value_compare, allocator_type> _tree;

	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs);

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs);

}

#endif