#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

    template<class Type>
    class LessThanPredicate {
    public:
        bool operator()(Type x, Type y) {
            return x < y;
        }
    };

    template<class Type>
    class EqualToPredicate {
    public:
        bool operator()(Type x, Type y) {
            return x == y;
        }
    };

    template<class Type, Type value>
    class EqualToValuePredicate {
    public:
        bool operator()(Type x) {
            return x == value;
        }
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
