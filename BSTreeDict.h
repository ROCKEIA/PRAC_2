#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
/*    BSTreeDict();
    ~BSTreeDict();

    V operator[](std::string key);
*/
    friend std::ostream& operator<<(std::ostream &out,
                                    const BSTreeDict<V> &bs) {
// He modificado esta línea y la he cambiado por la siguiente        bs.tree->print_inorder(out);
        out << *(bs.tree);
        return out;
    }
//};

/* ======================================================
   IMPLEMENTACIÓN
   ====================================================== */

/*template <typename V>*/
//He eliminado BSTreeDict<V>:: de delante en la siguiente línea
BSTreeDict() {
    tree = new BSTree<TableEntry<V>>();
}

//template <typename V>
//He eliminado BSTreeDict<V>:: de delante en la siguiente línea
~BSTreeDict() {
    delete tree;
}

/*
 * Acceso / inserción:
 *  - si la clave existe → devuelve el valor
 *  - si no existe → se inserta con valor por defecto
 */
//template <typename V>
/*V BSTreeDict<V>::operator[](std::string key) {
    TableEntry<V> entry(key, V{});

    if (!tree->search(entry)) {
        tree->insert(entry);
    }

    // Ahora seguro que existe: lo buscamos para devolver su valor
    // (BSTree no devuelve nodos, así que usamos un recorrido)
    // SOLUCIÓN habitual en prácticas: lanzar excepción si no está
    // o modificar BSTree para devolver referencia.
    // Aquí usamos una excepción controlada:
    throw std::logic_error("operator[] requiere acceso por referencia (no soportado)");
}
*/
//Para la sobrecarga de este operador utilizamos el método search.
V operator[](std::string key) {
        return search(key);
}
    //Faltaba añadir lo siguiente. Se han de implementar los métodos virtuales puros de Dict
    // Inserción
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    // Búsqueda
    V search(std::string key) override {
        TableEntry<V> entry(key);
        return tree->search(entry).value;
    }

    // Eliminación
    V remove(std::string key) override {
        TableEntry<V> entry(key);
        V value = tree->search(entry).value;
        tree->remove(entry);
        return value;
    }

    // Número de entradas
    int entries() override {
        return tree->size();
    }
};
#endif



