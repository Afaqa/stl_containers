#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <iterator>
#include "iterator.hpp"
#include <iostream>

namespace ft {

    template <class T, class U>     struct is_same          { static const bool value = false; };
    template <class T>              struct is_same<T, T>    { static const bool value = true; };

    template <bool, class T = void> struct enable_if            {};
    template <class T>              struct enable_if<true, T>   { typedef T type; };

    template<class T, class Alloc = std::allocator<T> >
    class vector {

    public:

        typedef T                                                           value_type;
        typedef std::size_t                                                 size_type;
        typedef Alloc                                                       allocator_type;
        typedef typename allocator_type::reference                          reference;
        typedef typename allocator_type::const_reference                    const_reference;
        typedef typename allocator_type::pointer                            pointer;
        typedef typename allocator_type::const_pointer                      const_pointer;
        typedef random_access_iterator<value_type>                          iterator;
        typedef random_access_iterator<const value_type>                    const_iterator;
        typedef std::reverse_iterator<iterator>                             reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                       const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type    difference_type;

        explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
            if (n != 0) {
                _data = _allocator.allocate(n);
                _end = _data + n;
                for(pointer p = _data; p != _end; p += 1) {
                    _allocator.construct(p, val);
                }
            }
            _capacity = n;
        }

        template <class InputIterator>
        vector(InputIterator first,
               typename enable_if<is_same<typename InputIterator::iterator_type, std::input_iterator_tag>::value,
                InputIterator>::type last,
               const allocator_type& alloc = allocator_type()) :
            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        vector(const vector& other) : _allocator(other._allocator) {
            _copy_other(other);
        }

        ~vector() {
            if (_data != NULL) {
                clear();
                _allocator.deallocate(_data, _capacity);
            }
        }

        vector& operator=(const vector& other) {
            if (this != &other) {
                _delete_data();
                _allocator = allocator_type(other._allocator);
                _copy_other(other);
            }
            return *this;
        }

        template <class InputIterator>
            void assign (InputIterator first,
                         typename enable_if<is_same<typename InputIterator::iterator_type, std::random_access_iterator_tag>::value,
                                 InputIterator>::type last) {

            }

        void assign (size_type n, const value_type& val) {

        }

        allocator_type get_allocator() const {
            return _allocator;
        }

        iterator begin() {
            return iterator(_data);
        }

        const_iterator begin() const {
            return const_iterator(_data);
        }

        iterator end() {
            return iterator(_end);
        }

        const_iterator end() const {
            return const_iterator(_end);
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

        size_type size() const {
            return static_cast<size_type>((_end - _data));
        }

        size_type max_size() const {
            //return std::min(_allocator.max_size(), std::numeric_limits<T>::min()); //todo check
            return _allocator.max_size();
        }

        void resize (size_type n, value_type val = value_type()) {

        }

        size_type capacity() const {
            return _capacity;
        }

        bool empty() const {
            return (_end - _data) == 0;
        }

        void reserve (size_type n) {

        }

        reference operator[] (size_type n) {
            return _data[n];
        }

        const_reference operator[] (size_type n) const {
            return _data[n];
        }

        reference at (size_type n) {
            if (n >= size())
                throw std::out_of_range("vector");
            return _data[n];
        }

        const_reference at (size_type n) const {
            if (n >= size())
                throw std::out_of_range("vector");
            return _data[n];
        }

        reference front() {

        }

        const_reference front() const {

        }

        reference back() {

        }

        const_reference back() const {

        }

        void push_back(const T& x) {

        }

        void pop_back() {

        }

        iterator insert(iterator position, const T& x) {

        }

        void insert(iterator position, size_type n, const T& x) {

        }

        template<class InputIterator>
                void insert(iterator position, InputIterator first, InputIterator last) {

                }

        iterator erase(iterator position) {

        }

        iterator erase(iterator first, iterator last) {

        }

        void swap(vector<T, Alloc>& other) {
            pointer data = _data;
            pointer end = _end;
            allocator_type allocator = _allocator;
            size_type capacity = _capacity;

            _data = other._data;
            _end = other._end;
            _allocator = other._allocator;
            _capacity = other._capacity;

            other._data = data;
            other._end = end;
            other._allocator = allocator;
            other._capacity = capacity;
        }

        void clear() {
            while (_data != _end) {
                _allocator.destroy(--_end);
            }
       }

    private:

        allocator_type  _allocator;
        pointer         _data;
        pointer         _end;
        size_type       _capacity;

        void _delete_data() {
            clear();
            _allocator.deallocate(_data);
            _capacity = 0;
        }

        void _copy_other(const vector& other) {
            _data = _allocator.allocate(other._capacity);
            _end = _data + other.size();
            _capacity = other._capacity;
            for (pointer p = _data, ps = other._data; ps != other._end; ++p, ++ps) {
                _allocator.construct(p, *ps);
            }
        }

    };

    template<class T, class Allocator>
        bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            if (x.size() != y.size())
                return false;
            for (typename vector<T, Allocator>::iterator xit = x.begin(), yit = y.begin;
                    xit != x.end(); ++xit, ++yit) {
                if (*xit != *yit) {
                    return false;
                }
            }
            return true;
        }

    template<class T, class Allocator>
        bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            for (typename vector<T, Allocator>::iterator xit = x.begin(), yit = y.begin;
                 yit != y.end(); ++xit, ++yit) {
                if (xit == x.end() || *xit < *yit)
                    return true;
                if (*yit < *xit)
                    return false;
            }
            return false;
        }

    template<class T, class Allocator>
        bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            return !(x == y);
        }

    template<class T, class Allocator>
        bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            return y < x;
        }

    template<class T, class Allocator>
        bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            return !(x < y);
        }

    template<class T, class Allocator>
        bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
            return !(y < x);
        }

    template<class T, class Allocator>
        void swap(vector<T, Allocator>& x, vector<T, Allocator>& y) {
            x.swap(y);
        }

};

#endif
