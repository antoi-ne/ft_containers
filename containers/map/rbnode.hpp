#ifndef FT_RBNODE_HPP
#define FT_RBNODE_HPP

namespace ft
{

	enum rbcolor
	{
			RED,
			BLACK
	};

	template <class T>
	class rbnode
	{

	public:

		T data;
		rbnode * parent;
		rbnode * left_child;
		rbnode * right_child;
		rbcolor color;
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
