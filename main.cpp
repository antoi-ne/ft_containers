#include <iostream>

#include <vector>
#include <map>
#include <iterator>
#include <chrono>
#include <memory>

#include "containers/map2/_rbtree.hpp"
#include "containers/map2/map.hpp"

int main(void)
{

    ft::_rbtree<int> rbt;

	rbt.insert(8);
	rbt.insert(18);
	rbt.insert(5);
	rbt.insert(15);
	rbt.insert(17);
	rbt.insert(25);
	rbt.insert(40);
	rbt.insert(80);
	rbt.prettyPrint();
}
