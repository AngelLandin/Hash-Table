#include <iostream>
#include <vector>
#include "HashTable.h"

using namespace std;

int main() {
    HashTable* ht = new HashTable();

    cout << "=== Inserciones iniciales (Moni, Aaron, Olivia) ===\n";
    ht->set("Moni", 100);
    ht->set("Aaron", 50);
    ht->set("Olivia", 80);
    ht->printTable();

    cout << "Gets:\n";
    cout << "Moni: " << ht->get("Moni") << "\n";
    cout << "Aaron: " << ht->get("Aaron") << "\n";
    cout << "Olivia: " << ht->get("Olivia") << "\n";
    cout << "Ferrari (no existe): " << ht->get("Ferrari") << "\n\n";

    // Forzar/observar colisiones
    cout << "Índices base (hash) para colisiones:\n";
    cout << "hash('A') = " << ht->getHashIndex("A") << "\n";
    cout << "hash('h') = " << ht->getHashIndex("h") << "\n";
    cout << "hash('N') = " << ht->getHashIndex("N") << "\n\n";

    cout << "=== Insertando claves que colisionan: A, H, O ===\n";
    ht->set("A", 1);
    ht->set("D", 2);
    ht->set("N", 3); // puede fallar si probing no encuentra hueco
    ht->printTable();

    cout << "Nota: la inserción de 'O' puede fallar (mensaje de 'tabla llena') dependiendo del probing y del tamaño del Hash Table.\n\n";

    // Actualizar valor existente
    cout << "=== Actualizar Aaron -> 500 ===\n";
    ht->set("Aaron", 500);
    cout << "Aaron ahora: " << ht->get("Aaron") << "\n\n";

    // Borrar y reutilización tombstone
    cout << "=== Borrar 'Moni' (tombstone) y luego insertar 'Nueva' ===\n";
    ht->remove("Moni");
    cout << "Después de remove('Moni'), get('Moni') = " << ht->get("Moni") << " (esperado -1)\n";
    ht->printTable();

    ht->set("Nueva", 999);
    cout << "Después de insertar 'Nueva', get('Nueva') = " << ht->get("Nueva") << "\n";
    ht->printTable();
    cout << "Reutilización/tombstone comprobada (según política de probing)\n\n";

    // Llenar la tabla para provocar 'tabla llena' en algunas inserciones
    cout << "=== Intento de llenar la tabla con K1..K4 ===\n";
    ht->set("K1", 10);
    ht->set("K2", 11);
    ht->set("K3", 12);
    ht->set("K4", 13); // algunas inserciones pueden printar "tabla llena"
    ht->printTable();

    cout << "=== Intentar eliminar clave inexistente 'Ferrari' (no debe cambiar nada) ===\n";
    ht->remove("Ferrari"); // no debe crash
    ht->printTable();
    cout << "Eliminar inexistente OK\n\n";

    // Listar keys activas
    cout << "=== Keys activas ===\n";
    vector<string> allKeys = ht->keys();
    for (auto &k : allKeys){
        cout << k << " ";
    }
    cout << "\n\n";

    delete ht;
    return 0;
}
