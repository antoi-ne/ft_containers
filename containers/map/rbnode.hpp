#ifndef FT_RBNODE_HPP
#define FT_RBNODE_HPP

namespace ft
{

	template <class T>
	class rbnode
	{

	public:

		enum color
		{
			RED = 0,
			BLACK = 1
		};

		T data;
		rbnode * parent;
		rbnode * left_child;
		rbnode * right_child;
		rbnode::color color;
		bool is_leaf;

		rbnode()
			: data(), parent(nullptr), left_child(nullptr), right_child(nullptr), color(BLACK), is_leaf(true)
		{}

		rbnode(T key)
			: data(key), parent(nullptr), left_child(nullptr), right_child(nullptr), color(RED), is_leaf(false)
		{}

		~rbnode()
		{}

	};

}

#endif
