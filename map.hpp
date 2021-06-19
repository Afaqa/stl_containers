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

    template<class Key, class T, class Compare = LessThanPredicate <Key>, class Alloc = allocator <pair<const Key, T>>>
    class map {
        class _value_compare;

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
        typedef bidirectional_iterator <value_type>                      iterator;
        typedef bidirectional_iterator <value_type>                      const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;
        typedef std::size_t                                              size_type;
    private:
        class _value_compare {
        protected:
            Compare comp;

            _value_compare(Compare c) : comp(c) {}

        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };

    public:

        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type());
        template<class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type());
        map(const map &x);
        ~map();
        map &operator=(const map &x);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        bool empty() const;
        size_type size() const;
        size_type max_size() const;
        mapped_type &operator[](const key_type &k);
        pair<iterator, bool> insert(const value_type &val);
        iterator insert(iterator position, const value_type &val);
        template<class InputIterator>
        void insert(InputIterator first, InputIterator last);
        void erase(iterator position);
        size_type erase(const key_type &k);
        void erase(iterator first, iterator last);
        void swap(map &x);
        void clear();
        key_compare key_comp() const;
        value_compare value_comp() const;
        iterator find(const key_type &k);
        const_iterator find(const key_type &k) const;
        size_type count(const key_type &k) const;
        iterator lower_bound(const key_type &k);
        const_iterator lower_bound(const key_type &k) const;
        iterator upper_bound(const key_type &k);
        const_iterator upper_bound(const key_type &k) const;
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
        pair<iterator, iterator> equal_range(const key_type &k);
        allocator_type get_allocator() const;
    private:
        key_compare    _kcomp;
        size_type      _size;
        allocator_type _allocator;
    };

}

#endif
