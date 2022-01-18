#ifndef FT_MAP_TREE_HPP
# define FT_MAP_TREE_HPP
// Original author: Algorithm Tutor
// Adapted by: ancoulon

#include <iostream>
#include <memory>
#include <utility>

using namespace std;

namespace ft
{
	template <typename Type>
	class node
	{
	public:
		Type data;
		node *parent;
		node *left;
		node *right;
		bool color; // false for black, true for red
		bool leaf;	// true if NULL node (leaf of the tree)
	};

	template <class Type, class Compare = std::less<Type>, class Alloc = std::allocator<Type> >
	class tree
	{
	public:
		typedef Type value_type;
		typedef node<value_type> node_type;
		typedef size_t size_type;
		typedef Alloc allocator_type;
		typedef Compare value_compare;

		tree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _comp(comp)
		{
			// creating the leaf node
			this->_leaf = this->_node_alloc.allocate(1);
			this->_leaf->left = nullptr;
			this->_leaf->right = nullptr;
			this->_leaf->color = 0;
			this->_leaf->leaf = true;

			// empty tree points to the leaf node
			this->_root = this->_leaf;
		}

		tree(const tree &rhs)
		{
			this->_node_alloc = rhs._node_alloc;
			this->_alloc = rhs._alloc;
			this->_comp = rhs._comp;

			this->_leaf = this->_node_alloc.allocate(1);
			this->_leaf->left = nullptr;
			this->_leaf->right = nullptr;
			this->_leaf->color = 0;
			this->_leaf->leaf = true;

			this->_root = this->_leaf;

			// todo
		}

		~tree()
		{
			// todo
			this->_node_alloc.deallocate(this->_leaf, 1);
		}

		tree &operator=(const tree &rhs)
		{
			if (this != &rhs)
			{
				this->_node_alloc = rhs._node_alloc;
				this->_alloc = rhs._alloc;
				this->_comp = rhs._comp;

				// todo
			}
			return *this;
		}

		// Pre-Order traversal
		// Node->Left Subtree->Right Subtree
		void preorder()
		{
			this->preOrderHelper(this->_root);
		}

		// In-Order traversal
		// Left Subtree -> Node -> Right Subtree
		void inorder()
		{
			this->inOrderHelper(this->_root);
		}

		// Post-Order traversal
		// Left Subtree -> Right Subtree -> Node
		void postorder()
		{
			this->postOrderHelper(this->_root);
		}

		// search the tree for the key k
		// and return the corresponding node
		node_type *searchTree(const value_type& k)
		{
			return this->searchTreeHelper(this->_root, k);
		}

		// find the node with the minimum key
		node_type *minimum(node_type *node)
		{
			while (node->left != this->_leaf)
			{
				node = node->left;
			}
			return node;
		}

		// find the node with the maximum key
		node_type *maximum(node_type *node)
		{
			while (node->right != this->_leaf)
			{
				node = node->right;
			}
			return node;
		}

