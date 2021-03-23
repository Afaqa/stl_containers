#include <vector>
#include "vector.hpp"
#include <iostream>

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
        std::cout << ++i << ": " << *it << std::endl;
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
    std::vector<int> sv2(0);
    std::vector<int> *sv3 = new std::vector<int>(10, 15);
//    printVectorInfo(sv);
//    printVectorInfo(sv1);
//    printVectorInfo(sv2);
//    printVectorInfo(*sv3);
    printVectorInfo(fv);
    printVectorInfo(fv1);
    printVectorInfo(*fv2);
}
