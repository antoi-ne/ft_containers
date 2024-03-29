#ifndef FT_MAP_MAP_HPP
#define FT_MAP_MAP_HPP

#include <functional>
#include <memory>

#include "../utils/pair.hpp"
#include "./_rbtree.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    public:

        // member types

        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const Key, T>                      value_type;
        typedef Compare                                     key_compare;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

        // member classes

        class value_compare: public std::binary_function<value_type, value_type, bool>
        {

        protected:

            key_compare comp;

        public:

            value_compare(key_compare c)
                : comp(c)
            {}

            bool operator()(const value_type& lhs, const value_type& rhs) const
            {
                return this->comp(lhs.first, rhs.first);
            }

        };

    private:

        allocator_type                                      _alloc;
        key_compare                                         _key_comp;
        value_compare                                       _value_comp;
        _rbtree<value_type, value_compare, allocator_type>  _tree;

    public: // constructors & destructor

        explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
            : _alloc(alloc), _key_comp(comp), _value_comp(_key_comp), _tree(_value_comp, _alloc)
        {}

        map(const map &x)
        {}

        ~map()
        {}

        map &operator=(const map &x)
        {}

    };
}

#endif