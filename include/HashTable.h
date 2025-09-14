#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <iostream> // para printTable()

// Clase Node que almacena {key: value}
class Node {
public:
    std::string key; // Atributo Key
    int value; // Atributo value
    bool isDeleted; // Atributo que se encargara del tombstone

    //Constructor de la clase Node
    Node(const std::string& key, int value) 
        : key(key), value(value), isDeleted(false) {}
};

class HashTable {
private:
    static const int SIZE = 13; // Definimos el tamaño en 13
    Node* dataMap[SIZE]; // Array de Node de tamaño 13, almacenará las {key : value}

    int hash(const std::string& key) const; // Firma de la funcion hash

public:
    HashTable(); // Firma Constructor
    ~HashTable(); // Firma Destructor

    // Firmas de las operaciones principales
    void set(const std::string& key, int value);
    int get(const std::string& key) const;
    void remove(const std::string& key);

    // utilidades
    std::vector<std::string> keys() const;
    void printTable() const;

    // sólo para pruebas / depuración
    int getHashIndex(const std::string& key) const;
};

#endif // HASH_TABLE_H
