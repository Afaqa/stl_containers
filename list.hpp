#ifndef LIST_HPP
#define LIST_HPP

#include <limits>
#include <iterator>
#include "memory.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <iostream>

namespace stl {

    template<class T>
    struct _list_node {
        _list_node *next;
        _list_node *prev;
        T          *value;

        _list_node() : next(this), prev(this), value() {}
    };

    template<typename T>
    class list_iterator {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        typedef _list_node<value_type> _node_type;
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
    class list_const_iterator {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        typedef const _list_node<value_type> _node_type;
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
        typedef list_iterator<value_type>                                iterator;
        typedef list_const_iterator<value_type>                          const_iterator;
        typedef stl::reverse_iterator<iterator>                           reverse_iterator;
        typedef stl::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef typename stl::iterator_traits<iterator>::difference_type difference_type;
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
            for (size_type i = 0; i < n; ++i) {
                push_back(val);
            }
        }

        template<class InputIterator>
        list(InputIterator first,
             typename enable_if<is_valid_iterator_type<InputIterator, std::input_iterator_tag, pointer>::value, InputIterator>::type last,
             const allocator_type &alloc = allocator_type())
            : _node(), _size(), _allocator(_node_alloc(alloc)) {
            for (; first != last; ++first) {
                push_back(*first);
            }
        }

        list(const list &x) : _node(), _size(), _allocator(x._allocator) {
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                push_back(*it);
            }
        }

