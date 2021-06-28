#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

    template<class Type>
    struct LessThanPredicate {
        bool operator()(const Type &x, const Type &y) const {
            return x < y;
        }
    };

    template<class Type>
    struct EqualToPredicate {
        bool operator()(Type x, Type y) const {
            return x == y;
        }
    };

    template<class Type>
    struct EqualToValuePredicate {
        explicit EqualToValuePredicate(const Type &val) : value(val) {}
        bool operator()(Type x) const { return x == value; }
        Type value;
    };

    template<typename T>
    inline T &min(T &a, T &b) {
        return a < b ? a : b;
    }

    template<typename T>
    inline T &max(T &a, T &b) {
        return a > b ? a : b;
    }

    template<typename T>
    inline const T &min(const T &a, const T &b) {
        return a < b ? a : b;
    }

    template<typename T>
    inline const T &max(const T &a, const T &b) {
        return a > b ? a : b;
    }

}

#endif
