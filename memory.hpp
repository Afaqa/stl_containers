#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <limits>

namespace ft {

    template<class T>
    class allocator;

    template<>
    class allocator<void> {
    public:
        typedef void       *pointer;
        typedef const void *const_pointer;
        typedef void       value_type;
        template<class U>
        struct rebind {
            typedef allocator<U> other;
        };
    };

    template<class T>
    class allocator {
    public:
        typedef T              value_type;
        typedef T              *pointer;
        typedef T              &reference;
        typedef const T        *const_pointer;
        typedef const T        &const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        template<class U>
        struct rebind {
            typedef allocator<U> other;
        };

        allocator() throw() {}

        template<class U>
        allocator(const allocator<U> &) throw() {}

        ~allocator() throw() {}

        pointer address(reference x) const {
            return &x;
        }

        const_pointer address(const_reference x) const {
            return &x;
        }

        pointer allocate(size_type n, allocator<void>::const_pointer = 0) {
            if (n > max_size())
                throw std::length_error("allocator<T>::allocate(size_t n)"
                                        " 'n' exceeds maximum supported size");
            return static_cast<pointer>(::operator new(n * sizeof(value_type)));
        }

        void deallocate(pointer p, size_type) {
            ::operator delete(p);
        }

        size_type max_size() const throw() {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }

        void construct(pointer p, const_reference val) {
            new((void *) p) value_type(val);
        }

        void destroy(pointer p) {
            p->~value_type();
        }
    };
}

#endif
