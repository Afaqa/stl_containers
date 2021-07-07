### This project is educational and is marked public exclusively to show  my progress as a developer since june 2021. ###

---

## STL containers ##

---

This is an implementation if C++98 STL containers: vector, list, map, stack, queue; 
and related to them: allocator, iterators, enable_if;
without features of containers added on C++11 and later.

All containers are tested using GoogleTest framework.

#### This project was tested with the following: ####
- cmake 3.17
- make 4.3
- clang++ 12.0.0
- MacOS 10.14 Mojave

_Some features may not work correctly on other setups_

#### Usage ####

```shell
make all;          # to create testing binary
./stl_containers;  # to run tests
```
