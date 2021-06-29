#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

    struct false_type {
        static const bool value = false;
    };

    struct true_type {
        static const bool value = true;
    };

    template<class T>
    struct remove_const {
        typedef T type;
    };
    template<class T>
    struct remove_const<const T> {
        typedef T type;
    };

    template<class T, class U>
    struct is_same : public false_type {
    };

    template<class T>
    struct is_same<T, T> : public true_type {
    };

    template<bool, class T = void>
    struct enable_if {
    };
    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<class T, class U, class Ptr>
    struct is_valid_iterator_type {
    private:
        struct _char2 {
            char one;
            char two;
        };

        template<class T1>
        static _char2 f(enable_if<is_same<typename T1::iterator_category, U>::value, Ptr> T1::* = 0);

        template<class T1>
        static char f(...);

    public:
        static const bool value = sizeof(f<T>(0)) == sizeof(_char2) || is_same<T, Ptr>::value;
    };

    template<typename T>
    void swap(T &a, T &b) {
        T c = a;
        a = b;
        b = c;
    }

}

#endif
