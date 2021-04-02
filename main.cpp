#include <vector>
#include "vector.hpp"
#include "iterator.hpp"
#include <iostream>
#include <deque>

template<typename T>
void printVectorInfo(std::vector<T> const& vector, bool print = true) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    if (print) {
        int i = 0;
        std::cout << "<start> ";
        for (typename std::vector<T>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
            std::cout << ++i << ": " << *it << std::endl;
        }
        std::cout << "<end> " << std::endl;
    }
    std::cout << std::endl;
}
template<typename T>
void printVectorInfo(ft::vector<T> & vector, bool print = true) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    if (print) {
        int i = 0;
        std::cout << "<start> ";
        for (typename ft::vector<T>::iterator it = vector.begin(); it != vector.end(); ++it) {
            std::cout << (i + 1) << ": " << *it << " (iterator) | " << vector[i] << " ([])" << std::endl;
            ++i;
        }
    }
    std::cout << "<end> " << std::endl;
    std::cout << std::endl;
}

int main1() {
    const std::size_t start_size = 15;
    const std::size_t v_size = 2200;

    ft::vector<std::string, std::allocator<std::string> > fv(start_size);
    std::string v;
    for (ft::vector<std::string>::size_type i = 0; i < v_size; ++i, v.push_back(static_cast<char>((31 + i * 3) % 127))) {
        fv.push_back(v);
    }
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << (i + 1) << ": " << fv[i] << std::endl;
    }
    std::cout << "last val: " << fv[fv.size() - 1] << std::endl;
    printVectorInfo(fv, false);
    std::vector<std::string, std::allocator<std::string> > sv(start_size);
    v.clear();
    for (std::vector<std::string>::size_type i = 0; i < v_size; ++i, v.push_back(static_cast<char>((31 + i * 3) % 127))) {
        sv.push_back(v);
    }
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << (i + 1) << ": " << sv[i] << std::endl;
    }
    std::cout << "last val: " << sv[sv.size() - 1] << std::endl;
    printVectorInfo(sv, false);
    while (fv.size())
        fv.pop_back();
    while (sv.size())
        sv.pop_back();
    return 0;
}

int main2() {
    ft::vector<int>  fv;
    ft::vector<int>  fv1(0);
    ft::vector<int>  *fv2 = new ft::vector<int>(10, 15);
    std::vector<int> sv;
    std::vector<int> sv1 = std::vector<int>();
    std::deque<int> aa;
    std::string a[10] = {"1", "22", "333", "4444", "55555", "666666", "7777777", "88888888", "999999999"};
    ft::vector<std::string> a1(a+3, a + 9);
    std::vector<std::string> a2(a+3, a + 9);
    std::vector<int> sv2(0);
    std::vector<int> *sv3 = new std::vector<int>(10, 15);
    ft::vector<int>  *fv3 = new ft::vector<int>(sv3->begin(), sv3->end());
    std::vector<int> *sv4 = new std::vector<int>(fv2->begin(), fv2->end());
    ft::input_iterator<int> ftitstart(&fv2->begin()[0]);
    ft::input_iterator<int> ftitend(&fv2->end()[0]);
    ft::vector<int>  *fv4 = new ft::vector<int>(ftitstart, ftitend);
    std::vector<int> *sv5 = new std::vector<int>(ftitstart, ftitend);
//    printVectorInfo(a2);
    printVectorInfo(sv);
    printVectorInfo(sv1);
    printVectorInfo(sv2);
    printVectorInfo(*sv3);
    printVectorInfo(*sv4);
    sv4->assign(sv4->size(), 120);
    printVectorInfo(*sv4);
    sv4->assign(sv4->size() - 4, 30);
    printVectorInfo(*sv4);
    sv4->assign(sv4->size() + 10, 12);
    printVectorInfo(*sv4);
    printVectorInfo(*sv5);
    printVectorInfo(fv);
    printVectorInfo(fv1);
    printVectorInfo(*fv2);
    printVectorInfo(*fv3);
    fv3->assign(fv3->size(), 120);
    printVectorInfo(*fv3);
    fv3->assign(fv3->size() - 4, 30);
    printVectorInfo(*fv3);
    fv3->assign(fv3->size() + 10, 12);
    printVectorInfo(*fv3);
    printVectorInfo(*fv4);
    printVectorInfo(a1);
    printVectorInfo(a2);
    delete fv2, delete fv3, delete fv4;
    delete sv3, delete sv4, delete sv5;
    return 0;
}

int main3() {
    ft::vector<std::string> fv;
    std::vector<std::string> sv;
    fv.insert(fv.begin(), "");
    sv.insert(sv.begin(), "");
    printVectorInfo(fv);
    printVectorInfo(sv);
    fv.erase(fv.begin());
    sv.erase(sv.begin());
    printVectorInfo(fv);
    printVectorInfo(sv);
    std::string strings[] = {"first", "second", "third", "forth", "fifth"};
    fv.insert(fv.begin(), strings, strings + 5);
    sv.insert(sv.begin(), strings, strings + 5);
    printVectorInfo(fv);
    printVectorInfo(sv);
    fv.insert(++++++fv.begin(), "insertSingle");
    sv.insert(++++++sv.begin(), "insertSingle");
    printVectorInfo(fv);
    printVectorInfo(sv);
    fv.insert(++++++++++fv.begin(), 5, "insertMultiple");
    sv.insert(++++++++++sv.begin(), 5, "insertMultiple");
    printVectorInfo(fv);
    printVectorInfo(sv);
    std::string iterstr[] = {"1iter1", "2iter2", "3iter3", "4iter4", "5iter5"};
    ft::vector<std::string> vec(iterstr, iterstr + 5);
    fv.insert(++fv.begin(), vec.begin(), vec.end());
    sv.insert(++sv.begin(), vec.begin(), vec.end());
    printVectorInfo(fv);
    printVectorInfo(sv);
    fv.insert(++++++++++++++++++++++fv.begin(), "lastInsert");
    sv.insert(++++++++++++++++++++++sv.begin(), "lastInsert");
    printVectorInfo(fv);
    printVectorInfo(sv);
    fv.erase(++++++++++++fv.begin());
    sv.erase(++++++++++++sv.begin());
    printVectorInfo(fv);
    printVectorInfo(sv);
    return 0;
}

int main() {
    return main3();
}
