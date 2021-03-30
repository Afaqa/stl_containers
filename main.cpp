#include <vector>
#include "vector.hpp"
#include "iterator.hpp"
#include <iostream>
#include <deque>

template<typename T>
void printVectorInfo(std::vector<T> const& vector) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    int i = 0;
    std::cout << "<start> ";
    for (typename std::vector<T>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << ++i << ": " << *it << std::endl;
    }
    std::cout << "<end> " << std::endl;
    std::cout << std::endl;
}
template<typename T>
void printVectorInfo(ft::vector<T> & vector) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    int i = 0;
    std::cout << "<start> ";
    for (typename ft::vector<T>::iterator it = vector.begin(); it != vector.end(); ++it) {
        vector[i] += 5;
        std::cout << (i + 1) << ": " << *it << " (iterator) | " << vector[i] << " ([])" << std::endl;
        ++i;
    }
    std::cout << "<end> " << std::endl;
    std::cout << std::endl;
}

int main() {
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
    delete fv2;
    delete sv3;
}
