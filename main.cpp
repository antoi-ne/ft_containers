#include <iostream>

#include <vector>
#include <map>
//#include <iterator>
#include <iterator>

#include "containers/iterator/wrap_iter.hpp"
#include "containers/iterator/reverse_iterator.hpp"
#include "containers/vector/vector.hpp"
#include <chrono>


int main(void)
{
	std::map<int, int> x;

	// x.insert(std::make_pair(42, 420));
	// x.insert(std::make_pair(1, 10));
	// x.insert(std::make_pair(27, 270));
	// x.insert(std::make_pair(19, 190));

	std::map<int, int>::iterator it = x.end();
	std::cout << (it == x.begin()) << std::endl;
}
