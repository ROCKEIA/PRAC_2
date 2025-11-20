#ifndef BSTREE_H
#define BSTREE_H
#include <ostream>
#include <iostream>
#include <stdexcept>
#include "BSNode.h"

template<typename T>
class BSTree {
    private:
        int nelem;
        BSNode<T> *root;

        const BSNode<T>* search(BSNode<T>* n, T e){
            if(n == nullptr){
                throw std::runtime_error("No se encontró el elemento");
            } else if(n->elem < e){
                return search(n->right, e);
            } else if(n->elem > e){
                return search(n->left, e);
            } else{
                return n;
            }
        }

        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n == nullptr){
                return new BSNode<T>(e);
            } else if(n->elem == e){
                throw std::runtime_error("Este objeto ya existe");
            } else if(n->elem < e){
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }

        void print_in_order(std::ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_in_order(out, n->left);
                out << n->elem << " ";
                print_in_order(out, n->right);
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            } else if(n->elem < e){
                n->right = remove(n->right, e);
            } else if(n->elem > e){
                n->left = remove(n->left, e);
            } else{
                if(n->left != nullptr && n->right != nullptr){
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                } else {
                    if(n->left != nullptr){
                        n = n->left;
                    } else {
                        n = n->right;
                    }
                }
            }
            return n;
        }

        T max(BSNode<T>* n) const{
            if(n == nullptr){
                throw std::runtime_error("Elemento no encontrado");
            } else if(n->right != nullptr){
                return max(n->right);
            } else {
                return n->elem;
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if(n->right == nullptr){
                return n->left;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }

        void delete_cascade(BSNode<T>* n){
            if(n != nullptr){
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

        int depth(BSNode<T>* n){
            if(n == nullptr){
                return 0;
            }
            int leftDepth = depth(n->left);
            int rightDepth = depth(n->right);
            return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
        }

    public:
        BSTree(){
            nelem = 0;
            root = nullptr;
        }

        const int size(){
            return nelem;
        }

        const T search(T e){
            return search(root, e)->elem;
        }

        const T operator[](T e){
            return search(e);
        }

        void insert(T e){
            root = insert(root, e);
            nelem++;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_in_order(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root, e);
            nelem--;
        }

        ~BSTree(){
            delete_cascade(root);
        }
};

#endif

