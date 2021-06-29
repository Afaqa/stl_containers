#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

    template <class T>
    struct has_iterator_typedefs
    {
    private:
        struct _char2 {
            char one;
            char two;
        };
        template <class _Up> static _char2 test(...);
        template <class _Up> static char test(typename std::__void_t<typename _Up::iterator_category>::type*,
                                               typename std::__void_t<typename _Up::difference_type>::type*,
                                               typename std::__void_t<typename _Up::value_type>::type*,
                                               typename std::__void_t<typename _Up::reference>::type*,
                                               typename std::__void_t<typename _Up::pointer>::type*
        );
    public:
        static const bool value = sizeof(test<T>(0,0,0,0,0)) == sizeof(char);
    };

    template<class It, bool>
    struct _iterator_traits {};

    template<class It>
    struct _iterator_traits<It, true>
    {
        typedef typename It::difference_type   difference_type;
        typedef typename It::value_type        value_type;
        typedef typename It::pointer           pointer;
        typedef typename It::reference         reference;
        typedef typename It::iterator_category iterator_category;
    };

    template<class It>
    struct iterator_traits : _iterator_traits<It, has_iterator_typedefs<It>::value> {};

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
