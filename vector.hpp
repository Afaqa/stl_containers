#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <iterator>
#include "memory.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include <iostream>

namespace ft {

    template<class T, class Alloc = allocator<T> >
    class vector {

    public:

        typedef T                                                        value_type;
        typedef std::size_t                                              size_type;
        typedef Alloc                                                    allocator_type;
        typedef typename allocator_type::reference                       reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer                         pointer;
        typedef typename allocator_type::const_pointer                   const_pointer;
        typedef random_access_iterator<value_type>                       iterator;
        typedef random_access_iterator<const value_type>                 const_iterator;
        typedef std::reverse_iterator<iterator>                          reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type difference_type;

        explicit vector(const allocator_type &alloc = allocator_type()) : _allocator(alloc), _data(NULL), _end(NULL),
                                                                          _capacity(0) {
        }

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) :
            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
            if (n != 0) {
                _allocate(n);
                _construct_data(_data, _end, val);
            }
        }

        template<class InputIterator>
        vector(InputIterator first,
               typename enable_if<
                   is_valid_iterator_type<InputIterator, std::random_access_iterator_tag, pointer>::value &&
                   !is_same<typename std::iterator_traits<InputIterator>::iterator_category, std::random_access_iterator_tag>::value,
                   InputIterator>::type last,
               const allocator_type &alloc = allocator_type()) :
            _allocator(alloc), _data(NULL), _end(NULL), _capacity(0) {
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        template<class ForwardIterator>
        vector(ForwardIterator first,
               typename enable_if<
                   is_valid_iterator_type<ForwardIterator, std::random_access_iterator_tag, pointer>::value &&
                   !is_same<typename std::iterator_traits<ForwardIterator>::iterator_category, std::input_iterator_tag>::value, ForwardIterator>::type last,
               const allocator_type &alloc = allocator_type()) : _allocator(alloc), _data(NULL), _end(NULL),
                                                                 _capacity(0) {
            difference_type n = distance(first, last);
            if (n != 0) {
                _allocate(n);
                _construct_data(first, last);
            }
        }

        vector(const vector &other) : _allocator(other._allocator), _data(NULL), _end(NULL), _capacity(0) {
            if (other._capacity)
                _copy_other(other);
        }

        ~vector() {
            if (_data != NULL) {
                _delete_data();
            }
        }

        vector &operator=(const vector &other) {
            if (this != &other) {
                assign(other.begin(), other.end());
            }
            return *this;
        }

        template<class InputIterator>
        void assign(InputIterator first, typename enable_if<
            is_valid_iterator_type<InputIterator, std::input_iterator_tag, pointer>::value &&
            !is_valid_iterator_type<InputIterator, std::forward_iterator_tag, pointer>::value, InputIterator>::type last) {
            for (; first != last; ++first) {
                push_back(*first);
            }
        }

        template<class ForwardIterator>
        void assign(ForwardIterator first,
                    typename enable_if<is_valid_iterator_type<ForwardIterator, std::forward_iterator_tag, pointer>::value, ForwardIterator>::type last) {
            size_type n = distance(first, last);
            if (n > _capacity) {
                _delete_data();
                _allocate(n);
                _construct_data(first, last);
            }
            else {
                if (n > size()) {
                    for (size_type i = 0; i < size(); ++first, ++i) {
                        _data[i] = *first;
                    }
                    _construct_end(first, last);
                }
                else {
                    _destroy_end_until(_data + n);
                    for (size_type i = 0; i < size(); ++i) {
                        _data[i] = *first++;
                    }
                }
            }
        }

        void assign(size_type n, const_reference val) {
            if (n > _capacity) {
                _delete_data();
                _allocate(n);
                _construct_data(_data, _end, val);
            }
            else {
                size_type      copySize = std::min(n, size());
                for (size_type i        = 0; i < copySize; ++i) {
                    _data[i] = val;
                }
                if (copySize < n)
                    _construct_end_until(_data + n, val);
                else
                    _destroy_end_until(_data + n);
            }
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
            return static_cast<size_type>(_end - _data);
        }

        size_type max_size() const {
            return min<size_type>(_allocator.max_size(), std::numeric_limits<difference_type>::min());
        }

        void resize(size_type n, value_type val = value_type()) {
            if (_capacity < n) {
                size_type newCapacity = n > _capacity * 2 ? n : _capacity * 2;
                pointer   new_data    = _allocator.allocate(newCapacity, _data);
                size_type i           = 0;
                while (i < size()) {
                    _allocator.construct(new_data + i, _data[i]);
                    ++i;
                }
                while (i < n) {
                    _allocator.construct(new_data + i, val);
                    ++i;
                }
                _delete_data();
                _data     = new_data;
                _end      = _data + n;
                _capacity = newCapacity;
            }
            else if (n < size()) {
                _destroy_end_until(_data + n);
            }
        }

        size_type capacity() const {
            return _capacity;
        }

        bool empty() const {
            return (_end - _data) == 0;
        }

        void reserve(size_type n) {
            if (_capacity < n) {
                pointer      newData = _allocator.allocate(n);
                size_type    size_   = 0;
                for (pointer p       = _data; p != _end; ++p, ++size_) {
                    _allocator.construct(newData + size_, *p);
                }
                _delete_data();
                _data     = newData;
                _end      = _data + size_;
                _capacity = n;
            }
        }

        reference operator[](size_type n) {
            return _data[n];
        }

        const_reference operator[](size_type n) const {
            return _data[n];
        }

        reference at(size_type n) {
            if (n >= size())
                throw std::out_of_range("vector");
            return _data[n];
        }

        const_reference at(size_type n) const {
            if (n >= size())
                throw std::out_of_range("vector");
            return _data[n];
        }

        reference front() {
            return *_data;
        }

        const_reference front() const {
            return *_data;
        }

        reference back() {
            return *(_end - 1);
        }

        const_reference back() const {
            return *(_end - 1);
        }

        void push_back(const_reference x) {
            if (_capacity == 0) {
                size_type n = 1;
                _allocate(n);
                --_end;
            }
            else if (size() >= _capacity) {
                size_type n       = _capacity * 2;
                pointer   newData = _allocator.allocate(n, _data);
                size_type i       = 0;
                while (i < size()) {
                    _allocator.construct(newData + i, _data[i]);
                    ++i;
                }
                _delete_data();
                _data     = newData;
                _end      = _data + i;
                _capacity = n;
            }
            _allocator.construct(_end++, x);
        }

        void pop_back() {
            _allocator.destroy(--_end);
        }

        iterator insert(iterator position, const T &x) {
            pointer   pos = &*position;
            size_type id  = pos - _data; // todo rework
            if (size() >= _capacity) {
                size_type n       = _capacity == 0 ? 1 : _capacity * 2;
                pointer   newData = _allocator.allocate(n);
                size_type i       = 0;
                while (_data + i != pos) {
                    _allocator.construct(newData + i, _data[i]);
                    ++i;
                }
                _allocator.construct(newData + i++, x);
                while (_data + i <= _end) {
                    _allocator.construct(newData + i, _data[i - 1]);
                    ++i;
                }
                _delete_data();
                _data     = newData;
                _end      = _data + i;
                _capacity = n;
            }
            else {
                if (size() != 0) {
                    _allocator.construct(_end, *(_end - 1));
                    for (pointer p = _end - 1; p > pos; --p) {
                        *p = *(p - 1);
                    }
                }
                *pos = x;
                ++_end;
            }
            return iterator(_data + id);
        }

        void insert(iterator position, size_type n, const T &x) {
            pointer pos = &*position;
            if (size() + n >= _capacity) {
                size_type newCapacity = _capacity == 0 ? n : _capacity * 2;
                pointer   newData     = _allocator.allocate(newCapacity, _data);
                size_type i           = 0;
                while (_data + i != pos) {
                    _allocator.construct(newData + i, _data[i]);
                    ++i;
                }
                for (size_type j = 0; j < n; ++j, ++i) {
                    _allocator.construct(newData + i, x);
                }
                while (_data + i - n != _end) {
                    _allocator.construct(newData + i, _data[i - n]);
                    ++i;
                }
                _delete_data();
                _data     = newData;
                _end      = _data + i;
                _capacity = newCapacity;
            }
            else {
                pointer        p = _end - 1;
                for (size_type i = 0; i < n; ++i) {
                    _allocator.construct(p + n + i, *(p + i));
                }
                for (; p != pos + n; --p) {
                    *p = *(p - 1);
                }
                while (p >= pos) {
                    *p = x;
                    --p;
                }
                _end += n;
            }
        }

        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            while (first != last) {
                position = insert(position, *first++);
                ++position;
            }
        }

        iterator erase(iterator position) {
            difference_type pos = position - begin();
            pointer         p   = _data + pos;
            _allocator.destroy(p);
            if (p + 1 != _end) {
                _allocator.construct(p, *(p + 1));
                for (++p; p < _end - 1; ++p) {
                    *p = *(p + 1);
                }
                _allocator.destroy(--_end);
            }
            else
                --_end;
            return iterator(_data + pos);
        }

        iterator erase(iterator first, iterator last) {
            return 1 + last + first - first;
        }

        void swap(vector<T, Alloc> &other) {
            pointer        data      = _data;
            pointer        end       = _end;
            allocator_type allocator = _allocator;
            size_type      capacity  = _capacity;

            _data      = other._data;
            _end       = other._end;
            _allocator = other._allocator;
            _capacity  = other._capacity;

            other._data      = data;
            other._end       = end;
            other._allocator = allocator;
            other._capacity  = capacity;
        }

        void clear() {
            while (_data != _end) {
                _allocator.destroy(--_end);
            }
        }

    private:

        allocator_type _allocator;
        pointer        _data;
        pointer        _end;
        size_type      _capacity;

        void _allocate(size_type n) {
            if (n > max_size())
                throw std::length_error("vector");
            _data     = _allocator.allocate(n);
            _end      = _data + n;
            _capacity = n;
        }

        void _delete_data() {
            clear();
            if (_capacity)
                _allocator.deallocate(_data, _capacity);
            _capacity = 0;
        }

        void _copy_other(const vector &other) {
            _data     = _allocator.allocate(other._capacity);
            _end      = _data + other.size();
            _capacity = other._capacity;
            _construct_data(other.begin(), other.end());
        }

        template<typename Iterator>
        void _construct_data(Iterator begin, Iterator end) {
            for (pointer p = _data; begin != end; ++p, ++begin) {
                _allocator.construct(p, *begin);
            }
        }

        void _construct_data(pointer begin, pointer end, const_reference value) {
            for (pointer p = begin; p != end; ++p) {
                _allocator.construct(p, value);
            }
        }

        template<typename Iterator>
        void _construct_end(Iterator begin, Iterator end) {
            while (begin != end) {
                _allocator.construct(_end, *begin++);
                ++_end;
            }
        }

        void _construct_end_until(pointer end, const_reference value) {
            for (; _end != end; ++_end) {
                _allocator.construct(_end, value);
            }
        }

        void _destroy_end_until(pointer new_end) {
            while (new_end != _end) {
                _allocator.destroy(--_end);
            }
        }

    };

    template<class T, class Allocator>
    bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
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
    bool operator<(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
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
    bool operator!=(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
        return !(x == y);
    }

    template<class T, class Allocator>
    bool operator>(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
        return y < x;
    }

    template<class T, class Allocator>
    bool operator>=(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
        return !(x < y);
    }

    template<class T, class Allocator>
    bool operator<=(const vector<T, Allocator> &x, const vector<T, Allocator> &y) {
        return !(y < x);
    }

    template<class T, class Allocator>
    void swap(vector<T, Allocator> &x, vector<T, Allocator> &y) {
        x.swap(y);
    }

};

#endif
