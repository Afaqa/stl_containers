#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

namespace ft {

    template<typename T>
    class input_iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        typedef T                           value_type;
        typedef std::ptrdiff_t              difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::input_iterator_tag     iterator_category;

        input_iterator() : _data() {}
        input_iterator(pointer data) : _data(data) {}
        input_iterator(input_iterator const& other) : _data(other._data) {}
        input_iterator& operator=(input_iterator const& other) {
            _data = other._data;
            return *this;
        }
        ~input_iterator() {}

        input_iterator& operator++() {
            ++_data;
            return *this;
        }
        input_iterator operator++(int) {
            input_iterator ret(_data);
            ++*this;
            return ret;
        }

        bool operator==(input_iterator const& other) const { return _data == other._data; }
        bool operator!=(input_iterator const& other) const { return !(*this == other); }

        reference operator*() { return *_data; }
        pointer operator->() { return _data; }

    private:

        pointer _data;

    };

    template<typename T>
    class output_iterator : public std::iterator<std::output_iterator_tag, T> {
    public:
        typedef T                           value_type;
        typedef std::ptrdiff_t              difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::output_iterator_tag    iterator_category;

        output_iterator() : _data() {}
        output_iterator(pointer data) : _data(data) {}
        output_iterator(output_iterator const& other) : _data(other._data) {}
        output_iterator& operator=(output_iterator const& other) {
            _data = other._data;
            return *this;
        }
        ~output_iterator() {}

        output_iterator& operator++() {
            ++_data;
            return *this;
        }

        output_iterator operator++(int) {
            output_iterator ret(_data);
            ++*this;
            return ret;
        }

        reference operator*() { return *_data; }

    private:

        pointer _data;

    };

    template<typename T>
    class forward_iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        typedef T                           value_type;
        typedef std::ptrdiff_t              difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef std::forward_iterator_tag   iterator_category;

        forward_iterator() : _data() {}
        forward_iterator(pointer data) : _data(data) {}
        forward_iterator(forward_iterator const& other) : _data(other._data) {}
        forward_iterator& operator=(forward_iterator const& other) {
            _data = other._data;
            return *this;
        }
        ~forward_iterator() {}

        forward_iterator& operator++() {
            ++_data;
            return *this;
        }

        forward_iterator operator++(int) {
            forward_iterator ret(_data);
            ++*this;
            return ret;
        }

        bool operator==(forward_iterator const& other) const { return _data == other._data; }
        bool operator!=(forward_iterator const& other) const { return !(*this == other); }

        reference operator*() { return *_data; }
        pointer operator->() { return _data; }

    private:

        pointer _data;

    };

    template<typename T>
    class bidirectional_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        bidirectional_iterator() : _data() {}
        bidirectional_iterator(pointer data) : _data(data) {}
        bidirectional_iterator(bidirectional_iterator const& other) : _data(other._data) {}
        bidirectional_iterator& operator=(bidirectional_iterator const& other) {
            _data = other._data;
            return *this;
        }
        ~bidirectional_iterator() {}

        bidirectional_iterator& operator++() {
            ++_data;
            return *this;
        }

        bidirectional_iterator& operator--() {
            --_data;
            return *this;
        }

        bidirectional_iterator operator--(int) {
            bidirectional_iterator ret(_data);
            --*this;
            return ret;
        }

        bool operator==(bidirectional_iterator const& other) const { return _data == other._data; }
        bool operator!=(bidirectional_iterator const& other) const { return !(*this == other); }

        reference operator*() { return *_data; }
        pointer operator->() { return _data; }

    private:

        pointer _data;

    };

    template<typename T>
    class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;

        random_access_iterator() : _data() {}
        random_access_iterator(pointer data) : _data(data) {}
        random_access_iterator(random_access_iterator const& other) : _data(other._data) {}
        random_access_iterator& operator=(random_access_iterator const& other) {
            _data = other._data;
            return *this;
        }
        ~random_access_iterator() {}

        random_access_iterator& operator++() {
            ++_data;
            return *this;
        }

        random_access_iterator& operator--() {
            --_data;
            return *this;
        }

        random_access_iterator operator--(int) {
            random_access_iterator ret(_data);
            --*this;
            return ret;
        }

        random_access_iterator& operator+=(difference_type n) {
            _data += n;
            return *this;
        }

        random_access_iterator& operator-=(difference_type n) {
            return *this += -n;
        }

        random_access_iterator operator+(difference_type n) const {
            random_access_iterator  tmp(_data + n);
            return tmp;
        }

        random_access_iterator operator-(difference_type n) const {
            random_access_iterator  tmp(_data - n);
            return tmp;
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }

        bool operator==(random_access_iterator const& other) const { return _data == other._data; }
        bool operator!=(random_access_iterator const& other) const { return !(*this == other); }
        bool operator< (random_access_iterator const& other) const { return other._data - _data > 0; }
        bool operator> (random_access_iterator const& other) const { return other < *this; }
        bool operator>=(random_access_iterator const& other) const { return !(*this < other); }
        bool operator<=(random_access_iterator const& other) const { return !(*this > other); }

        reference operator*() { return *_data; }
        pointer operator->() { return _data; }

    private:

        pointer _data;

    };
}

#endif