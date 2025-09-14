#include "HashTable.h"
#include <iostream>

using namespace std;

// ---------------- HashTable ----------------
HashTable::HashTable() {
    // Inicializamos el dataMap con nullptr (vacío)
    for (int i = 0; i < SIZE; i++) dataMap[i] = nullptr;
}

// Destructor
HashTable::~HashTable() {
    //Recorremos todo el dataMap
    for (int i = 0; i < SIZE; i++) {
        if (dataMap[i] != nullptr) { // Verifica si esta vacío en la posición i
            delete dataMap[i]; // Liberamos la memoria, para evitar fugas de memoria.
        }
    }
}

//Función Hash
int HashTable::hash(const std::string& key) const {
    int h = 0; // Variable que almacenará el indice
    int prime = 23; // Número primo
    // Iterador para calcular el indice donde se almacenará el Node
    for (size_t i = 0; i < key.length(); i++) {
        int asciiValue = int(key[i]); // Convertirmos cada letra a su valor en ASCII
        // Función Hash que cálculo el índice 
        h = (h + asciiValue * prime) % SIZE; // Numero primo para mejorar la distribución de las claves y reducir colisiones
    }
    // Retornamos el índice
    return h;
}

// Función para agregar un nuevo Nodo (key: value) al Hash Table
void HashTable::set(const std::string& key, int value) {
    int originalHash = hash(key); // Calculamos el índice
    int i = 0; // Iterador
    int tombstoneIndex = -1; // Marcado como -1 si no encuentra nada de tombstone.

    // While en caso de colisión
    while (i < SIZE) {
        int index = (originalHash + i * i) % SIZE; // Técnica de Quadratic Probing

        // slot vacío -> insertar (o usar tombstone si ya lo encontramos)
        if (dataMap[index] == nullptr) {
            int finalIndex = (tombstoneIndex != -1) ? tombstoneIndex : index; // Si tombstoneIndex es diferente a -1, entonces tombstoneIndex = finalIndex, si no, tombstoneIndex = index
            if (dataMap[finalIndex] != nullptr) {
                delete dataMap[finalIndex]; // liberar tombstone si se reutiliza
            }
            dataMap[finalIndex] = new Node(key, value); // Almacenamos el Node en el Hash Table
            return;
        }

        // tombstone -> recordar primera posición borrada
        if (dataMap[index]->isDeleted == true) {
            if (tombstoneIndex == -1) {
                tombstoneIndex = index; // Ubicamos la posición libre en el tombstone
            }
        }
        // misma clave -> actualizar
        else if (dataMap[index]->key == key) {
            dataMap[index]->value = value; // Si se inserta un key que ya existe en la Hash table, solo actualizamos su valor
            return;
        }
        i++;
    }

    // Si recorrimos toda la tabla y encontramos tombstone, lo usarmos
    if (tombstoneIndex != -1) {
        // Si hay un tombstone, liberamos la memoria en la ubicación del tombstone
        delete dataMap[tombstoneIndex];
        // Una vez, liberada la memoria, almacenamos el nuevo Node
        dataMap[tombstoneIndex] = new Node(key, value);
        return;
    }

    // Mensaje cuando la Tabla está llena
    cout << "Error: HashTable llena, no se pudo insertar -> " << key << endl;
}

int HashTable::get(const std::string& key) const {
    int index = hash(key); // Obtenemos el índice con la función hash

    int newIndex = 0; // Definimos una nueva variable de índice en caso de que haya ocurrido colisión
    int i = 0;
    while (i < SIZE) {
        newIndex = (index + (i * i)) % SIZE; // Técnica Quadratic probing con direccionamiento abierto
        
        // Si no se encuentra la key a buscar en el Hash Table, retorna -1, no existe la key.
        if (dataMap[newIndex] == nullptr) { 
            return -1; 
        }

        // Verificamos si en la posición newIndex en el HashTable la key es igual a la key buscada y además que no este marcada como tombstone
        if (!dataMap[newIndex]->isDeleted && dataMap[newIndex]->key == key) {
            return dataMap[newIndex]->value; // Retorna el valor de la key buscada en el Hash Table
        }
        i++;
    }

    return -1; // Retorna -1 si no se encontro la key dentro del Hash Table
}

void HashTable::remove(const std::string& key) {
    int index = hash(key); // Obtenemos el índice con la función hash
    int newIndex = 0; // Nuevo índice en caso de que haya ocurrido colisión anteriormente al insertar el valor a remover
    int i = 0; // iterador

    // While para encontrar en base a la key el Node a "Eliminar"
    while (i < SIZE) {
        newIndex = (index + (i * i)) % SIZE; // Quadratic Probing

        // Sí en la posición del índice (newIndex) cálculado con el Quadratic Probing dentro del Hash Table, encuentra un nullptr
        // Entonces el key a remover no existe, se retorna nada.
        if (dataMap[newIndex] == nullptr) {
            return;
        }


        // Si se encuentra el Node con la key asociada, se marca como true el atributo isDeleted del Node (Tombstone)
        if (!dataMap[newIndex]->isDeleted && dataMap[newIndex]->key == key) {
            dataMap[newIndex]->isDeleted = true; // Aplicamos Tombstone para evitar que eliminar un elemento rompa la secuencia de búsqueda en direccionamiento abierto.
            return;
        }
        i++;
    }
}

// Función que almacena en un vector todas las Keys que contiene el Hash Table al momento.
vector<string> HashTable::keys() const {
    vector<string> allKeys;
    for (int i = 0; i < SIZE; i++) {
        if (dataMap[i] != nullptr && !dataMap[i]->isDeleted) {
            allKeys.push_back(dataMap[i]->key);
        }
    }
    return allKeys;
}

// Función que imprime el Hash Table
void HashTable::printTable() const {

    // Loop para recorrer todo el Hash Table
    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";

        // Si el Hash Table en la posición i no está vacío y no está marcado como Tombstone, entonces imprime el key y su value asociado
        if (dataMap[i] != nullptr && !dataMap[i]->isDeleted) {
            cout << "{" << dataMap[i]->key << ", " << dataMap[i]->value << " }" << endl;
        } 
        
        // Si el Hash Table en la posición i no está vacío pero está marcado como Tombstone, entonces imprime "{Eliminado, 0}"
        else if (dataMap[i] != nullptr && dataMap[i]->isDeleted) {
            cout << "{" << "Eliminado, " << "0 }" << endl;
        } 
        
        // Si el Hash Table en la posición i está vacío, imprime "{Null, -1}"
        else {
            cout << "{" << "Null, " << "-1 }" << endl;
        }
    }
}

// Función que retorna el valor del hash, solo usado para los casos de prueba.
int HashTable::getHashIndex(const std::string& key) const {
    return hash(key);
}
