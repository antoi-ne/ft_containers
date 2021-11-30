#include <iostream>

#include <vector>
#include <map>
//#include <iterator>

#include "containers/iterator/wrap_iter.hpp"
#include "containers/iterator/reverse_iterator.hpp"
#include "containers/vector/vector.hpp"
#include "containers/map/rbtree.hpp"

int main(void)
{
	ft::rbtree<int> tree;

	tree.insert(4);
	//tree.insert(12);
	//tree.insert(0);
	//tree.insert(150);
	tree.print();
}
