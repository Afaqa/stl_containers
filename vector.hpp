#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {

    template <typename T>
    class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
    {};

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

        explicit vector(const allocator_type& alloc = allocator_type()) {

        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {

        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {

        }

        vector(const vector& x) {

        }

        ~vector() {}

        vector& operator=(const vector& x) {

        }

    };

};

#endif
