#include <iostream>
#include <fstream>
#include <memory>

class IMediciones {

public:

    virtual void imprimir() const = 0;
    virtual void serializar(std::ofstream&) const = 0;
    virtual void deserializar(std::ifstream&) = 0;
    virtual ~IMediciones() {}

};

class MedicionBase : public IMediciones {
    
protected:

    std::unique_ptr<float> tiempoMedicion;

public:

    MedicionBase(float t) {
        tiempoMedicion = std::make_unique<float>(t);
    }

    MedicionBase(const MedicionBase& other) {
        tiempoMedicion = std::make_unique<float>(*other.tiempoMedicion);
    }

    float getTiempo() const {
        return *tiempoMedicion;
    }

    virtual void imprimir() const = 0;
    virtual ~MedicionBase() {}

};


class Presion : public MedicionBase {

public:

    float presionEstatica, presionDinamica;

    Presion(float p, float q, float t) : MedicionBase(t), presionEstatica(p), presionDinamica(q) {}

    Presion(const Presion& other) : MedicionBase(other), presionEstatica(other.presionEstatica), presionDinamica(other.presionDinamica) {}

    void serializar(std::ofstream& out) const override {

        out.write(reinterpret_cast<const char*>(&presionEstatica), sizeof(float));
        out.write(reinterpret_cast<const char*>(&presionDinamica), sizeof(float));
        out.write(reinterpret_cast<const char*>(tiempoMedicion.get()), sizeof(float));
    }

    void deserializar(std::ifstream& in) override {

        in.read(reinterpret_cast<char*>(&presionEstatica), sizeof(float));
        in.read(reinterpret_cast<char*>(&presionDinamica), sizeof(float));
        float t;
        in.read(reinterpret_cast<char*>(&t), sizeof(float));
        tiempoMedicion = std::make_unique<float>(t);
    }

    void imprimir() const override {

        std::cout << "Presion - Estatica: " << presionEstatica
                  << ", Dinamica: " << presionDinamica
                  << ", Tiempo: " << *tiempoMedicion << "\n";
    }
};

class Posicion : public MedicionBase {

public:

    float latitud, longitud, altitud;

    Posicion(float lat, float lon, float alt, float t) : MedicionBase(t), latitud(lat), longitud(lon), altitud(alt) {}

    Posicion(const Posicion& other) : MedicionBase(other), latitud(other.latitud), longitud(other.longitud), altitud(other.altitud) {}

    void serializar(std::ofstream& out) const override {

        out.write(reinterpret_cast<const char*>(&latitud), sizeof(float));
        out.write(reinterpret_cast<const char*>(&longitud), sizeof(float));
        out.write(reinterpret_cast<const char*>(&altitud), sizeof(float));
        out.write(reinterpret_cast<const char*>(tiempoMedicion.get()), sizeof(float));
    }

    void deserializar(std::ifstream& in) override {

        in.read(reinterpret_cast<char*>(&latitud), sizeof(float));
        in.read(reinterpret_cast<char*>(&longitud), sizeof(float));
        in.read(reinterpret_cast<char*>(&altitud), sizeof(float));
        float t;
        in.read(reinterpret_cast<char*>(&t), sizeof(float));
        tiempoMedicion = std::make_unique<float>(t);
    }

    void imprimir() const override {

        std::cout << "Posicion - Lat: " << latitud
                  << ", Lon: " << longitud
                  << ", Alt: " << altitud
                  << ", Tiempo: " << *tiempoMedicion << "\n";
    }
};

class SaveFlightData {

private:

    Posicion posicion;
    Presion presion;

public:

    SaveFlightData(const Posicion& p, const Presion& q) : posicion(p), presion(q) {}

    void serializar(std::ofstream& out) const {
        posicion.serializar(out);
        presion.serializar(out);
    }

    void deserializar(std::ifstream& in) {
        posicion.deserializar(in);
        presion.deserializar(in);
    }

    void imprimir() const {
        std::cout << "--- Datos de Vuelo ---\n";
        posicion.imprimir();
        presion.imprimir();
        std::cout << "----------------------\n";
    }
};


int main() {

    // Crear mediciones
    Posicion pos(-34.6f, -58.4f, 950.0f, 5.3f);
    Presion pres(101.3f, 5.8f, 6.1f);

    // Guardar datos
    SaveFlightData vuelo(pos, pres);

    // Serializar a archivo
    std::ofstream archivoOut("vuelo.datos", std::ios::binary);

    if (archivoOut) {

        vuelo.serializar(archivoOut);
        archivoOut.close();
    }

    // Crear objeto vacío y deserializar desde archivo

    SaveFlightData vueloLeido(pos, pres);  // se usa como base para deserializar

    std::ifstream archivoIn("vuelo.datos", std::ios::binary);
    
    if (archivoIn) {
        vueloLeido.deserializar(archivoIn);
        archivoIn.close();
    }

    // Imprimir resultado
    vueloLeido.imprimir();

    return 0;
}
