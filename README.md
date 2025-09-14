[![ITESM](https://img.shields.io/badge/Instituci%C3%B3n-ITESM-blue)](https://tec.mx)
[![Curso](https://img.shields.io/badge/Curso-EDyAF%20(Gpo%20604)-0b6efd)]()
[![Actividad](https://img.shields.io/badge/Actividad-2--HashTable-green)]()

# 🧩 Actividad 2 — Implementación de una Tabla Hash

**Programación de estructuras de datos y algoritmos fundamentales (Gpo 604)**  
**Instituto Tecnológico y de Estudios Superiores de Monterrey**

---

## 👥 Integrantes del equipo

| Nombre                        | Matrícula |
| ----------------------------- | --------- |
| Ángel Landín López            | A00574700 |
| Ángeles Araiza García         | A00574806 |
| Carlos Andrés Gloria Cortes   | A00574714 |
| Mónica Isabel Torres García   | A00573457 |

---

## 🏷 Nombre de la actividad
**Actividad 2 - Implementación de una tabla Hash**

---

## 📂 Estructura del proyecto

```
.
├─ HashTable.h        // Declaración: Node, HashTable y firmas
├─ HashTable.cpp      // Implementación: hash, set, get, remove, printTable, keys
└─ main.cpp           // Casos de prueba y demostración (secuencia reproducible)
```

---

## 🧠 Resumen del proyecto

Implementación educativa en **C++** de una **HashTable** (tamaño fijo) con:

- `SIZE = 13` (tabla estática para prácticas).
- Función hash basada en acumulación con número primo `p = 23`.
- Resolución de colisiones por **Quadratic Probing**.
- Borrado lógico mediante **Tombstone** (`isDeleted = true`) con reutilización.

---

## 🔧 Componentes principales

### `Node` (HashTable.h)
- `std::string key;`  
- `int value;`  
- `bool isDeleted;` // tombstone flag

### `HashTable` (HashTable.h / HashTable.cpp)
- `static const int SIZE = 13;`  
- `Node* dataMap[SIZE];`  
- Métodos principales:
  - `void set(const std::string& key, int value);`
  - `int get(const std::string& key) const;`
  - `void remove(const std::string& key);`
  - `std::vector<std::string> keys() const;`
  - `void printTable() const;`
  - `int getHashIndex(const std::string& key) const;`
  - `int hash(const std::string& key) const;`

---

## 📐 Detalles técnicos

### 🔢 Función hash (versión GitHub-friendly)

**Fórmula (texto plano):**

```
h(k) = ( Σ_{j=0}^{|k|-1} ascii(k[j]) * p ) mod m
```

Lo mismo explicado:

- `h(k)` = índice resultante para la clave `k`.  
- `ascii(k[j])` = valor ASCII del carácter en la posición `j` de la clave.  
- `p` = primo multiplicador (en esta implementación `p = 23`).  
- `m` = tamaño de la tabla (`SIZE = 13` en el código).

**Forma expandida (más legible):**

```
h(k) = ( ascii(k[0])*p + ascii(k[1])*p + ... + ascii(k[|k|-1])*p ) % m
```

---

### 🔍 Ejemplo numérico (rápido)

Clave: `"A"` → `ascii('A') = 65`

Cálculo paso a paso:

- producto: `65 * 23 = 1495`  
- módulo: `1495 % 13 = 0`

Por tanto: `h("A") = 0` — coincide con las pruebas del programa.

---

### 🧾 Implementación (C++)

```cpp
int HashTable::hash(const std::string& key) const {
    int h = 0;
    const int prime = 23;   // p = 23
    for (size_t i = 0; i < key.length(); ++i) {
        int asciiValue = static_cast<int>(key[i]);
        h = (h + asciiValue * prime) % SIZE; // SIZE = m = 13
    }
    return h;
}
```

---

### 🔁 Quadratic Probing

**Fórmula (texto plano):**

```
index_i = ( h(k) + i^2 ) % m   for i = 0,1,2,...
```

**Implementación (extracto):**

```cpp
int index = (originalHash + i * i) % SIZE;
```

**Comentario:** reduce clustering primario frente a linear probing. Elegir `m` primo mejora cobertura.

---

### 🪓 Tombstone (borrado lógico)

- `remove(key)` marca el nodo con `isDeleted = true` en vez de liberar el puntero.  
- `set` recuerda la primera posición con tombstone y la reutiliza si aparece un `nullptr` después.  
- Evita romper la cadena de búsqueda en probing abierto.

**Fragmento (marca tombstone):**

```cpp
if (!dataMap[newIndex]->isDeleted && dataMap[newIndex]->key == key) {
    dataMap[newIndex]->isDeleted = true;
    return;
}
```

---

## 🖼 Diagramas (SVG) — Instrucciones

Markwon puede no renderizar HTML/SVG inline; para máxima compatibilidad en GitHub y Markwon sigue estos pasos:

1. Crea la carpeta `diagrams/` en tu repo.  
2. Crea `diagrams/quadratic_probing.svg` y pega el contenido del bloque "Diagrama A" (más abajo).  
3. Crea `diagrams/tombstone_reuse.svg` y pega el contenido del bloque "Diagrama B" (más abajo).  
4. En el README inserta las imágenes con:

```markdown
![Quadratic Probing](diagrams/quadratic_probing.svg)
![Tombstone Reuse](diagrams/tombstone_reuse.svg)
```

> Si Markwon no muestra SVGs, convierte los SVG a PNG y enlázalos igual.

---

### Diagrama A — Quadratic Probing (guardar en `diagrams/quadratic_probing.svg`)

```svg
<!-- Guarda esto en diagrams/quadratic_probing.svg -->
<svg width="980" height="120" viewBox="0 0 980 120" xmlns="http://www.w3.org/2000/svg">
  <style>
    .box { fill:#f8f9fa; stroke:#343a40; stroke-width:1.5; }
    .idx { font: 12px monospace; fill:#495057; }
    .key { font: 13px monospace; fill:#0d6efd; font-weight:700; }
    .step { fill:#ffc107; stroke:#b88600; stroke-width:1.2; opacity:0.95; }
    .arrow { stroke:#198754; stroke-width:2; marker-end:url(#arrowhead); }
  </style>
  <defs>
    <marker id="arrowhead" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#198754" />
    </marker>
  </defs>

  <g transform="translate(10,10)">
    <g>
      <rect x="0"   y="0" width="72" height="48" class="box"/>
      <rect x="74"  y="0" width="72" height="48" class="box"/>
      <rect x="148" y="0" width="72" height="48" class="box"/>
      <rect x="222" y="0" width="72" height="48" class="box"/>
      <rect x="296" y="0" width="72" height="48" class="box"/>
      <rect x="370" y="0" width="72" height="48" class="box"/>
      <rect x="444" y="0" width="72" height="48" class="box"/>
      <rect x="518" y="0" width="72" height="48" class="box"/>
      <rect x="592" y="0" width="72" height="48" class="box"/>
      <rect x="666" y="0" width="72" height="48" class="box"/>
      <rect x="740" y="0" width="72" height="48" class="box"/>
      <rect x="814" y="0" width="72" height="48" class="box"/>
      <rect x="888" y="0" width="72" height="48" class="box"/>
    </g>

    <g>
      <text x="36"  y="30" class="idx">0</text>
      <text x="110" y="30" class="idx">1</text>
      <text x="184" y="30" class="idx">2</text>
      <text x="258" y="30" class="idx">3</text>
      <text x="332" y="30" class="idx">4</text>
      <text x="406" y="30" class="idx">5</text>
      <text x="480" y="30" class="idx">6</text>
      <text x="554" y="30" class="idx">7</text>
      <text x="628" y="30" class="idx">8</text>
      <text x="702" y="30" class="idx">9</text>
      <text x="776" y="30" class="idx">10</text>
      <text x="850" y="30" class="idx">11</text>
      <text x="924" y="30" class="idx">12</text>
    </g>

    <rect x="0" y="0" width="72" height="48" class="step" />
    <text x="20" y="28" class="key">Ocupado</text>

    <path d="M36,58 L110,78" class="arrow" />
    <path d="M110,78 L332,78" class="arrow" />
    <path d="M332,78 L702,78" class="arrow" />

    <rect x="74"  y="0" width="72" height="48" fill="#e9ecef" stroke="#adb5bd"/>
    <text x="90" y="28" class="idx">probe i=1</text>

    <rect x="296" y="0" width="72" height="48" fill="#e9ecef" stroke="#adb5bd"/>
    <text x="312" y="28" class="idx">probe i=2</text>

    <rect x="666" y="0" width="72" height="48" fill="#e9ecef" stroke="#adb5bd"/>
    <text x="682" y="28" class="idx">probe i=3</text>

    <text x="0" y="110" font-family="sans-serif" font-size="12" fill="#495057">
      Ejemplo: h(k) = 0. Probing secuencia: 0 → 1 → 4 → 9  (i^2 mod m).
    </text>
  </g>
</svg>
```

---

### Diagrama B — Tombstone y reutilización (guardar en `diagrams/tombstone_reuse.svg`)

```svg
<!-- Guarda esto en diagrams/tombstone_reuse.svg -->
<svg width="980" height="140" viewBox="0 0 980 140" xmlns="http://www.w3.org/2000/svg">
  <style>
    .box { fill:#f8f9fa; stroke:#343a40; stroke-width:1.5; }
    .idx { font: 12px monospace; fill:#495057; }
    .active { fill:#d1e7dd; stroke:#0f5132; }
    .tomb { fill:#ffe5d0; stroke:#b45309; }
    .new { fill:#cfe2ff; stroke:#084298; }
  </style>

  <g transform="translate(10,10)">
    <rect x="0"   y="0" width="72" height="48" class="box"/>
    <rect x="74"  y="0" width="72" height="48" class="box"/>
    <rect x="148" y="0" width="72" height="48" class="box"/>
    <rect x="222" y="0" width="72" height="48" class="box"/>
    <rect x="296" y="0" width="72" height="48" class="box"/>
    <rect x="370" y="0" width="72" height="48" class="box"/>
    <rect x="444" y="0" width="72" height="48" class="box"/>
    <rect x="518" y="0" width="72" height="48" class="box"/>
    <rect x="592" y="0" width="72" height="48" class="box"/>
    <rect x="666" y="0" width="72" height="48" class="box"/>
    <rect x="740" y="0" width="72" height="48" class="box"/>
    <rect x="814" y="0" width="72" height="48" class="box"/>
    <rect x="888" y="0" width="72" height="48" class="box"/>

    <g>
      <text x="36"  y="30" class="idx">0</text>
      <text x="110" y="30" class="idx">1</text>
      <text x="184" y="30" class="idx">2</text>
      <text x="258" y="30" class="idx">3</text>
      <text x="332" y="30" class="idx">4</text>
      <text x="406" y="30" class="idx">5</text>
      <text x="480" y="30" class="idx">6</text>
      <text x="554" y="30" class="idx">7</text>
      <text x="628" y="30" class="idx">8</text>
      <text x="702" y="30" class="idx">9</text>
      <text x="776" y="30" class="idx">10</text>
      <text x="850" y="30" class="idx">11</text>
      <text x="924" y="30" class="idx">12</text>
    </g>

    <rect x="0" y="0" width="72" height="48" class="tomb"/>
    <text x="8" y="28" font-family="monospace" font-size="12" fill="#b45309">Tombstone</text>

    <rect x="148" y="0" width="72" height="48" class="active"/>
    <text x="166" y="28" font-family="monospace" font-size="13" fill="#0f5132">Aaron</text>

    <rect x="296" y="0" width="72" height="48" class="active"/>
    <text x="314" y="28" font-family="monospace" font-size="13" fill="#0f5132">Olivia</text>

    <rect x="74"  y="0" width="72" height="48" class="active"/>
    <text x="92" y="28" font-family="monospace" font-size="13" fill="#0f5132">A</text>

    <line x1="184" y1="58" x2="36" y2="110" stroke="#0d6efd" stroke-width="2" marker-end="url(#arr)"/>
    <defs>
      <marker id="arr" markerWidth="8" markerHeight="6" refX="7" refY="3" orient="auto">
        <polygon points="0 0, 8 3, 0 6" fill="#0d6efd"/>
      </marker>
    </defs>
    <text x="400" y="110" font-family="sans-serif" font-size="12" fill="#495057">
      Inserción de "Nueva": reaprovecha la posición marcada como Tombstone en índice 0.
    </text>
  </g>
</svg>
```

---

## 🧪 Casos de prueba y salida (formato elegante)

> La salida que produjo `main.cpp`, reformateada para mayor claridad.

### Inserciones iniciales (Moni, Aaron, Olivia)

| Índice | Contenido        |
|:------:|:----------------:|
| 0      | {Moni, 100}      |
| 1      | {Null, -1}       |
| 2      | {Null, -1}       |
| 3      | {Null, -1}       |
| 4      | {Aaron, 50}      |
| 5      | {Null, -1}       |
| 6      | {Null, -1}       |
| 7      | {Null, -1}       |
| 8      | {Null, -1}       |
| 9      | {Null, -1}       |
| 10     | {Olivia, 80}     |
| 11     | {Null, -1}       |
| 12     | {Null, -1}       |

**Gets:**
- `Moni: 100`  
- `Aaron: 50`  
- `Olivia: 80`  
- `Ferrari (no existe): -1`

**Índices base (hash) para colisiones:**
- `hash('A') = 0`  
- `hash('h') = 0`  
- `hash('N') = 0`

---

### Insertando claves que colisionan: `A`, `D`, `N`

| Índice | Contenido        |
|:------:|:----------------:|
| 0      | {Moni, 100}      |
| 1      | {A, 1}           |
| 2      | {Null, -1}       |
| 3      | {Null, -1}       |
| 4      | {Aaron, 50}      |
| 5      | {D, 2}           |
| 6      | {Null, -1}       |
| 7      | {Null, -1}       |
| 8      | {Null, -1}       |
| 9      | {N, 3}           |
| 10     | {Olivia, 80}     |
| 11     | {Null, -1}       |
| 12     | {Null, -1}       |

---

### Actualizar, Tombstone y reutilización

- `set("Aaron", 500)` → `Aaron ahora: 500`  
- `remove("Moni")` → `get("Moni") = -1` (tombstone en índice 0)  
- `set("Nueva", 999)` → reutiliza tombstone (índice 0) → `get("Nueva") = 999`

---

### Llenado parcial y eliminación inexistente

Intento de insertar `K1..K4` y `remove("Ferrari")` (sin efecto). Estado final (parcial):

| Índice | Contenido        |
|:------:|:----------------:|
| 0      | {K4, 13}         |
| 1      | {A, 1}           |
| 2      | {Nueva, 999}     |
| 3      | {K2, 11}         |
| 4      | {Aaron, 500}     |
| 5      | {D, 2}           |
| 6      | {K1, 10}         |
| 7      | {Null, -1}       |
| 8      | {Null, -1}       |
| 9      | {N, 3}           |
| 10     | {Olivia, 80}     |
| 11     | {Null, -1}       |
| 12     | {K3, 12}         |

**Keys activas:** `K4 A Nueva K2 Aaron D K1 N Olivia K3`

---

## 🧾 Cómo compilar y ejecutar

```bash
g++ -std=c++17 HashTable.cpp main.cpp -o hashtable
./hashtable
# En Windows:
# hashtable.exe
```

---

## ⚖️ Complejidad y observaciones

- `set/get/remove`: promedio O(1), peor caso O(m), donde `m` = tamaño de la tabla.  
- **Limitaciones actuales:**
  - Tabla estática (`SIZE = 13`) — no hay rehash automático.  
  - Acumulación de tombstones puede degradar rendimiento con el tiempo.  
- **Mejoras recomendadas:**
  - Implementar *rehash* (resize a primo mayor) cuando el load factor supere un umbral (ej. 0.6).  
  - Rehash periódico para limpiar tombstones.  
  - Soportar `template<K,V>` y/o usar `std::hash` para generalizar.

---

## 🧾 Licencia & Créditos

Trabajo académico para **Programación de estructuras de datos y algoritmos fundamentales (Gpo 604)** — **ITESM**.  
Implementado y documentado por: **Ángel Landín, Ángeles Araiza, Carlos Andrés Gloria, Mónica Isabel Torres**.

---

