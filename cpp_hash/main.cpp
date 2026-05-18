#include <iostream>
#include <string>
#include <fstream>  // Requisito para leer archivos
#include <sstream>  // Requisito para procesar las líneas del CSV

using namespace std;

// 1. Estructura extendida según el formato oficial del proyecto
struct Estudiante {
    int id;
    string nombre;
    string career;
    int semester;
    double gpa;
    int skill_score;
};

struct Nodo {
    Estudiante estudiante;
    Nodo* siguiente;
};

class HashTable {
private:
    static const int SIZE = 10;
    Nodo* tabla[SIZE];
    int totalElementos;
    int totalColisiones;

    int funcionHash(int id) {
        return id % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            tabla[i] = nullptr;
        }
        totalElementos = 0;
        totalColisiones = 0;
    }

    // 2. Modificado para recibir el objeto Estudiante completo
    bool insertar(Estudiante est) {
        // Validar ID duplicado
        if (buscar(est.id) != nullptr) {
            cout << "Error: ya existe un estudiante con el ID " << est.id << " (Omitido).\n";
            return false;
        }

        int indice = funcionHash(est.id);

        Nodo* nuevo = new Nodo;
        nuevo->estudiante = est; // Copia todos los atributos de golpe
        nuevo->siguiente = nullptr;

        // Si ya hay algo en el bucket, hay colisión
        if (tabla[indice] != nullptr) {
            totalColisiones++;
        }

        // Insertar al inicio de la lista enlazada (como estaba en tu base)
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;

        totalElementos++;
        return true;
    }

    Estudiante* buscar(int id) {
        int indice = funcionHash(id);
        Nodo* actual = tabla[indice];

        while (actual != nullptr) {
            if (actual->estudiante.id == id) {
                return &actual->estudiante;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool eliminar(int id) {
        int indice = funcionHash(id);
        Nodo* actual = tabla[indice];
        Nodo* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->estudiante.id == id) {
                // 3. Ajuste de colisiones: si el nodo a eliminar causaba colisión, restarla
                if (anterior != nullptr || actual->siguiente != nullptr) {
                    totalColisiones--;
                }

                if (anterior == nullptr) {
                    tabla[indice] = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }

                delete actual;
                totalElementos--;

                cout << "Estudiante eliminado correctamente.\n";
                return true;
            }

            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "No se encontro estudiante con ese ID.\n";
        return false;
    }

    void mostrarTabla() {
        cout << "\n--- CONTENIDO DE LA HASH TABLE (POR BUCKET) ---\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "Bucket [" << i << "]: ";
            Nodo* actual = tabla[i];

            if (actual == nullptr) {
                cout << "vacio";
            }

            while (actual != nullptr) {
                cout << "(" << actual->estudiante.id << ", "
                     << actual->estudiante.nombre << ", "
                     << actual->estudiante.career << ") -> ";
                actual = actual->siguiente;
            }
            cout << "NULL\n";
        }
    }

    void mostrarEstadisticas() {
        cout << "\n--- ESTADISTICAS HASH ---\n";
        cout << "Total de estudiantes cargados: " << totalElementos << endl;
        cout << "Total de buckets: " << SIZE << endl;
        cout << "Total de colisiones generadas: " << totalColisiones << endl;
        cout << "Factor de carga: " << calcularFactorCarga() << endl;
    }

    float calcularFactorCarga() {
        return (float) totalElementos / SIZE;
    }

    // 4. Nueva función para procesar la carga masiva desde el CSV
    void cargarDesdeCSV(string nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << nombreArchivo << "\n";
            return;
        }

        string linea;
        // Leer y saltar la línea de encabezados (student_id, full_name...)
        getline(archivo, linea);

        int cargadosExito = 0;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue; // Ignorar líneas vacías

            stringstream ss(linea);
            string campo;
            Estudiante est;

            try {
                getline(ss, campo, ','); est.id = stoi(campo);
                getline(ss, est.nombre, ',');
                getline(ss, est.career, ',');
                getline(ss, campo, ','); est.semester = stoi(campo);
                getline(ss, campo, ','); est.gpa = stod(campo);
                getline(ss, campo, ','); est.skill_score = stoi(campo);

                if (insertar(est)) {
                    cargadosExito++;
                }
            } catch (...) {
                cout << "Error al procesar la linea: " << linea << " (Formato incorrecto)\n";
            }
        }
        archivo.close();
        cout << "\n>>> Carga masiva finalizada. Se cargaron " << cargadosExito << " estudiantes exitosamente.\n";
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
    }
};

int main() {
    // REQUISITO OBLIGATORIO: Mostrar tus datos en consola para las capturas del PDF
    cout << "===========================================\n";
    cout << "Estudiante: [Edwin Oswaldo Cortez Tista]\n";
    cout << "Carne: [9921 24 7626]\n";
    cout << "===========================================\n";

    HashTable hash;
    int opcion;

    do {
        cout << "\n========== MENU HASH TABLE ==========\n";
        cout << "1. Carga masiva desde CSV (estudiantes.csv)\n";
        cout << "2. Buscar estudiante por ID\n";
        cout << "3. Eliminar estudiante por ID\n";
        cout << "4. Mostrar tabla hash por bucket\n";
        cout << "5. Mostrar estadisticas de la tabla\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            // Llama de forma automatizada al archivo solicitado
            hash.cargarDesdeCSV("estudiantes.csv");
        }
        else if (opcion == 2) {
            int id;
            cout << "Ingrese ID a buscar: ";
            cin >> id;

            Estudiante* encontrado = hash.buscar(id);
            if (encontrado != nullptr) {
                cout << "\n--- Estudiante Encontrado ---\n";
                cout << "ID: " << encontrado->id << "\n";
                cout << "Nombre: " << encontrado->nombre << "\n";
                cout << "Carrera: " << encontrado->career << "\n";
                cout << "Semestre: " << encontrado->semester << "\n";
                cout << "GPA: " << encontrado->gpa << "\n";
                cout << "Skill Score: " << encontrado->skill_score << "\n";
            } else {
                cout << "Estudiante no encontrado.\n";
            }
        }
        else if (opcion == 3) {
            int id;
            cout << "Ingrese ID a eliminar: ";
            cin >> id;
            hash.eliminar(id);
        }
        else if (opcion == 4) {
            hash.mostrarTabla();
        }
        else if (opcion == 5) {
            hash.mostrarEstadisticas();
        }
        else if (opcion == 6) {
            cout << "Saliendo del programa...\n";
        }
        else {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}