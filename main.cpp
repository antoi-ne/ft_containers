//#include "containers/vector/vector.hpp"

#include "containers/iterator/iterator_wrapper.hpp"

#include <vector>
#include <iostream>
#include <iterator>

int main(void)
{
	std::iterator_traits<ft::wrap_iter<int *> >::value_type x;
	(void)x;
}
