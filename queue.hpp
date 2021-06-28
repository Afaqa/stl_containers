#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft {
    template<class T, class Container = list <T> >
    class queue {
    public:
        typedef T                                  value_type;
        typedef Container                          container_type;
        typedef typename container_type::size_type size_type;

        explicit queue(const container_type &ctnr = container_type())
            : _container(ctnr) {
        }

        bool empty() const {
            return _container.empty();
        }

        size_type size() const {
            return _container.size();
        }

        value_type &front() {
            return _container.front();
        }

        const value_type &front() const {
            return _container.front();
        }

        value_type &back() {
            return _container.back();
        }

        const value_type &back() const {
            return _container.back();
        }

        void push(const value_type &val) {
            _container.push_back(val);
        }

        void pop() {
            _container.pop_front();
        }

    private:
        container_type _container;
        template<class T1, class C1>
        friend bool operator==(const queue<T1, C1> &lhs,
                               const queue<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator!=(const queue<T1, C1> &lhs,
                               const queue<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator<(const queue<T1, C1> &lhs,
                              const queue<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator<=(const queue<T1, C1> &lhs,
                               const queue<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator>(const queue<T1, C1> &lhs,
                              const queue<T1, C1> &rhs);
        template<class T1, class C1>
        friend bool operator>=(const queue<T1, C1> &lhs,
                               const queue<T1, C1> &rhs);
    };

    template<class T, class Container>
    bool
    operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container == rhs._container;
    }

    template<class T, class Container>
    bool
    operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container != rhs._container;
    }

    template<class T, class Container>
    bool
    operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container < rhs._container;
    }

    template<class T, class Container>
    bool
    operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container <= rhs._container;
    }

    template<class T, class Container>
    bool
    operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container > rhs._container;
    }

    template<class T, class Container>
    bool
    operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
        return lhs._container >= rhs._container;
    }
}

#endif
