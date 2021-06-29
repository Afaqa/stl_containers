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
    std::ostream &operator<<(std::ostream &o, const pair<T1, T2> &p) {
        o << '(' << p.first << ", " << p.second << ')';
        return o;
    }

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    }

    template<typename T>
    class map_iterator {
        typedef T iterator_value;
    public:
        typedef typename iterator_value::value_type value_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef value_type                          *pointer;
        typedef value_type                          &reference;
        typedef std::bidirectional_iterator_tag     iterator_category;
    private:
        typedef typename value_type::first_type  _key_type;
        typedef typename value_type::second_type _mapped_type;
        typedef const value_type                 *_const_pointer;
        typedef const value_type                 &_const_reference;
    public:
        map_iterator() : _data() {}

        explicit map_iterator(iterator_value data) : _data(data) {}

        map_iterator(map_iterator const &other) : _data(other._data) {}

        map_iterator &operator=(map_iterator const &other) {
            _data = other._data;
            return *this;
        }

        ~map_iterator() {}

        map_iterator &operator++() {
            ++_data;
            return *this;
        }

        map_iterator &operator--() {
            --_data;
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

        reference operator*() { return *_data; }

        _const_reference operator*() const { return *_data; }

        pointer operator->() { return _data.get_pointer(); }

        _const_pointer operator->() const { return _data.get_pointer(); }

        iterator_value _data;
    private:
    };

    template<typename T>
    class map_const_iterator {
        typedef T iterator_value;
    public:
        typedef const typename iterator_value::value_type value_type;
        typedef std::ptrdiff_t                            difference_type;
        typedef value_type                                *pointer;
        typedef value_type                                &reference;
        typedef std::bidirectional_iterator_tag           iterator_category;
    private:
        typedef typename value_type::first_type              _key_type;
        typedef typename value_type::second_type             _mapped_type;
        typedef const value_type                             *_const_pointer;
        typedef const value_type                             &_const_reference;
        typedef typename iterator_value::iterator_value_type _it_value_type;
    public:
        map_const_iterator() : _data() {}

        explicit map_const_iterator(iterator_value data) : _data(data) {}

        map_const_iterator(const map_iterator<_it_value_type> &other) : _data(other._data) {}

        map_const_iterator(map_const_iterator const &other) : _data(other._data) {}

        map_const_iterator &operator=(map_const_iterator const &other) {
            _data = other._data;
            return *this;
        }

        ~map_const_iterator() {}

        map_const_iterator &operator++() {
            ++_data;
            return *this;
        }

        map_const_iterator &operator--() {
            --_data;
            return *this;
        }

        map_const_iterator operator++(int) {
            map_const_iterator ret(_data);
            ++*this;
            return ret;
        }

        map_const_iterator operator--(int) {
            map_const_iterator ret(_data);
            --*this;
            return ret;
        }

        bool operator==(map_const_iterator const &other) const { return _data == other._data; }

        bool operator!=(map_const_iterator const &other) const { return !(*this == other); }

        _const_reference operator*() const { return *_data; }

        _const_pointer operator->() const { return _data.get_pointer(); }

    private:
        iterator_value _data;
    };

    template<class Key, class T, class Compare = LessThanPredicate <Key>, class Alloc = allocator <pair<const Key, T> > >
    class map {
        struct _value_compare;
        struct _tree_node;
        struct _tree;

        template<typename Type>
        class map_iterator_value;

        typedef _tree_node _node_type;
        typedef _tree      _tree_type;
    public:
        typedef Key                                                       key_type;
        typedef T                                                         mapped_type;
        typedef pair<const key_type, mapped_type>                         value_type;
        typedef Compare                                                   key_compare;
        typedef _value_compare                                            value_compare;
        typedef Alloc                                                     allocator_type;
        typedef typename allocator_type::reference                        reference;
        typedef typename allocator_type::const_reference                  const_reference;
        typedef typename allocator_type::pointer                          pointer;
        typedef typename allocator_type::const_pointer                    const_pointer;
        typedef map_iterator<map_iterator_value<_node_type> >             iterator;
        typedef map_const_iterator<map_iterator_value<const _node_type> > const_iterator;
        typedef ft::reverse_iterator<iterator>                            reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                      const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type  difference_type;
        typedef std::size_t                                               size_type;
    private:
        typedef typename allocator_type::template rebind<_node_type>::other _node_allocator;

        struct _value_compare {
            _value_compare(key_compare c) : comp(c) {}

            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }

        private:
            key_compare comp;
        };

        struct _tree_node {
            typedef value_type value_type;

            static const bool red   = true;
            static const bool black = false;

            value_type *value;
            _tree_node *left;
            _tree_node *right;
            _tree_node *parent;
            bool       color;

            _tree_node() : value(), left(), right(), parent(), color(red) {}

            bool is_red() const { return color; }

            _node_type *next() {
                _node_type *tmp = this;
                if (tmp->right != NULL) {
                    tmp     = tmp->right;
                    while (tmp->left)
                        tmp = tmp->left;
                }
                else {
                    while (tmp->parent && tmp != tmp->parent->left) {
                        tmp = tmp->parent;
                    }
                    if (tmp->parent)
                        tmp = tmp->parent;
                }
                return tmp;
            }

            _node_type *prev() {
                _node_type *tmp = this;
                if (tmp->left != NULL) {
                    tmp     = tmp->left;
                    while (tmp->right)
                        tmp = tmp->right;
                }
                else {
                    while (tmp->parent && tmp != tmp->parent->right) {
                        tmp = tmp->parent;
                    }
                    if (tmp->parent)
                        tmp = tmp->parent;
                }
                return tmp;
            }

            //      |                     |
            //     l_node        =>       r_node
            //    /     \\       =>     //     \
            //   a      r_node       l_node     c
            //       /    \       /     \
            //      b     c      a       b
            _tree_node *rotate_left() {
                _tree_node *r_node = right;
                right = r_node->left;
                if (right)
                    right->parent = this;
                r_node->parent    = parent;
                parent = r_node;
                r_node->left  = this;
                r_node->color = color;
                color = red;
                return r_node;
            }

            // opposite to rotate_left
            _tree_node *rotate_right() {
                _tree_node *l_node = left;
                left = l_node->right;
                if (left)
                    left->parent = this;
                l_node->parent   = parent;
                parent = l_node;
                l_node->right = this;
                l_node->color = color;
                color = red;
                return l_node;
            }

            void flip_color() {
                color = !color;
                if (left)
                    left->color  = !left->color;
                if (right)
                    right->color = !right->color;
            }
        };

        struct _tree {
            _node_type *head;
            size_type  size;
            _node_type *start;
            _node_type *end;

            _tree() : head(), size(), start(), end() {}

            _tree(const _tree &x) : head(x.head), size(x.size), start(x.start), end(x.end) {}

            _tree &operator=(const _tree &x) {
                head  = x.head;
                size  = x.size;
                start = x.start;
                end   = x.end;
                return *this;
            }

            void update_range() {
                start = true_empty() ? head : _lowest_node();
            }

            bool true_empty() const {
                return head == end;
            }

            bool has_right(_node_type *node) const {
                return node->right && node->right != end;
            }

            _node_type *move_red_left(_node_type *node) {
                node->flip_color();
                if (has_right(node) && node->right->left && node->right->left->is_red()) {
                    node->right = node->right->rotate_right();
                    node = node->rotate_left();
                    node->flip_color();
                }
                return node;
            }

            _node_type *move_red_right(_node_type *node) {
                node->flip_color();
                if (node->left && node->left->left && node->left->left->is_red()) {
                    node = node->rotate_right();
                    node->flip_color();
                }
                return node;
            }

        private:
            _node_type *_lowest_node() const {
                _node_type *lowest = head;
                while (lowest->left)
                    lowest = lowest->left;
                return lowest;
            }
        };

        template<typename Type>
        class map_iterator_value {
        public:
            typedef const Type                            const_type;
            typedef typename ft::remove_const<Type>::type type;
            typedef map_iterator_value<type>              iterator_value_type;
            typedef map_iterator_value<const_type>        const_iterator_value_type;
            typedef typename Type::value_type             value_type;

            map_iterator_value() : _tree() {}

            map_iterator_value(_node_type *data, const _tree_type *tree) : _data(data), _tree(tree) {}

            map_iterator_value(const map_iterator_value<type> &other) : _data(other._data), _tree(other._tree) {}

            map_iterator_value(const map_iterator_value<const_type> &other) : _data(other._data), _tree(other._tree) {}

            ~map_iterator_value() {}

            map_iterator_value &operator++() {
                if (_data->right != NULL) {
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

            map_iterator_value &operator--() {
                if (_data->left != NULL) {
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

            map_iterator_value operator++(int) {
                map_iterator_value ret(_data);
                ++*this;
                return ret;
            }

            map_iterator_value operator--(int) {
                map_iterator_value ret(_data);
                --*this;
                return ret;
            }

            bool operator==(map_iterator_value const &other) const { return _data == other._data; }

            reference operator*() { return *_data->value; }

            const_reference operator*() const { return *_data->value; }

            pointer get_pointer() { return _data->value; }

            const_pointer get_pointer() const { return _data->value; }

            _node_type       *_data;
            const _tree_type *_tree;
        private:

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

    public:
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _kcomp(
            comp), _tree(), _allocator(alloc) {
            _init_tree();
        }

        template<class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _kcomp(comp), _tree(), _allocator(alloc) {
            _init_tree();
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        map(const map &x) : _kcomp(x._kcomp), _tree(), _allocator(x._allocator) {
            _init_tree();
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                insert(*it);
            }
        }

        ~map() {
            clear();
            _uninit_tree();
        }

        map &operator=(const map &x) {
            clear();
            _kcomp = x._kcomp;
            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                insert(*it);
            }
            return *this;
        }

        iterator begin() {
            return _make_iterator(_tree.start);
        }

        const_iterator begin() const {
            return _make_const_iterator(_tree.start);
        }

        iterator end() {
            return _make_iterator(_tree.end);
        }

        const_iterator end() const {
            return _make_const_iterator(_tree.end);
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
            return _tree.size == 0;
        }

        size_type size() const {
            return _tree.size;
        }

        size_type max_size() const {
            return min<size_type>(_allocator.max_size(), min<size_type>(
                std::numeric_limits<size_type>::max() / (sizeof(value_type) + sizeof(_node_type)),
                std::numeric_limits<difference_type>::max()));
        }

        mapped_type &operator[](const key_type &k) {
            _node_type *node = _find_node(k);
            if (!node) {
                // pair . iterator -> ret
                return insert(ft::make_pair(k, mapped_type())).first->second;
            }
            // _mode_type -> value_type -> ret
            return node->value->second;
        }

        pair<iterator, bool> insert(const value_type &val) {
            if (_tree.true_empty()) {
                _insert_pre_end(_tree.head, val);
                _tree.head->color = _tree.head->black;
                _tree.update_range();
                return ft::make_pair(begin(), true);
            }
            pair<_node_type *, bool> inserted = _insert(_tree.head, val);
            _tree.update_range();
            if (_tree.head->color != _node_type::black) {

            }
            _tree.head->color = _tree.head->black;
            return ft::make_pair(_make_iterator(inserted.first), inserted.second);
        }

        iterator insert(iterator position, const value_type &val) {
            _node_type *pos = _find_node(position->first);
            if (pos && _equal(val.first, pos)) {
                pos->value->second = val.second;
                return iterator(_make_iterator(pos));
            }
            return insert(val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        void erase(iterator position) {
            erase(position->first);
        }

        size_type erase(const key_type &k) {
            size_type presize = size();
            _tree.head = _delete(_tree.head, k);
            _tree.update_range();
            return size() - presize;
        }

        void erase(iterator first, iterator last) {
            while (first != last) {
                iterator tmp = first;
                ++first;
                erase(tmp->first);
            }
        }

        void swap(map &x) {
            ft::swap(_allocator, x._allocator);
            ft::swap(_kcomp, x._kcomp);
            ft::swap(_tree, x._tree);
        }

        void clear() {
            if (!_tree.true_empty()) {
                _clear_node(_tree.head);
                _tree.head = _tree.end;
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

        iterator find(const key_type &k) {
            _node_type *node = _find_node(k);
            return node ? _make_iterator(node) : end();
        }

        const_iterator find(const key_type &k) const {
            _node_type *node = _find_node(k);
            return node ? _make_const_iterator(node) : end();
        }

        size_type count(const key_type &k) const {
            return _find_node(k) ? 1 : 0;
        }

        iterator lower_bound(const key_type &k) {
            return _make_iterator(_find_node_not_less(k));
        }

        const_iterator lower_bound(const key_type &k) const {
            return _make_const_iterator(_find_node_not_less(k));
        }

        iterator upper_bound(const key_type &k) {
            return _make_iterator(_find_node_more(k));
        }

        const_iterator upper_bound(const key_type &k) const {
            return _make_const_iterator(_find_node_more(k));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
            return make_pair(lower_bound(k), upper_bound(k));
        }

        pair<iterator, iterator> equal_range(const key_type &k) {
            return make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const {
            return allocator_type(_allocator);
        }

    private:
        key_compare     _kcomp;
        _tree_type      _tree;
        _node_allocator _allocator;

        void _init_tree() {
            _tree.end = _allocator.allocate(1);
            _allocator.construct(_tree.end, _node_type());
            _tree.head = _tree.end;
            _tree.update_range();
        }

        void _uninit_tree() {
            _allocator.destroy(_tree.end);
            _allocator.deallocate(_tree.end, 1);
        }

        inline bool _less(const key_type &key, _node_type *node) const {
            return _kcomp(key, node->value->first);
        }

        inline bool _more(const key_type &key, _node_type *node) const {
            return _kcomp(node->value->first, key);
        }

        inline bool _equal(const key_type &key, _node_type *node) const {
            return !_less(key, node) && !_more(key, node);
        }

        iterator _make_iterator(_node_type *node) {
            return iterator(map_iterator_value<_node_type>(node, &_tree));
        }

        const_iterator _make_const_iterator(_node_type *node) const {
            return iterator(map_iterator_value<_node_type>(node, &_tree));
        }

        _node_type *_create_node(const_reference val) {
            _node_type *node = _allocator.allocate(1);
            _allocator.construct(node, _node_type());
            node->value = get_allocator().allocate(1);
            get_allocator().construct(node->value, val);
            return node;
        }

        _node_type *_find_node(const key_type &key) const {
            _node_type *current = _tree.head;
            while (current) {
                if (_is_end(current))
                    return NULL;
                if (_equal(key, current))
                    break;
                else if (_less(key, current))
                    current = current->left;
                else
                    current = current->right;
            }
            return current;
        }

        _node_type *_find_node_not_less(const key_type &key) const {
            _node_type *current = _tree.start;
            while (!_is_end(current) && _more(key, current))
                current = current->next();
            return current;
        }

        _node_type *_find_node_more(const key_type &key) const {
            _node_type *current = _tree.start;
            while (!_is_end(current) && _more(key, current))
                current = current->next();
            if (!_is_end(current) && !_less(key, current))
                return current->next(); // equal
            return current;
        }

        _node_type *_delete_min(_node_type *node) {
            if (!node->left) {
                node->parent->left = NULL;
                _node_type *ret    = NULL;
                if (node->right) {
                    ret = node->right;
                    ret->parent = node->parent;
                }
                _delete_node(node);
                return ret;
            }
            if (node->left && node->left->left && !node->left->is_red() && !node->left->left->is_red())
                _tree.move_red_left(node);
            node->left = _delete_min(node->left);

            if (_tree.has_right(node) && node->right->is_red())
                node = node->rotate_left();
            if (node->left && node->left->left && node->left->is_red() && node->left->left->is_red())
                node = node->rotate_right();
            if (_tree.has_right(node) && node->left && node->left->is_red() && node->right->is_red())
                node->flip_color();
            return node;
        }

        //       |        |=>        |
        //     parent     |=>     child
        //     /   \      |=>     /   \
        //    a    child  |=>    a   parent
        //        /   \   |=>        /   \
        //       b     c  |=>       b     c
        void _swap_relative_nodes(_node_type *parent, _node_type *child) {
            _node_type *tmp;
            if (child == parent->left) {
                tmp = child->left;
                child->left  = parent;
                parent->left = tmp;
                ft::swap(child->right, parent->right);
            }
            else if (child == parent->right) {
                tmp = child->right;
                child->right  = parent;
                parent->right = tmp;
                ft::swap(child->left, parent->left);
            }
            if (parent->parent) {
                if (parent->parent->right == parent) {
                    parent->parent->right = child;
                }
                else {
                    parent->parent->left = child;
                }
            }
            child->parent = parent->parent;
            if (parent->left) parent->left->parent   = parent;
            if (parent->right) parent->right->parent = parent;
            if (child->left) child->left->parent     = child;
            if (child->right) child->right->parent   = child;
            ft::swap(parent->color, child->color);
        }

        // swap nodes (swap links between their parents and children)
        // value does not change and iterators pointing to existing
        // nodes will still work
        void _swap_nodes(_node_type *a, _node_type *b) {
            // swap parent left or right pointers
            if (a->parent && b->parent) {
                _node_type *&a_par_node = a->parent->left == a ? a->parent->left : a->parent->right;
                _node_type *&b_par_node = b->parent->left == b ? b->parent->left : b->parent->right;
                ft::swap(a_par_node, b_par_node);
            }
            else if (a->parent) {
                if (a->parent->left == a)
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }
            else if (b->parent) {
                if (b->parent->left == b)
                    b->parent->left = a;
                else
                    b->parent->right = a;
            }
            // set a's children parent pointer to b
            if (a->left) a->left->parent   = b;
            if (a->right) a->right->parent = b;
            // set b's children parent pointer to a
            if (b->left) b->left->parent   = a;
            if (b->right) b->right->parent = a;
            // swap children and parent pointers of a and b
            ft::swap(b->left, a->left);
            ft::swap(b->right, a->right);
            ft::swap(b->parent, a->parent);
            ft::swap(b->color, a->color);
        }

        _node_type *_delete(_node_type *current, const key_type &key) {
            if (!current)
                return NULL;
            else if (_less(key, current) && current->left) {
                if (current->left->left && !current->left->is_red() && !current->left->left->is_red())
                    current = _tree.move_red_left(current);
                current->left = _delete(current->left, key);
            }
            else {
                if (current->left && current->left->is_red())
                    current = current->rotate_right();
                if (!_tree.has_right(current) && _equal(key, current)) {
                    // delete the node, connect node->left, dont lose _tree.end
                    if (current->parent && current->parent->left != current) {
                        if (current->right && current->left) {
                            _node_type *tmp = current->left;
                            while (tmp->right)
                                tmp         = tmp->right;
                            tmp->right        = _tree.end;
                            _tree.end->parent = tmp;
                        }
                    }
                    _node_type *ret = current->left;
                    if (current->left)
                        current->left->parent = current->parent;
                    else if (current->right) {
                        ret = current->right;
                        ret->parent = current->parent;
                    }
                    _delete_node(current);
                    return ret;
                }
                if (_tree.has_right(current) && current->right->left && !current->right->is_red() &&
                    !current->right->left->is_red())
                    current = _tree.move_red_right(current);
                if (_equal(key, current) && current->right) {
                    _node_type *min        = _get_min(current->right);
                    if (min == current->right) {
                        _swap_relative_nodes(current, min);
                    }
                    else
                        _swap_nodes(current, min);
                    ft::swap(current, min);
                    if (min == current->right) {
                        current->right = min->right;
                    }
                    else {
                        min->parent->left = min->right;
                    }
                    if (min->right)
                        min->right->parent = min->parent;
                    _delete_node(min);
                }
                else
                    current->right = _delete(current->right, key);
            }
            if (_tree.has_right(current) && current->right->is_red())
                current = current->rotate_left();
            if (current->left && current->left->left && current->left->is_red() && current->left->left->is_red())
                current = current->rotate_right();
            if (_tree.has_right(current) && current->left && current->left->is_red() && current->right->is_red())
                current->flip_color();
            return current;
        }

        _node_type *_get_min(_node_type *node) const {
            while (node->left)
                node = node->left;
            return node;
        }

        void _delete_node(_node_type *node) {
            get_allocator().destroy(node->value);
            get_allocator().deallocate(node->value, 1);
            _allocator.destroy(node);
            _allocator.deallocate(node, 1);
            --_tree.size;
        }

        void _clear_node(_node_type *node) {
            if (node->left)
                _clear_node(node->left);
            if (_tree.has_right(node))
                _clear_node(node->right);
            _delete_node(node);
        }

        bool _is_end(_node_type *node) const {
            return node == _tree.end;
        }

        pair<_node_type *, bool> _insert(_node_type *&node, const_reference val) {
            pair<_node_type *, bool> inserted;
            if (!node) {
                node = _create_node(val);
                ++_tree.size;
                return make_pair(node, true);
            }

            if (_tree.has_right(node) && node->left && node->left->is_red() && node->right->is_red())
                node->flip_color();

            bool less = _is_end(node) || _less(val.first, node);
            bool more = !_is_end(node) && _more(val.first, node);
            if (!less && !more) {
                inserted = make_pair(node, false);
            }
            else if (less) {
                inserted = _insert(node->left, val);
            }
            else if (node->right != _tree.end) {
                inserted = _insert(node->right, val);
            }
            else {
                _insert_pre_end(node->right, val);
                inserted = make_pair(node->right, true);
            }

            if (!inserted.first->parent)
                inserted.first->parent = node;

            if (_tree.has_right(node) && node->right->is_red())
                node = node->rotate_left();
            if (node->left && node->left->left && node->left->is_red() && node->left->left->is_red())
                node = node->rotate_right();

            return inserted;
        }

        void _insert_pre_end(_node_type *&node, const value_type &val) {
            node = _create_node(val);
            node->right       = _tree.end;
            _tree.end->parent = node;
            ++_tree.size;
        }
    };

}

#endif
