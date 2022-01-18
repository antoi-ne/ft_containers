#include <iostream>

#include <vector>
#include <map>
#include <iterator>
#include <chrono>
#include <memory>


#include "containers/iterator/wrap_iter.hpp"
#include "containers/iterator/reverse_iterator.hpp"
#include "containers/vector/vector.hpp"
#include "containers/map_new/tree.hpp"


int main(void)
{
	ft::tree<int, std::less<int>, std::allocator<int> > rbt;

	rbt.insert(8);
	rbt.insert(18);
	rbt.insert(5);
	rbt.insert(15);
	rbt.insert(17);
	rbt.insert(25);
	rbt.insert(40);
	rbt.insert(80);
	rbt.deleteNode(25);
	rbt.prettyPrint();

}
