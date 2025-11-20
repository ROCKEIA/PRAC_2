#ifdef HASHTABLE_H
#define HASHTABLE_H
#include "C:\Users\rocke\OneDrive\Documentos\GitHub\Practica1\Listlinked.h"
#include "Dict.h"
#include "TableEntry.h"
#include <ostream>
#include <stdexcept>
#include <iostream>
#include <string>

typename<typename V>
class HashTable<V> : Dict<V> {
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>> *table;
		int h(std::string key){
			//FUNCION EN LA TABLA QUE DEVUELVE LA SUMA DE LOS VALORES ASCII Y EL TAMAÑO DEL HASH
			int sum = 0;
			size_str = key.size();
			for( int i = 1; i <= size_str; ++i){
				char aux = key.at(i)
				sum = sum + std:string::int(aux);
			}
			pos = sum % max;
			return pos;
		};
	public:
		HashTable(int size){//METODO QUE RESERVARA LA MEMORIA DINAMICA PARA CREAR UNA TABLA DE TAMAÑO SIZE E INICIALIZARA LOS ATRIBUTOS N Y MAX DE LA CLASE
			n = 0;
			max = size;
			table = new ListLinked<TableEntry<V>>[max];
		};
//METODO DESTRUCTOR QUE SE ENCARGA DE LIBERAR MEMORIA DINAMICA RESERVADA PARA CREAR LA TABLA
		~HashTable(){
			detele[] table;;
		};
			//DEVUELVE EL NUMERO TOTAL DE LOS CUBETAS DE LA TABLA
		int capacity(){
			return max;
		};
//SOBRECARGA DEL OPERADOR PARA IMPRIMIR EL CONTENIDO DE LA TABLA HASH
		friend std::ostream&operator<<(std::ostream out, const HashTable<V> &th){
			out << "Contenido de las cubetas de la tabla: \n";
			for(int i = 0;i < th.max; i++){
				out << th.table[i] << "\n";
			}
			return out
		};
		V operator[](std::string key){
			int pos = h(key);
			confir = table[pos].search(TableEntry<V>(key)); // Search para vee si existe la clave // 
			if(confir == -1){
				throw std::runtime_error("LLave no encontrada")
			}
			return table[pos][confir].value;
		};
		void insert(std::string key, V value) override{
			int pos = h(key);
			confir = table[pos].search(TableEntry<V>(key));
			if(confir != -1){
				throw std::runtime_error("La llave ya existe");
			}
			TableEntry<V> Cubeta_nueva(key, value);
			table[pos].prepend(Cubeta_nueva);
			n++;
		};
		V search(std::string key) override{
			int pos = h(key);
			confir = table[pos].search(TableEntry<V>(key));
			if(confir == -1){
				throw std::runtime_error("llave no encontrada");
			}
			return confir;
		};
		V remove(std::string key) override{
			int pos = h(key);
			confir = table[pos].search(TableEntry<V>(key));
			if(confir == -1){
				throw std::runtime_error;
			}
			V data_eliminada = table[pos][confir].value;
			table[pos].remove();
			n--;
			return data_eliminada;
		};
		int entries() override{
			return n;
		};
};

#endif
