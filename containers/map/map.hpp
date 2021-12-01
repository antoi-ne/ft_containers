#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "rbtree.hpp"
#include "pair.hpp"

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

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		// member classes

		class value_compare;

		// constructors

		map();
		
		explicit map(const Compare& comp, const Allocator& alloc = Allocator());

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());

		map(const map& other);

		// destructor

		~map();

		// element access

		T& at(const Key& key);

		const T& at(const Key& key) const;

		T& operator[](const Key& key);

		// capacity

		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		// modifiers

		void clear();

		void swap(map& other);
	
	private:

		rbtree<value_type, key_compare, allocator_type> _tree;

	};

}

#endif