        list &operator=(const list &x) {
            clear();
            _allocator = x._allocator;
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                push_back(*it);
            }
            return *this;
        }

        ~list() {
            clear();
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
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
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
            return *_node.next->value;
        }

        const_reference front() const {
            return *_node.next->value;
        }

        reference back() {
            return *_node.prev->value;
        }

        const_reference back() const {
            return *_node.prev->value;
        }

        template<class InputIterator>
        void assign(InputIterator first,
                    typename enable_if<is_valid_iterator_type<InputIterator, std::input_iterator_tag, pointer>::value, InputIterator>::type last) {
            clear();
            for (; first != last; ++first) {
                push_back(*first);
            }
        }

        void assign(size_type n, const value_type &val) {
            clear();
            for (size_type i = 0; i < n; ++i) {
                push_back(val);
            }
        }

        void push_front(const value_type &val) {
            _make_new(&_node, _node.next, val);
            ++_size;
        }

        void pop_front() {
            _node_type *next = _node.next;
            _node.next       = next->next;
            next->next->prev = next->prev;
            get_allocator().destroy(next->value);
            get_allocator().deallocate(next->value, 1);
            _allocator.destroy(next);
            _allocator.deallocate(next, 1);
            --_size;
        }

        void push_back(const value_type &val) {
            _make_new(_node.prev, &_node, val);
            ++_size;
        }

        void pop_back() {
            _node_type *prev = _node.prev;
            _node.prev       = prev->prev;
            prev->prev->next = prev->next;
            get_allocator().destroy(prev->value);
            get_allocator().deallocate(prev->value, 1);
            _allocator.destroy(prev);
            _allocator.deallocate(prev, 1);
            --_size;
        }

        iterator insert(iterator position, const value_type &val) {
            _node_type *current = _node.next;
            for (iterator it = begin(); it != position; ++it)
                current = current->next;
            _make_new(current->prev, current, val);
            ++_size;
            return --position;
        }

        void insert(iterator position, size_type n, const value_type &val) {
            _node_type *current = _node.next;
            for (iterator it = begin(); it != position; ++it)
                current = current->next;
            while (n > 0) {
                _make_new(current->prev, current, val);
                --n;
                ++_size;
            }
        }

        template<class InputIterator>
        void insert(iterator position, InputIterator first,
                    typename enable_if<is_valid_iterator_type<InputIterator, std::input_iterator_tag, pointer>::value, InputIterator>::type last) {
            _node_type *current = _node.next;
            for (iterator it = begin(); it != position; ++it)
                current = current->next;
            for (; first != last; ++first) {
                _make_new(current->prev, current, *first);
                ++_size;
            }
        }

        iterator erase(iterator position) {
            _node_type *current = _node.next;
            for (iterator it = begin(); it != position; ++it)
                current = current->next;
            iterator ret(current->next);
            _delete_node(current);
            --_size;
            return ret;
        }

        iterator erase(iterator first, iterator last) {
            _node_type *current = _node.next;
            for (iterator it = begin(); it != first; ++it)
                current = current->next;
            _node_type *todelete;
            for (; first != last; ++first) {
                todelete = current;
                current = current->next;
                --first;
                _delete_node(todelete);
                --_size;
            }
            return iterator(current);
        }

        void swap(list &x) {
            stl::swap(*this, x);
        }

        void resize(size_type n, value_type val = value_type()) {
            while (_size > n) {
                pop_back();
            }
            while (_size < n) {
                push_back(val);
            }
        }

        void clear() {
            while (_size > 0) {
                pop_front();
            }
        }

        void splice(iterator position, list &x) {
            _node_type *node = _get_node(position, begin(), _node.next);
            _connect_nodes(node, x._node.next, x._node.prev);
            _size += x._size;
            x._size = 0;
        }

        void splice(iterator position, list &x, iterator i) {
            _node_type *node = _get_node(position, begin(), _node.next);
            _node_type *xnode = _get_node(i, x.begin(), x._node.next);
            _connect_nodes(node, xnode, xnode);
            --x._size;
            ++_size;
        }

        void splice(iterator position, list &x, iterator first, iterator last) {
            _node_type *node = _get_node(position, begin(), _node.next);
            _node_type *x_left_node = _get_node(first, x.begin(), x._node.next);
            _node_type *x_right_node = _get_node(last, x.begin(), x._node.next);
            x_right_node = x_right_node->prev;
            size_type size = stl::distance(first, last);
            _connect_nodes(node, x_left_node, x_right_node);
            _size += size;
            x._size -= size;
        }

        void remove(const value_type &val) {
            remove_if(EqualToValuePredicate<value_type>(val));
        }

        template<class Predicate>
        void remove_if(Predicate pred) {
            for (_node_type *node = _node.next; node != &_node; node = node->next) {
                if (pred(*node->value)) {
                    node = node->prev;
                    _delete_node(node->next);
                    --_size;
                }
            }
        }

        void unique() {
            unique(EqualToPredicate<value_type>());
        }

        template<class BinaryPredicate>
        void unique(BinaryPredicate binary_pred) {
            for (_node_type *node = _node.next->next; node != &_node; node = node->next) {
                if (binary_pred(*node->prev->value, *node->value)) {
                    node = node->prev;
                    _delete_node(node->next);
                    --_size;
                }
            }
        }

        void merge(list &x) {
            return merge(x, LessThanPredicate<value_type>());
        }

        template<class Compare>
        void merge(list &x, Compare comp) {
            if (&x == this)
                return;
            _node_type *node = _node.next;
            _node_type *x_left_node = x._node.next;
            _node_type *x_right_node = x_left_node;
            for (;node != &_node; node = node->next) {
                if (x_left_node == &x._node)
                    break;
                if (comp(*x_left_node->value, *node->value)) {
                    x_right_node = x_left_node->next;
                    while (x_right_node != &x._node && comp(*x_right_node->value, *node->value)) {
                        x_right_node = x_right_node->next;
                    }
                    _connect_nodes(node, x_left_node, x_right_node->prev);
                    x_left_node = x_right_node;
                }
            }
            if (x_left_node != &x._node)
                _connect_nodes(node, x_left_node, x._node.prev);
            _size += x._size;
            x._size = 0;
        }

        void sort() {
            sort(LessThanPredicate<value_type>());
        }

        template<class Compare>
        void sort(Compare comp) {
            _qsort(_node.next, _node.prev, comp);
        }

        void reverse() {
            _node_type *current = _node.next;
            for (;;current = current->prev) {
                stl::swap(current->next, current->prev);
                if (current == &_node)
                    break;
            }
        }

        allocator_type get_allocator() const {
            return allocator_type(_allocator);
        }

    private:
        _node_type  _node;
        size_type   _size;
        _node_alloc _allocator;

        _node_type *_make_new(_node_type *prev, _node_type *next, const_reference val = value_type()) {
            _node_type *the_new = _allocator.allocate(1);
            _allocator.construct(the_new, _node_type());
            the_new->value = get_allocator().allocate(1);
            get_allocator().construct(the_new->value, val);
            the_new->prev = prev;
            the_new->next = next;
            prev->next = the_new;
            next->prev = the_new;
            return the_new;
        }

        void _delete_node(_node_type *node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            get_allocator().destroy(node->value);
            get_allocator().deallocate(node->value, 1);
            _allocator.destroy(node);
            _allocator.deallocate(node, 1);
        }

        // connect into (pre-)pos list nodes from left to right
        // list a: ---[pos->prev] => [pos]---
        // list b: ---[m] => [left] => ... => [right] => [n]---
        // so list b will have connected ---[m] => [n]---
        // and list a will have ---[pos->prev] => [left] ... [right] => [pos]
        void _connect_nodes(_node_type *pos, _node_type *left, _node_type *right) {
            left->prev->next = right->next;
            right->next->prev = left->prev;
            if (left->value)
                pos->prev->next = left;
            left->prev = pos->prev;
            right->next = pos;
            if (right->value)
                pos->prev = right;
        }

        _node_type *_get_node(iterator position, iterator start, _node_type *node) {
            for (; start != position; ++start)
                node = node->next;
            return node;
        }

        template<class Compare>
        void _qsort(_node_type *left, _node_type *right, Compare &comp) {
            if (right != NULL && left != right && left != right->next) {
                _node_type *p = _qsort_partition(left, right, comp);
                _qsort(left, p->prev, comp);
                _qsort(p->next, right, comp);
            }
        }

        template<class Compare>
        _node_type *_qsort_partition(_node_type *left, _node_type *right, Compare &comp) {
            const_reference pivot = *right->value;
            _node_type *i = left->prev;
            for (_node_type *j = left; j != right; j = j->next) {
                if (comp(*j->value, pivot)) {
                    i = i == &_node ? left : i->next;
                    stl::swap(i->value, j->value);
                }
            }
            i = i == &_node ? left : i->next;
            stl::swap(i->value, right->value);
            return i;
        }
    };

    template<class T, class Alloc>
    bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        for (typename list<T, Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
             lit != lhs.end(); ++lit, ++rit) {
            if (!(*lit == *rit)) {
                return false;
            }
        }
        return true;
    }

    template<class T, class Alloc>
    bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        for (typename list<T, Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
             rit != rhs.end(); ++lit, ++rit) {
            if (lit == lhs.end() || *lit < *rit)
                return true;
            if (*rit < *lit)
                return false;
        }
        return false;
    }

    template<class T, class Alloc>
    bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template<class T, class Alloc>
    bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return rhs < lhs;
    }

    template<class T, class Alloc>
    bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return !(rhs < lhs);
    }

    template<class T, class Alloc>
    bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return  !(lhs < rhs);
    }

    template<class T, class Alloc>
    void swap(list<T, Alloc> &x, list<T, Alloc> &y) {
        x.swap(y);
    }

}

#endif
