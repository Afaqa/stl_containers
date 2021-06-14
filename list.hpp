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
    struct _list_node {
        _list_node *next;
        _list_node *prev;
        T    *value;
        _list_node() : next(this), prev(this), value() {}
    };

    template<typename T>
    class   list_iterator {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        typedef _list_node<value_type>    _node_type;
    public:
        list_iterator() : _data() {}
        explicit list_iterator(_node_type *data) : _data(data) {}
        list_iterator(list_iterator const &other) : _data(other._data) {}
        list_iterator &operator=(list_iterator const &other) {
            _data = other._data;
            return *this;
        }

        ~list_iterator() {}

        list_iterator &operator++() {
            _data = _data->next;
            return *this;
        }

        list_iterator &operator--() {
            _data = _data->prev;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator ret(_data);
            ++*this;
            return ret;
        }

        list_iterator operator--(int) {
            list_iterator ret(_data);
            --*this;
            return ret;
        }

        bool operator==(list_iterator const &other) const { return _data == other._data; }
        bool operator!=(list_iterator const &other) const { return !(*this == other); }
        reference operator*() { return *_data->value; }
        pointer operator->() { return _data->value; }

    private:

        _node_type *_data;

    };

    template<typename T>
    class   list_const_iterator {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        typedef const _list_node<value_type>    _node_type;
    public:
        list_const_iterator() : _data() {}
        explicit list_const_iterator(_node_type *data) : _data(data) {}
        list_const_iterator(list_const_iterator const &other) : _data(other._data) {}
        list_const_iterator &operator=(list_const_iterator const &other) {
            _data = other._data;
            return *this;
        }

        ~list_const_iterator() {}

        list_const_iterator &operator++() {
            _data = _data->next;
            return *this;
        }

        list_const_iterator &operator--() {
            _data = _data->prev;
            return *this;
        }

        list_const_iterator operator++(int) {
            list_const_iterator ret(_data);
            ++*this;
            return ret;
        }

        list_const_iterator operator--(int) {
            list_const_iterator ret(_data);
            --*this;
            return ret;
        }

        bool operator==(list_const_iterator const &other) const { return _data == other._data; }
        bool operator!=(list_const_iterator const &other) const { return !(*this == other); }
        reference operator*() { return *_data->value; }
        pointer operator->() { return _data->value; }

    private:

        _node_type *_data;

    };

    template<class T, class Alloc = allocator<T> >
    class list {
    public:
        typedef T                                                        value_type;
        typedef std::size_t                                              size_type;
        typedef Alloc                                                    allocator_type;
        typedef typename allocator_type::reference                       reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer                         pointer;
        typedef typename allocator_type::const_pointer                   const_pointer;
        typedef list_iterator<value_type>                       iterator;
        typedef list_const_iterator<value_type>                 const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;
    private:
        typedef _list_node<T>                                               _node_type;
        typedef typename allocator_type::template rebind<_node_type>::other _node_alloc;
    public:

        explicit list(const allocator_type &alloc = allocator_type())
            : _node(), _size(), _allocator(_node_alloc(alloc)) {

        }

        explicit list(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type())
            : _node(), _size(), _allocator(_node_alloc(alloc)) {

        }

        template<class InputIterator>
        list(InputIterator first, InputIterator last,
             const allocator_type &alloc = allocator_type())
            : _node(), _size(), _allocator(_node_alloc(alloc)) {

        }

        list(const list &x) : _node(), _size(x._size), _allocator(x._allocator) {

        }

        list& operator= (const list& x) {
            //free nodes
            //swap allocator
            //update size
            //insert nodes
        }

        iterator begin() {
            return iterator(_node.next);
        }

        const_iterator begin() const {
            return const_iterator(_node.next);
        }

        iterator end() {
            return iterator(&_node);
        }

        const_iterator end() const {
            return const_iterator(&_node);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(_node.prev);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_node.prev);
        }

        reverse_iterator rend() {
            return reverse_iterator(_node);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_node);
        }

        bool empty() const {
            return _size == size_type();
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return min<size_type>(_allocator.max_size(), min<size_type>(
                std::numeric_limits<size_type>::max() / (sizeof(value_type) + sizeof(_node_type)),
                std::numeric_limits<difference_type>::max()));
        }

        reference front() {
            return _node.next->value;
        }

        const_reference front() const {
            return _node.next->value;
        }

        reference back() {
            return _node.prev->value;
        }

        const_reference back() const {
            return _node.prev->value;
        }

    private:
        _node_type     _node;
        size_type      _size;
        _node_alloc    _allocator;
    };

}

#endif
