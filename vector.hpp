#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <iterator>
#include <iostream>

namespace ft {

    template <typename T>
    class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
    {

        T&   _value;

        VectorIterator() {}

    public:

        typedef typename std::iterator_traits<T>::reference reference;
        typedef typename std::iterator_traits<T>::value_type value_type;

        explicit VectorIterator(T& value) : _value(value) {}

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
            _value += sizeof(value_type);
            return *this;
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
            _allocator(alloc) {
            if (n != 0) {
                _data = _allocator.allocate(n);
                _end = _data + n * sizeof(value_type);
                _allocator.construct(_data, val);
//            for(pointer _p = _data; _p != _end; ++_p) {
//            }
            }
            _capacity = n;
        }

//        template <class InputIterator>
//        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
//            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
//
//        }

        vector(const vector& x) {

        }

        ~vector() {}

        vector& operator=(const vector& x) {

        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last) {

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

        }

        iterator end() {
            return iterator(_end);
        }

        const_iterator end() const {

        }

        reverse_iterator rbegin() {

        }

        const_reverse_iterator rbegin() const {

        }

        reverse_iterator rend() {

        }

        const_reverse_iterator rend() const {

        }

        size_type size() const {
            return static_cast<size_type>((_end - _data) / sizeof(value_type));
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

    private:

        allocator_type  _allocator;
        pointer         _data;
        pointer         _end;
        size_type       _size;
        size_type       _capacity;

    };

};

#endif
