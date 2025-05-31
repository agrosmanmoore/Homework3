#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Clase 1: Generador de datos
class DataGenerator {

public:

    std::vector<double> doubles;
    std::vector<std::string> strings;
    std::vector<std::vector<int>> listas;

    // template para agregar datos al vector correcto
    template<typename T>

    void agregarDato(const T& dato) {

        if constexpr (std::is_same_v<T, double>) {
            doubles.push_back(dato);  // Si es double, lo guarda en doubles

        } else if constexpr (std::is_same_v<T, std::string>) {
            strings.push_back(dato);  // Si es string, lo guarda en strings

        } else {

            static_assert(!sizeof(T*), "Tipo de dato equivocado");
        }

    }

    // Agregar matriz de enteros (para "listas")
    void agregarLista(const std::vector<int>& fila) {
        listas.push_back(fila);
    }
};

// Clase 2: Constructor del JSON
class JsonBuilder {

private:

    DataGenerator& data;  // Referencia a los datos generados

public:

    JsonBuilder(DataGenerator& generator) : data(generator) {}

    // Método para construir e imprimir el JSON
    void imprimirJSON() {

        std::ostringstream out;

        out << "{\n";

        // Vec_doubles
        out << "  \"vec_doubles\" : [";

        for (size_t i = 0; i < data.doubles.size(); ++i) {

            out << data.doubles[i];

            if (i < data.doubles.size() - 1) out << ", ";
        }
        out << "],\n";

        // Palabras
        out << "  \"palabras\" : [";

        for (size_t i = 0; i < data.strings.size(); ++i) {

            out << "\"" << data.strings[i] << "\"";

            if (i < data.strings.size() - 1) out << ", ";
        }
        out << "],\n";

        // Listas (matriz de enteros)
        out << "  \"listas\" : [\n";

        for (size_t i = 0; i < data.listas.size(); ++i) {

            out << "    [";

            for (size_t j = 0; j < data.listas[i].size(); ++j) {
                out << data.listas[i][j];

                if (j < data.listas[i].size() - 1) out << ", ";
            }

            out << "]";

            if (i < data.listas.size() - 1) out << ",";
            
            out << "\n";
        }
        out << "  ]\n";

        out << "}\n";

        std::cout << out.str();  // Imprimir el JSON final
    }
};

// Función principal
int main() {
    DataGenerator generador;

    // Agregar doubles
    generador.agregarDato(1.3);
    generador.agregarDato(2.1);
    generador.agregarDato(3.2);

    // Agregar palabras
    generador.agregarDato(std::string("Hola"));
    generador.agregarDato(std::string("Mundo"));

    // Agregar listas
    generador.agregarLista({1, 2});
    generador.agregarLista({3, 4});

    // Crear el constructor de JSON y mostrarlo
    JsonBuilder builder(generador);
    builder.imprimirJSON();

    return 0;
}
