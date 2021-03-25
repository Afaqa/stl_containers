#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <iterator>
#include <iostream>

namespace ft {

    template <class T, class U>     struct is_same          { static const bool value = false; };
    template <class T>              struct is_same<T, T>    { static const bool value = true; };

    template <bool, class T = void> struct enable_if            {};
    template <class T>              struct enable_if<true, T>   { typedef T type; };

    template <typename T>
    class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
    {

        T   _value;

        VectorIterator() {}

    public:

        typedef typename std::iterator_traits<T>::reference reference;
        typedef typename std::iterator_traits<T>::value_type value_type;

        explicit VectorIterator(T value) : _value(value) {}
//        explicit VectorIterator(T& value) : _value(value) {}

        VectorIterator(VectorIterator<T> const& other) : _value(other._value) {
        }

        VectorIterator& operator=(VectorIterator<T> const& other) {
            _value = other._value;
            return *this;
        }

        ~VectorIterator() {}

        reference  operator*() {
            return *_value;
        }

        VectorIterator& operator++() {
            ++_value;
            return *this;
        }

        VectorIterator operator++(int) {
            VectorIterator<T> ret;
            ret._value = _value + 1;
            return ret;
        }

        bool    operator!=(VectorIterator<T> const& other) {
            return _value != other._value;
        }

    };

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
        typedef VectorIterator<pointer>                                     iterator;
        typedef VectorIterator<const_pointer>                               const_iterator;
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
               typename enable_if<is_same<typename InputIterator::iterator_type, std::random_access_iterator_tag>::value,
                InputIterator>::type last,
               const allocator_type& alloc = allocator_type()) :
            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        vector(const vector& x) {

        }

        ~vector() {
            clear();
        }

        vector& operator=(const vector& x) {

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
            return reverse_iterator(_data);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_data);
        }

        reverse_iterator rend() {
            return reverse_iterator(_end);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_end);
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

        }

        const_reference operator[] (size_type n) const {

        }

        reference at (size_type n) {

        }

        const_reference at (size_type n) const {

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
            for (pointer p = _data; p != _end; p += sizeof(value_type)) {
                _allocator.destroy(p);
            }
            _allocator.deallocate(_data, 0);
       }

    private:

        allocator_type  _allocator;
        pointer         _data;
        pointer         _end;
        size_type       _capacity;

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
