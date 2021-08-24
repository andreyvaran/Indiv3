//
// Created by mosco on 01.05.2021.
//
#include <iostream>
#include <fstream>
#include "my_tree_set.h"
#include <cassert>
void test() {
    my_tree_set t1, t2;
    t1 += 1;
    t1 += 3;
    t1 += 2;
    t1 += 2;
    t1 += 4;
    std::cout << t1 << '\n';
    t2 += 10;
    t2 += 2;
    t2 += 8;
    t2 += 7;
    t2 += 6;
    std::cout << t2 << '\n';
    t1 * t2;
    std::cout << t1 << '\n';
    my_tree_set t3, t4;
    t3 += 1;
    t3 += 2;
    t3 += 4;
    t4 += 1;
    t4 += 2;
    t4 += 6;
    assert(t3 != t4);
    std::cout << (t3 == t4) << std::endl;

    std::ifstream fin1("file1.txt");
    std::ifstream fin2("file2.txt");
    my_tree_set t5, t6;


    while (!fin1.eof()) {
        int x;
        fin1 >> x;
        t5 += x;
    }

    while (!fin2.eof()) {
        int x;
        fin2 >> x;
        t6 += x;
    }
    //assert(t5 == t6);
    std::cout << t5 << '\n';
    std::cout << t6 << '\n';
    std::cout << (t5 == t6) << std::endl;

}

