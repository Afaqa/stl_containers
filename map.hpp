#ifndef MAP_HPP
#define MAP_HPP

#include <limits>
#include <iterator>
#include "memory.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <iostream>

namespace ft {

    template<class T1, class T2>
    struct pair;

    template<class Key, class T, class Compare, class Alloc>
    class map;

    template<class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type  first;
        second_type second;

        pair() : first(), second() {}

        template<class U, class V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

        pair(const first_type &a, const second_type &b) : first(a), second(b) {}
    };

    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(rhs < lhs); }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); }

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    }

    template<typename T>
    class map_iterator {
        typedef T _node_type;
    public:
        typedef typename _node_type::value_type value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef value_type                      *pointer;
        typedef value_type                      &reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        typedef typename value_type::first_type  _key_type;
        typedef typename value_type::second_type _mapped_type;
    public:
        map_iterator() : _data() {}

        explicit map_iterator(_node_type *data) : _data(data) {}

        map_iterator(map_iterator const &other) : _data(other._data) {}

        map_iterator &operator=(map_iterator const &other) {
            _data = other._data;
            return *this;
        }

        ~map_iterator() {}

        map_iterator &operator++() {
            if (!_data);
            else if (_data->right != NULL) {
                _data = _get_lowest(_data->right);
            }
            else {
                while (_data->parent && _data != _data->parent->left) {
                    _data = _data->parent;
                }
                if (_data->parent)
                    _data = _data->parent;
            }
            return *this;
        }

        map_iterator &operator--() {
            if (!_data);
            else if (_data->left != NULL) {
                _data = _get_highest(_data->left);
            }
            else {
                while (_data->parent && _data != _data->parent->right) {
                    _data = _data->parent;
                }
                if (_data->parent)
                    _data = _data->parent;
            }
            return *this;
        }

        map_iterator operator++(int) {
            map_iterator ret(_data);
            ++*this;
            return ret;
        }

        map_iterator operator--(int) {
            map_iterator ret(_data);
            --*this;
            return ret;
        }

        bool operator==(map_iterator const &other) const { return _data == other._data; }

        bool operator!=(map_iterator const &other) const { return !(*this == other); }

        reference operator*() { return _data->value; }

        pointer operator->() { return _data->value; }

    private:
        _node_type *_data;

        _node_type *_get_lowest(_node_type *node) {
            while (node->left != NULL) {
                node = node->left;
            }
            return node;
        }

        _node_type *_get_highest(_node_type *node) {
            while (node->right != NULL) {
                node = node->right;
            }
            return node;
        }
    };

    template<class Key, class T, class Compare = LessThanPredicate <Key>, class Alloc = allocator <pair<const Key, T>>>
    class map {
        struct _value_compare;
        struct _tree_node;
        struct _tree;

        typedef _tree_node _node_type;
        typedef _tree      _tree_type;
    public:
        typedef Key                                                      key_type;
        typedef T                                                        mapped_type;
        typedef pair<const key_type, mapped_type>                        value_type;
        typedef Compare                                                  key_compare;
        typedef _value_compare                                           value_compare;
        typedef Alloc                                                    allocator_type;
        typedef typename allocator_type::reference                       reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer                         pointer;
        typedef typename allocator_type::const_pointer                   const_pointer;
        typedef map_iterator<_node_type>                                 iterator;
        typedef map_iterator<_node_type>                                 const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;
        typedef std::size_t                                              size_type;
    private:
        typedef typename allocator_type::template rebind<_node_type>::other _node_allocator;

        struct _value_compare {
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }

        private:
            key_compare comp;

            _value_compare(key_compare c) : comp(c) {}
        };

        struct _tree_node {
            typedef value_type value_type;

            static const bool red   = true;
            static const bool black = false;

            value_type value;
            _tree_node *left;
            _tree_node *right;
            _tree_node *parent;
            bool       color;

            _tree_node() : value(), left(), right(), parent(), color(red) {}

            _tree_node(value_type value) : value(value), left(), right(), parent(), color(red) {}

            bool is_red() const { return color; }

            //      |                     |
            //   p_node        =>      r_node
            //   /    \\       =>     //    \
            //  a     r_node       p_node    c
            //       /    \       /     \
            //      b     c      a       b
            _tree_node *rotate_left() {
                _tree_node *r_node = right;
                right = r_node->left;
                r_node->left  = this;
                r_node->color = color;
                color = red;
                return r_node;
            }

            // opposite to rotate_left
            _tree_node *rotate_right() {
                _tree_node *r_node = left;
                left = r_node->right;
                r_node->right = this;
                r_node->color = color;
                color = red;
                return r_node;
            }

            void flip_color() {
                color = !color;
                left->color  = !left->color;
                right->color = !right->color;
            }
        };

        struct _tree {
            _node_type *head;
            size_type  size;
            _node_type *start;
            _node_type *end;

            _tree() : head(), size(), start(), end() {}

            void update_range() {
                if (!head) {
                    start = head;
                    end   = head;
                }
                else {
                    start = _lowest_node();
                    end   = _highest_node();
                }
            }

        private:
            _node_type *_lowest_node() const {
                _node_type *lowest = head;
                while (lowest->left)
                    lowest = lowest->left;
                return lowest;
            }

            _node_type *_highest_node() const {
                _node_type *highest = head;
                while (highest->right)
                    highest = highest->right;
                return highest;
            }
        };

    public:

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _kcomp(
            comp), _tree(), _allocator(alloc) {}

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _kcomp(comp), _tree(), _allocator(alloc) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        map(const map &x) : _kcomp(x._kcomp), _tree(), _allocator(x._allocator) {
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                insert(*it);
            }
        }

        ~map() {
            clear();
        }

        map &operator=(const map &x) {
            clear();
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                insert(*it);
            }
        }

        iterator begin() {
            return iterator(_tree.start);
        }

        const_iterator begin() const {
            return iterator(_tree.start);
        }

        iterator end() {
            return iterator(_tree.end);
        }

        const_iterator end() const {
            return iterator(_tree.end);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return reverse_iterator(begin());
        }

        bool empty() const {
            return _tree.size == 0;
        }

        size_type size() const {
            return _tree.size;
        }

        size_type max_size() const;
        mapped_type &operator[](const key_type &k);

        pair<iterator, bool> insert(const value_type &val) {
            pair<_node_type *, bool> inserted = _insert(_tree.head, val);
            _tree.update_range();
            return ft::make_pair(iterator(inserted.first), inserted.second);
        }

        iterator insert(iterator position, const value_type &val);
        template<class InputIterator>
        void insert(InputIterator first, InputIterator last);
        void erase(iterator position);
        size_type erase(const key_type &k);
        void erase(iterator first, iterator last);

        void swap(map &x) {
            ft::swap(*this, x);
        }

        void clear() {
            if (_tree.head) {
                _clear_node(_tree.head);
                _tree.head = NULL;
                _tree.size = 0;
                _tree.update_range();
            }
        }

        key_compare key_comp() const {
            return _kcomp;
        }

        value_compare value_comp() const {
            return value_compare(_kcomp);
        }

        iterator find(const key_type &k);
        const_iterator find(const key_type &k) const;
        size_type count(const key_type &k) const;
        iterator lower_bound(const key_type &k);
        const_iterator lower_bound(const key_type &k) const;
        iterator upper_bound(const key_type &k);
        const_iterator upper_bound(const key_type &k) const;
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
        pair<iterator, iterator> equal_range(const key_type &k);

        allocator_type get_allocator() const {
            return allocator_type(_allocator);
        }

    private:
        key_compare     _kcomp;
        _tree_type      _tree;
        _node_allocator _allocator;

        _node_type *_create_node(const_reference val) {
            _node_type *node = _allocator.allocate(1);
            _allocator.construct(node, _node_type(val));
            return node;
        }

        void _clear_node(_node_type *node) {
            if (node->left)
                _clear_node(node->left);
            if (node->right)
                _clear_node(node->right);
            _allocator.destroy(node);
            _allocator.deallocate(node, 1);
        }

        pair<_node_type *, bool> _insert(_node_type *&node, const_reference val) {
            pair<_node_type *, bool> inserted;
            if (!node) {
                node = _create_node(val);
                ++_tree.size;
                return make_pair(node, true);
            }
            if (node->left && node->right && node->left->is_red() && node->right->is_red())
                node->flip_color();

            bool less = _kcomp(val.first, node->value.first);
            bool more = _kcomp(node->value.first, val.first);
            if (!less && !more) {
                node->value.second = val.second;
                inserted = make_pair(node, false);
            }
            else if (less) {
                inserted = _insert(node->left, val);
            }
            else if (more) {
                inserted = _insert(node->right, val);
            }

            if (!inserted.first->parent)
                inserted.first->parent = node;

            if (node->left && node->right && node->right->is_red() && !node->left->is_red())
                node->rotate_left();
            if (node->left && node->left->left && node->left->is_red() && node->left->left->is_red())
                node->rotate_right();
            return inserted;
        }
    };

}

#endif
