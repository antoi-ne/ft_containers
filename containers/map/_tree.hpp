#ifndef _FT_TREE_HPP
#define _FT_TREE_HPP

#include <functional>
#include <memory>

namespace ft
{

	template <class Type>
	struct _node
	{
		typedef Type value_type;

		value_type value;
		_node * right;
		_node * left;
		_node * parent;

		_node(value_type value)
			: value(value), right(nullptr), left(nullptr), parent(nullptr)
		{}

		~_node()
		{}
	};

	template <class Type, class Allocator>
	_node<Type> * _make_node(Type value, Allocator alloc)
	{
		_node<Type> * node;

		node = alloc.allocate(1);
		alloc.construct(node, _node(value));
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

		typedef _node<value_type> node_type;

		// constructors

		_tree(value_compare comp)
			: _comp(comp), _alloc(), _root(nullptr)
		{}

		// destructors

		~_tree()
		{}

		// accessors

		size_t size() const
		{
			return this->_sizeNode(this->_root);
		}

		node_type * search(value_type key)
		{
			return this->_searchTree(this->_root, key);
		}

		node_type * minimum()
		{
			return this->_minimum(this->_root);
		}

		node_type * maximum()
		{
			return this->_maximum(this->_root);
		}

		// modifiers

		node_type * insert(value_type key)
		{
			node_type * node = this->search(key)
			if (node != nullptr)
				return node;

			node = _make_node(key, this->_node_alloc);
			node_type * cursor = this->_root;
			node_type * parent = nullptr;

			while (cursor != nullptr)
			{
				parent = cursor
				if (this->_comp(node->value, cursor->value))
					cursor = cursor->left;
				else
					cursor = cursor->right;
			}

			node->parent = parent;
			if (parent == nullptr)
				this->_root = node;
			else if (this->_comp(node->value, parent->value))
				parent->left = node;
			else
				parent->right = node;
			return node;
		}

		size_t erase(value_type key)
		{
			return this->_eraseNode(this->_root, key) != NULL;
		}

	private:

		value_compare _comp;
		allocator_type _alloc;
		typename allocator_type::template rebind<node_type>::other _node_alloc;
		node_type * _root;

		node_type * _minimum(node_type * node)
		{
			while (node->left)
				node = node->left
			return node;
		}

		node_type * _maximum(node_type * node)
		{
			while (node->right)
				node = node->right
			return node;
		}

		node_type * _searchTree(node_type * node, value_type key)
		{
			if (this->_root == nullptr)
				return nullptr;
			if (this->_comp(key, node->value))
				return this->_searchTree(node->left, key);
			else
				return this->_searchTree(node->right, key);
		}

		node_type * _eraseNode(node_type * node, value_type key)
		{
			if (node == nullptr)
				return node;
			else if (this->_comp(key, node->value))
				node->left = this->_eraseNode(node->left, key);
			else if (this->_comp(node->value, key))
				node->right = this->_eraseNode(node->right, key);
			else
			{
				if (node->left == nullptr && node->right == nullptr)
				{
					this->_alloc.destroy(&node->value);
					this->_node_alloc.deallocate(node, 1);
				}
				else if (node->right == nullptr)
				{
					node_type * tmp = node;
					node = node->left;
					this->_alloc.destroy(&tmp->value);
					this->_node_alloc.deallocate(tmp, 1);
				}
				else if (node->left == nullptr)
				{
					node_type * tmp = node;
					node = node->right;
					this->_alloc.destroy(&tmp->value);
					this->_node_alloc.deallocate(tmp, 1);
				}
				else
				{
					node_type * tmp = this->_minimum(node->right);
					node->value = tmp->value;
					node->right = this->_eraseNode(node->right, tmp->value);
				}
			}
			return node;
		}

		size_t _sizeNode(node_type * node) const
		{
			size_t s = 0;
			if (node != nullptr)
			{
				s += this->_sizeNode(node->left);
				s += this->_sizeNode(node->right);
			}
			return s;
		}

	};

}

#endif
