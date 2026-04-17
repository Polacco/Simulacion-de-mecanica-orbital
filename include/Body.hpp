#ifndef BODY_HPP
#define BODY_HPP

#include "Vector3.hpp"
#include <string>

class Body {
public:
    std::string name;
    double mass;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    Body(std::string _name, double _mass, Vector3 _pos, Vector3 _vel)
        : name(_name), mass(_mass), position(_pos), velocity(_vel), acceleration(0, 0, 0) {}

    // calcular la fuerza gravitatoria que OTRO cuerpo ejerce sobre este cuerpo
    Vector3 calculateGravitationalForce(const Body& other) const {
        const double G = 6.67430e-11; // constante de gravitacion universal
        
        Vector3 r_vector = other.position - this->position; // vector que va desde nosotros hacia el otro cuerpo
        double distance = r_vector.magnitude();

        if (distance < 1.0) return Vector3(0, 0, 0); 

        // formula matematica: F = G * (m1 * m2) / r^2 - fuerza, constante gravitacional, masas y distancia entre cuerpos
        double forceMagnitude = G * (this->mass * other.mass) / (distance * distance);
        // uso double porque en la realidad las distancias son grandes y las fuerzas dependen, pueden ser grandes o pequeñas

        return r_vector.normalized() * forceMagnitude;
    }
};

#endif