		// find the successor of a given node
		node_type *successor(node_type *x)
		{
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right != this->_leaf)
			{
				return this->minimum(x->right);
			}

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x.
			node_type *y = x->parent;
			while (y != this->_leaf && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		node_type *predecessor(node_type *x)
		{
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the
			// left subtree
			if (x->left != this->_leaf)
			{
				return this->maximum(x->left);
			}

			node_type *y = x->parent;
			while (y != this->_leaf && x == y->left)
			{
				x = y;
				y = y->parent;
			}

			return y;
		}

		// rotate left at node x
		void leftRotate(node_type *x)
		{
			node_type *y = x->right;
			x->right = y->left;
			if (y->left != this->_leaf)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr)
			{
				this->_root = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		// rotate right at node x
		void rightRotate(node_type *x)
		{
			node_type *y = x->left;
			x->left = y->right;
			if (y->right != this->_leaf)
			{
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == nullptr)
			{
				this->_root = y;
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y;
			}
			else
			{
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		// insert the key to the tree in its appropriate position
		// and fix the tree
		node_type * insert(const value_type& key)
		{
			node_type * found = this->searchTree(key);
			if (found != this->_leaf)
				return found;

			// Ordinary Binary Search Insertion
			node_type *node = this->_node_alloc.allocate(1);
			node->parent = nullptr;
			node->data = key;
			node->left = this->_leaf;
			node->right = this->_leaf;
			node->color = true; // new node must be red
			node->leaf = false;

			node_type *y = nullptr;
			node_type *x = this->_root;

			while (x != this->_leaf)
			{
				y = x;
				if (this->_comp(node->data, x->data))
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			// y is parent of x
			node->parent = y;
			if (y == nullptr)
			{
				this->_root = node;
			}
			else if (this->_comp(node->data, y->data))
			{
				y->left = node;
			}
			else
			{
				y->right = node;
			}

			// if new node is a root node, simply return
			if (node->parent == nullptr)
			{
				node->color = false;
				return node;
			}

			// if the grandparent is null, simply return
			if (node->parent->parent == nullptr)
			{
				return node;
			}

			// Fix the tree
			this->fixInsert(node);
			return node;
		}

		node_type *getRoot()
		{
			return this->_root;
		}

		// delete the node from the tree
		void deleteNode(const value_type& data)
		{
			this->deleteNodeHelper(this->_root, data);
		}

		// print the tree structure on the screen
		void prettyPrint()
		{
			if (this->_root)
			{
				this->printHelper(this->_root, "", true);
			}
		}

	private:
		allocator_type _alloc;
		typename allocator_type::template rebind<node_type>::other _node_alloc;
		value_compare _comp;

		node_type * _root;
		node_type *_leaf;

		void preOrderHelper(node_type *node)
		{
			if (node != this->_leaf)
			{
				std::cout << node->data << " ";
				this->preOrderHelper(node->left);
				this->preOrderHelper(node->right);
			}
		}

		void inOrderHelper(node_type *node)
		{
			if (node != this->_leaf)
			{
				this->inOrderHelper(node->left);
				std::cout << node->data << " ";
				this->inOrderHelper(node->right);
			}
		}

		void postOrderHelper(node_type *node)
		{
			if (node != this->_leaf)
			{
				this->postOrderHelper(node->left);
				this->postOrderHelper(node->right);
				std::cout << node->data << " ";
			}
		}

		node_type *searchTreeHelper(node_type *node, const value_type& key)
		{
			if (node == this->_leaf ||  key == node->data)
			{
				return node;
			}

			if (this->_comp(key, node->data))
			{
				return this->searchTreeHelper(node->left, key);
			}
			return this->searchTreeHelper(node->right, key);
		}

		void fixDelete(node_type *x)
		{
			node_type *s;
			while (x != this->_root && x->color == 0)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == 1)
					{
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						this->leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == 0 && s->right->color == 0)
					{
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->right->color == 0)
						{
							// case 3.3
							s->left->color = 0;
							s->color = 1;
							this->rightRotate(s);
							s = x->parent->right;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->right->color = 0;
						this->leftRotate(x->parent);
						x = this->_root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == 1)
					{
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						this->rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == 0 && s->right->color == 0)
					{
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->left->color == 0)
						{
							// case 3.3
							s->right->color = 0;
							s->color = 1;
							this->leftRotate(s);
							s = x->parent->left;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						this->rightRotate(x->parent);
						x = this->_root;
					}
				}
			}
			x->color = 0;
		}

		void rbTransplant(node_type *u, node_type *v)
		{
			if (u->parent == nullptr)
			{
				this->_root = v;
			}
			else if (u == u->parent->left)
			{
				u->parent->left = v;
			}
			else
			{
				u->parent->right = v;
			}
			v->parent = u->parent;
		}

		void deleteNodeHelper(node_type *node, value_type key)
		{
			// find the node containing key
			node_type * z = this->_leaf;
			node_type * x,  * y;
			while (node != this->_leaf)
			{
				if (node->data == key)
				{
					z = node;
				}

				if (node->data <= key)
				{
					node = node->right;
				}
				else
				{
					node = node->left;
				}
			}

			if (z == this->_leaf)
			{
				std::cout << "Couldn't find key in the tree" << std::endl;
				return;
			}

			y = z;
			bool y_original_color = y->color;
			if (z->left == this->_leaf)
			{
				x = z->right;
				this->rbTransplant(z, z->right);
			}
			else if (z->right == this->_leaf)
			{
				x = z->left;
				this->rbTransplant(z, z->left);
			}
			else
			{
				y = this->minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					this->rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				this->rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			delete z;
			if (y_original_color == 0)
			{
				this->fixDelete(x);
			}
		}

		// fix the red-black tree
		void fixInsert(node_type *k)
		{
			node_type *u;
			while (k->parent->color == 1)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left; // uncle
					if (u->color == 1)
					{
						// case 3.1
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							// case 3.2.2
							k = k->parent;
							this->rightRotate(k);
						}
						// case 3.2.1
						k->parent->color = 0;
						k->parent->parent->color = 1;
						this->leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right; // uncle

					if (u->color == 1)
					{
						// mirror case 3.1
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							// mirror case 3.2.2
							k = k->parent;
							this->leftRotate(k);
						}
						// mirror case 3.2.1
						k->parent->color = 0;
						k->parent->parent->color = 1;
						this->rightRotate(k->parent->parent);
					}
				}
				if (k == this->_root)
				{
					break;
				}
			}
			this->_root->color = 0;
		}

		void printHelper(node_type *root, string indent, bool last)
		{
			// print the tree structure on the screen
			if (root != this->_leaf)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "     ";
				}
				else
				{
					std::cout << "L----";
					indent += "|    ";
				}

				string sColor = root->color ? "RED" : "BLACK";
				std::cout << root->data << "(" << sColor << ")" << std::endl;
				this->printHelper(root->left, indent, false);
				this->printHelper(root->right, indent, true);
			}
		}
	};
}

#endif
