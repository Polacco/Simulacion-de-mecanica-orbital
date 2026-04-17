#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/Body.hpp"

int main() {
    // Datos reales (aprox)
    double earthMass = 5.972e24;
    double satelliteMass = 1000.0; // 1 tonelada
    
    // Posición: 7000km desde el centro de la Tierra (órbita baja)
    // Velocidad: ~7500 m/s es la velocidad orbital necesaria
    Body earth("Tierra", earthMass, Vector3(0, 0, 0), Vector3(0, 0, 0));
    Body sat("Sputnik", satelliteMass, Vector3(7000000, 0, 0), Vector3(0, 7500, 0));

    double dt = 10.0; // Saltos de 10 segundos
    int totalSteps = 1000;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Simulando órbita..." << std::endl;

    for (int i = 0; i < totalSteps; ++i) {
        // 1. Calcular fuerza que la Tierra ejerce sobre el satélite
        Vector3 forceOnSat = sat.calculateGravitationalForce(earth);
        
        // 2. Aplicar y actualizar
        sat.applyForce(forceOnSat);
        sat.update(dt);

        // Imprimir cada 100 pasos para no saturar la consola
        if (i % 100 == 0) {
            std::cout << "Paso " << i << " - Posicion Sat: (" 
                      << sat.position.x << ", " << sat.position.y << ")" << std::endl;
        }
    }

    return 0;
}