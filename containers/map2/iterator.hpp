#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <functional>
#include <memory>

#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../utils/pair.hpp"

namespace ft
{
    template <class Type, class Compare = std::less<Type> >
    class map_iterator: ft::iterator<std::bidirectional_iterator_tag, Type>
    {};
}

#endif
