#include <vector>
#include "vector.hpp"
#include <iostream>

template<typename T>
void printVectorInfo(std::vector<T> const& vector) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << std::endl;
}
template<typename T>
void printVectorInfo(ft::vector<T> const& vector) {
    std::cout << "empty: " << vector.empty() << std::endl;
    std::cout << "size: " << vector.size() << std::endl;
    std::cout << "max_size: " << vector.max_size() << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << std::endl;
}

int main() {
    ft::vector<int>  fv;
    ft::vector<int>  fv1(0);
    ft::vector<int>  fv2(10);
    std::vector<int> sv;
    std::vector<int> sv1 = std::vector<int>();
    std::vector<int> sv2(0);
    std::vector<int> sv3(10);
    printVectorInfo(sv);
    printVectorInfo(sv1);
    printVectorInfo(sv2);
    printVectorInfo(sv3);
    printVectorInfo(fv);
    printVectorInfo(fv1);
    printVectorInfo(fv2);
    std::cout << "> ";
//    std::cout << fv2.begin() << " " << fv.end() << std::endl;
    int i = 0;
    for (ft::vector<int>::iterator it = fv2.begin(); it != fv2.end(); ++it) {
        std::cout << ++i << ": " << *it << std::endl;
    }
    std::cout << "> ";
    std::iterator<ft::vector<int>, ft::vector<int>::value_type> iterator;
}
