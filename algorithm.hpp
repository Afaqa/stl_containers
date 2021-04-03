#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

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
