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
	ft::rbtree<int> bst;

	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.remove(25);
	bst.print();
}
