#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
private:
    int nelem;           // número de elementos
    BSNode<T>* root;     // nodo raíz

    // ===== funciones auxiliares =====
    void insert(BSNode<T>*& n, const T& e);
    bool search(BSNode<T>* n, const T& e) const;
    void print_inorder(std::ostream& out, BSNode<T>* n) const;
    void destroy(BSNode<T>* n);
    BSNode<T>* remove(BSNode<T>* n, const T& e);
    BSNode<T>* findMin(BSNode<T>* n) const;

public:
    // ===== constructor / destructor =====
    BSTree();
    ~BSTree();

    // ===== operaciones básicas =====
    bool empty() const;
    int size() const;

    void insert(const T& e);
    bool search(const T& e) const;
    void remove(const T& e);

    void print_inorder(std::ostream& out) const;
};

/* ======================================================
   IMPLEMENTACIÓN
   ====================================================== */

template <typename T>
BSTree<T>::BSTree() : nelem(0), root(nullptr) {}

template <typename T>
BSTree<T>::~BSTree() {
    destroy(root);
}

template <typename T>
bool BSTree<T>::empty() const {
    return root == nullptr;
}

template <typename T>
int BSTree<T>::size() const {
    return nelem;
}

/* ---------------- INSERCIÓN ---------------- */

template <typename T>
void BSTree<T>::insert(const T& e) {
    insert(root, e);
}

template <typename T>
void BSTree<T>::insert(BSNode<T>*& n, const T& e) {
    if (n == nullptr) {
        n = new BSNode<T>(e);
        nelem++;
    } else if (e < n->elem) {
        insert(n->left, e);
    } else if (e > n->elem) {
        insert(n->right, e);
    }
    // si e == n->elem → no se insertan duplicados
}

/* ---------------- BÚSQUEDA ---------------- */

template <typename T>
bool BSTree<T>::search(const T& e) const {
    return search(root, e);
}

template <typename T>
bool BSTree<T>::search(BSNode<T>* n, const T& e) const {
    if (n == nullptr) return false;
    if (e == n->elem) return true;
    if (e < n->elem) return search(n->left, e);
    return search(n->right, e);
}

/* ---------------- RECORRIDO INORDER ---------------- */

template <typename T>
void BSTree<T>::print_inorder(std::ostream& out) const {
    print_inorder(out, root);
}

template <typename T>
void BSTree<T>::print_inorder(std::ostream& out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

/* ---------------- ELIMINACIÓN ---------------- */

template <typename T>
void BSTree<T>::remove(const T& e) {
    root = remove(root, e);
}

template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, const T& e) {
    if (n == nullptr) return nullptr;

    if (e < n->elem) {
        n->left = remove(n->left, e);
    } else if (e > n->elem) {
        n->right = remove(n->right, e);
    } else {
        // nodo encontrado
        if (n->left == nullptr) {
            BSNode<T>* tmp = n->right;
            delete n;
            nelem--;
            return tmp;
        }
        if (n->right == nullptr) {
            BSNode<T>* tmp = n->left;
            delete n;
            nelem--;
            return tmp;
        }
        // dos hijos
        BSNode<T>* min = findMin(n->right);
        n->elem = min->elem;
        n->right = remove(n->right, min->elem);
    }
    return n;
}

template <typename T>
BSNode<T>* BSTree<T>::findMin(BSNode<T>* n) const {
    while (n->left != nullptr)
        n = n->left;
    return n;
}

/* ---------------- DESTRUCCIÓN ---------------- */

template <typename T>
void BSTree<T>::destroy(BSNode<T>* n) {
    if (n != nullptr) {
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

#endif
