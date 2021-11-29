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
			RB_ND = 0,
			RB_RED = 1,
			RB_BLACK = 2
		};

		T * data;
		rbnode * parent;
		rbnode * left_child;
		rbnode * right_child;
		rbnode::color color;

		rbnode(rbnode * parent)
			: data(nullptr), parent(parent), left_child(nullptr), right_child(nullptr), color(RB_BLACK)
		{}

		~rbnode()
		{}

	};

}

#endif
