//
// Created by mosco on 01.05.2021.
//

#ifndef INDIV3_MY_TREE_SET_H
#define INDIV3_MY_TREE_SET_H

#include <vector>
#include <iostream>
#include <algorithm>

//5. Упорядоченное множество на базе двоичного дерева
//Множество — абстрактная структура данных, которая позволяет хранить
//значения определённого типа в порядке, который бы обеспечивал быструю
//проверку наличия/отсутствия элемента во множестве. Использовать дерево
//поиска для представления множества. В узле дерева хранится значение.
//Класс должен содержать методы:
// проверка наличия элемента в множестве;
// мощность множества – количество элементов множества;
// сравнения множеств на равенство.
//Для класса необходимо перегрузить следующие операции:
// operator+= — добавление элемента;
// operator-= — исключение элемента;
// operator + — объединение множеств;
// operator * — пересечение множеств;
// вывод в поток.

//Используя множество целых чисел решить следующую задачу: Даны два
//файла целых чисел. Проверить, содержат ли эти файлы одинаковые наборы чисел,
//не учитывая, сколько раз число встречается в файле. Например, следующие
//файлы содержат одинаковые наборы чисел:
//1 3 3 2 1 7
//2 7 1 3 7

class my_tree_set {
public:
    class node {
    public:
        int key;
        int height;
        node *left;
        node *right;

        node(int k) {
            height = 1;
            key = k;
            left = nullptr;
            right = nullptr;
        }
    };

    node *root = nullptr;
    int value_;
    int num_elements;


    void operator+=(int value) {
        root = insertUtil(root, value);
    }

    void operator-=(int value) {
        root = removeUtil(root, value);
    }

    friend std::ostream &operator<<(std::ostream &os, my_tree_set &tree) {
        inorderUtil(tree.root, os);
        return os;
    }


    bool operator==(my_tree_set &second_tree) {
        std::vector<int> values1, values2;
        this->getValues(this->root, values1);
        getValues(second_tree.root, values2);
        std::sort(values1.begin(), values1.end());
        std::sort(values2.begin(), values2.end());
        return std::equal(values1.begin(), values1.end(), values2.begin());
    }
    bool operator!=(my_tree_set &second_tree) {
        return !(*this == second_tree);
    }
    my_tree_set &operator+(my_tree_set &second_tree) {
        std::vector<int> values;
        getValues(second_tree.root, values);
        for (int value : values) {
            //std::cout<< value << std::endl;
            if (this->search(value) == nullptr) {
                *this += value;
            }
        }
        return *this;
    }

    node *search(int x) {
        return searchUtil(root, x);
    }

    my_tree_set &operator*(my_tree_set &tree) {
        std::vector<int> values;
        this->getValues(this->root, values);
        for (int value : values) {
            if (tree.search(value) == nullptr) {
                *this -= value;
            }
        }
        return *this;
    }

private:

    int height(node *head) {
        if (head == nullptr) return 0;
        return head->height;
    }

    node *rightRotation(node *head) {
        node *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + std::max(height(head->left), height(head->right));
        newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node *leftRotation(node *head) {
        node *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + std::max(height(head->left), height(head->right));
        newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    void inorderUtil(node *head) {
        if (head == nullptr) return;
        inorderUtil(head->left);
        std::cout << head->key << " ";
        inorderUtil(head->right);
    }

    static void inorderUtil(node *head, std::ostream &os) {
        if (head == nullptr) return;
        inorderUtil(head->left, os);
        os << head->key << " ";
        inorderUtil(head->right, os);
    }

    void getValues(node *head, std::vector<int> &ans) {
        if (head == nullptr) {
            return;
        }
        getValues(head->left, ans);
        ans.push_back(head->key);
        getValues(head->right, ans);
    }

    node *insertUtil(node *head, int x) {
        if (head == nullptr) {
            num_elements += 1;
            node *temp = new node(x);
            return temp;
        }
        if (x < head->key) head->left = insertUtil(head->left, x);
        else if (x > head->key) head->right = insertUtil(head->right, x);
        head->height = 1 + std::max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (x < head->left->key) {
                num_elements += 1;
                return rightRotation(head);
            } else {
                head->left = leftRotation(head->left);
                num_elements += 1;
                return rightRotation(head);
            }
        } else if (bal < -1) {
            if (x > head->right->key) {
                num_elements += 1;
                return leftRotation(head);
            } else {
                head->right = rightRotation(head->right);
                num_elements += 1;
                return leftRotation(head);
            }
        }
        return head;
    }
    ///
    /// \param head
    /// \param x
    /// \return
    node *removeUtil(node *head, int x) {
        if (head == nullptr) return nullptr;
        if (x < head->key) {
            head->left = removeUtil(head->left, x);
        } else if (x > head->key) {
            head->right = removeUtil(head->right, x);
        } else {
            node *r = head->right;
            if (head->right == nullptr) {
                node *l = head->left;
                delete (head);
                head = l;
            } else if (head->left == nullptr) {
                delete (head);
                head = r;
            } else {
                while (r->left != nullptr) r = r->left;
                head->key = r->key;
                head->right = removeUtil(head->right, r->key);
            }
        }
        if (head == nullptr) return head;
        head->height = 1 + std::max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (height(head->left) >= height(head->right)) {
                return rightRotation(head);
            } else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        } else if (bal < -1) {
            if (height(head->right) >= height(head->left)) {
                return leftRotation(head);
            } else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    ///
    /// \param head
    /// \param x
    /// \return
    node *searchUtil(node *head, int x) {
        if (head == nullptr) return nullptr;
        int k = head->key;
        if (k == x) return head;
        if (k > x) return searchUtil(head->left, x);
        if (k < x) return searchUtil(head->right, x);
    }




};



#endif //INDIV3_MY_TREE_SET_H
