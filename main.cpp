#include <iostream>

#include <vector>
#include <map>
//#include <iterator>
#include <iterator>

#include "containers/iterator/wrap_iter.hpp"
#include "containers/iterator/reverse_iterator.hpp"
#include "containers/vector/vector.hpp"
// #include "containers/map/rbtree.hpp"
// #include "containers/map/map.hpp"

int main(void)
{
	std::map<int, int> v;

	std::map<int, int>::iterator it1 =  v.begin();
	std::map<int, int>::const_iterator it2 =  v.begin();

	if (it1 == it2)
		std::cout << "hey" << std::endl;

	// ft::rbtree<int> bst = ft::rbtree<int>();

	// bst.insert(8);
	// bst.insert(18);
	// bst.insert(5);
	// bst.insert(15);
	// bst.insert(17);
	// bst.insert(25);
	// bst.insert(40);
	// bst.insert(80);
	// bst.remove(25);
	// bst.print();
}
