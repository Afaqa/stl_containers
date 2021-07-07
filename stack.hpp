#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace stl {
    template<class T, class Container = list <T> >
    class stack {
    public:
        typedef T                                  value_type;
        typedef Container                          container_type;
        typedef typename container_type::size_type size_type;

        explicit stack(const container_type &ctnr = container_type())
            : _container(ctnr) {
        }

        bool empty() const {
            return _container.empty();
        }

        size_type size() const {
            return _container.size();
        }

        value_type &top() {
            return _container.back();
        }

        const value_type &top() const {
            return _container.back();
        }

        void push(const value_type &val) {
            _container.push_back(val);
        }

        void pop() {
            _container.pop_back();
        }

    protected:
        container_type _container;
        template<class T1, class C1>
        friend bool operator==(const stack<T1, C1> &lhs,
                               const stack<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator!=(const stack<T1, C1> &lhs,
                               const stack<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator<(const stack<T1, C1> &lhs,
                              const stack<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator<=(const stack<T1, C1> &lhs,
                               const stack<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator>(const stack<T1, C1> &lhs,
                              const stack<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator>=(const stack<T1, C1> &lhs,
                               const stack<T1, C1> &rhs);
    };

    template<class T, class Container>
    bool
    operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container == rhs._container;
    }

    template<class T, class Container>
    bool
    operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container != rhs._container;
    }

    template<class T, class Container>
    bool
    operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container < rhs._container;
    }

    template<class T, class Container>
    bool
    operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container <= rhs._container;
    }

    template<class T, class Container>
    bool
    operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container > rhs._container;
    }

    template<class T, class Container>
    bool
    operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs._container >= rhs._container;
    }
}

#endif
