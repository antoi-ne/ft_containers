#include <iostream>

#include <vector>
//#include <iterator>

#include "containers/iterator/wrap_iter.hpp"
#include "containers/iterator/reverse_iterator.hpp"
#include "containers/vector/vector.hpp"

int main(void)
{
	std::vector<int> vect;

	vect.insert(vect.begin(), 3);
	vect.push_back(10);
	vect.push_back(5);
	vect.insert(vect.begin()+2, 42);
	std::cout << "size: " << vect.size() << std::endl;
	for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); it++)
	{
		std::cout << "[" << *it << "]" << std::endl;
	}
	vect.pop_back();
	vect.clear();
}
