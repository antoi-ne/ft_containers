#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include "rbtree.hpp"
#include "pair.hpp"
#include "rbt_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

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
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::rbt_iterator<value_type> iterator;
		typedef typename ft::rbt_iterator<const value_type> iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// member class

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{

		protected:

			Compare comp;

			value_compare(Compare c)
				: comp(c)
			{}

			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return comp(lhs.first, rhs.first);
			}

		};

		// constructors

		map()
			: _tree()
		{}
		
		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
			: _tree()
		{}

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());

		map(const map& other);

		// destructor

		~map()
		{}

		// assignationn operator

		map& operator=(const map& other);

		// allocator

		allocator_type get_allocator() const;

		// element access

		T& at(const Key& key);

		const T& at(const Key& key) const;

		T& operator[](const Key& key);

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

		bool empty() const;

		size_type size() const;

		size_type max_size() const;

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

		size_type count(const Key& key) const;

		iterator find(const Key& key);

		const_iterator find(const Key& key) const;

		ft::pair<iterator,iterator> equal_range(const Key& key);

		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const;

		iterator lower_bound(const Key& key);

		const_iterator lower_bound(const Key& key) const;

		iterator upper_bound(const Key& key);

		const_iterator upper_bound(const Key& key) const;

		// observers

		key_compare key_comp() const;
	
		ft::map::value_compare value_comp() const;
	
	private:

		rbtree<value_type, key_compare, allocator_type> _tree;

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
