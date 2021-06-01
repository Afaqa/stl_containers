#ifndef LIST_HPP
#define LIST_HPP

#include <limits>
#include <iterator>
#include "memory.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <iostream>

namespace ft {

    template<class T>
    class _list_node_base {
    public:
        _list_node_base<T> prev;
        _list_node_base<T> next;
    };

    template<class T>
    class _list_node : public _list_node_base<T> {
    public:
        T value;
    };

    template<class T, class Alloc = allocator<T> >
    class list {
        typedef _list_node_base<T> _node_base;
    public:
        typedef T                                                        value_type;
        typedef std::size_t                                              size_type;
        typedef Alloc                                                    allocator_type;
        typedef typename allocator_type::reference                       reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer                         pointer;
        typedef typename allocator_type::const_pointer                   const_pointer;
        typedef bidirectional_iterator<value_type>                       iterator;
        typedef bidirectional_iterator<const value_type>                 const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;

        explicit list(const allocator_type &alloc = allocator_type())
            : _node(), _size(), _capacity(), _allocator(alloc) {

        }

        explicit list(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type())
            : _node(), _size(), _capacoty(), _allocator(alloc) {

        }

        template<class InputIterator>
        list(InputIterator first, InputIterator last,
             const allocator_type &alloc = allocator_type())
            : _node(), _size(), _capacity(), _allocator(alloc) {

        }

        list(const list &x) : _node(), _size(), _capacity(), _allocator(x._allocator) {

        }

    private:
        _node_base     _node;
        size_type      _size;
        size_type      _capacity;
        allocator_type _allocator;
    };

}

#endif
