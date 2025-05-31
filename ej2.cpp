#include <iostream>
using namespace std;

class Punto {
private:
    float x, y;

public:
    Punto(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    void setX(float x_) { x = x_; }
    void setY(float y_) { y = y_; }

    float getX() const { return x; }
    float getY() const { return y; }
};

class Circulo {
private:
    Punto centro;
    float radio;

public:
    Circulo(float r) : radio(r) {}

    void setRadio(float r) { radio = r; }

    float getRadio() const { return radio; }
    Punto getCentro() const { return centro; }
};

class Elipse {
private:
    float radioMayor, radioMenor;

public:
    Elipse(float rM, float rmen) : radioMayor(rM), radioMenor(rmen) {}

    void setRadioMayor(float rM) { radioMayor = rM; }
    void setRadioMenor(float rmen) { radioMenor = rmen; }

    float getRadioMayor() const { return radioMayor; }
    float getRadioMenor() const { return radioMenor; }

};

class Rectangulo {
private:
    float base, altura;
    Punto vertice_bajo_izq;

public:
    Rectangulo(float b, float a, Punto v) : base(b), altura(a), vertice_bajo_izq(v) {}

    void setBase(float b) { base = b; }
    void setAltura(float a) { altura = a; }
    void setVertice(const Punto& v) { vertice_bajo_izq = v; }

    float getBase() const { return base; }
    float getAltura() const { return altura; }
    Punto getVertice() const { return vertice_bajo_izq; }
};

// Template para procesar figuras geométricas

template <typename T>
class ProcesadorFiguras {

public:

    static float calcularArea(const T& figura) {
        static_assert(sizeof(T) == -1, "Figura desconocida");
        return 0.0f;
    }

};

// Especialización para Circulo

template <>

class ProcesadorFiguras<Circulo> {

public:

    static float calcularArea(const Circulo& c) {
        return 3.14159f * c.getRadio() * c.getRadio();
    }
};

// Especialización para Elipse
template <>

class ProcesadorFiguras<Elipse> {

public:

    static float calcularArea(const Elipse& e) {
        return 3.14159f * e.getRadioMayor() * e.getRadioMenor();
    }
};

// Especialización para Rectangulo
template <>

class ProcesadorFiguras<Rectangulo> {

public:

    static float calcularArea(const Rectangulo& r) {
        return r.getBase() * r.getAltura();
    }
};

int main() {
    
    Circulo c(5.0f);
    Elipse e(4.0f, 2.0f);
    Rectangulo r(3.0f, 6.0f, Punto(0.0f, 0.0f));

    cout << "Área del Círculo: " << ProcesadorFiguras<Circulo>::calcularArea(c) << endl;
    cout << "Área de la Elipse: " << ProcesadorFiguras<Elipse>::calcularArea(e) << endl;
    cout << "Área del Rectángulo: " << ProcesadorFiguras<Rectangulo>::calcularArea(r) << endl;

    return 0;
}
