#ifndef _FT_TREE_HPP
#define _FT_TREE_HPP

#include <functional>
#include <memory>

namespace ft
{

	template <class Type, class Compare, class Allocator>
	struct _node
	{
		typedef Type value_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;

		value_type _value;
		_node * _right;
		_node * _left;
		value_compare _comp;

		_node(value_type value)
			: _value(value), _right(nullptr), _right(nullptr)
		{}

		~_node()
		{}
	};

	template <class Type, class Compare, class Allocator>
	_node<Type, Compare, Allocator> * _make_node(Type value, Compare comp, Allocator alloc)
	{
		_node<Type, Compare, Allocator> * node;

		node = alloc.allocate(1);
		alloc.construct(node, _node<Type, Compare, Allocator>(value));
		return node;
	}

	template <class Type, class Compare = std::less<Type>, class Allocator = std::allocator<Type> >
	class _tree
	{

	public:

		// member types

		typedef Type value_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;

		typedef _node<value_type, value_compare, allocator_type> node_type;

		// constructors

		_tree()
			: _comp(), _alloc(), _root(nullptr)
		{}

		// destructors

		~_tree()
		{}

		// accessors

		node_type * search(value_type key)
		{}

		// modifiers

		void insert(value_type key)
		{}

	private:

		value_compare _comp;
		allocator_type _alloc;
		node_type * _root;

	};

}

#endif
