#include "raylib.h"
#include "Body.hpp"
#include <vector>

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Simulador de Mecanica Orbital - Raylib");

    // configuracion de camara
    Camera3D camera = { 0 };
    camera.position = { 0.0f, 25.0f, 50.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    double scale = 1e-6; 
    double dt = 100.0; // cada frame simula 100 segundos de tiempo real

    // tierra y satelite
    Phys::Body earth("Tierra", 5.972e24, Phys::Vector3(0, 0, 0), Phys::Vector3(0, 0, 0));
    Phys::Body sat("Sputnik", 1000.0, Phys::Vector3(8000000, 0, 0), Phys::Vector3(0, 0, 7500));

    std::vector<Vector3> trail;
    const int maxTrailPoints = 1000; 

    SetTargetFPS(60);
    DisableCursor(); // cursor oculto asi no molesta

    // BUCLE PRINCIPAL
    while (!WindowShouldClose()) {
        
	//rotar camara
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // "r" para resetear camara
        if (IsKeyPressed(KEY_R)) {
            camera.position = { 0.0f, 25.0f, 50.0f };
            camera.target = { 0.0f, 0.0f, 0.0f };
        }


        // fisica
        Phys::Vector3 force = sat.calculateGravitationalForce(earth);
        sat.applyForce(force);
        sat.update(dt);
	
	// logica de la estela de rastro
        Vector3 currentSatPos = { 
            static_cast<float>(sat.position.x * scale), 
            static_cast<float>(sat.position.y * scale), 
            static_cast<float>(sat.position.z * scale) 
        };

        trail.push_back(currentSatPos);
        
        if (trail.size() > maxTrailPoints) {
            trail.erase(trail.begin());
        }


        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);
                
                DrawSphere({0, 0, 0}, 2.0f, BLUE);  // tierra
                DrawSphereWires({0, 0, 0}, 2.1f, 16, 16, DARKBLUE);

                if (trail.size() >= 2) {
                    for (size_t i = 0; i < trail.size() - 1; i++) {
                        DrawLine3D(trail[i], trail[i + 1], RED);
                    }
                }

                DrawSphere(currentSatPos, 0.3f, WHITE); // satelite
                
                DrawGrid(20, 5.0f);

            EndMode3D();

            DrawRectangle(10, 10, 350, 130, Fade(SKYBLUE, 0.3f));
            DrawText("CONTROLES:", 20, 20, 15, YELLOW);
            DrawText("- Mover Mouse: Rotar camara", 20, 40, 12, RAYWHITE);
            DrawText("- Rueda Mouse: Zoom In/Out", 20, 55, 12, RAYWHITE);
            DrawText("- Tecla [R]: Resetear Camara", 20, 70, 12, RAYWHITE);
            
            DrawText(TextFormat("Velocidad: %.2f km/h", (sat.velocity.magnitude() * 3.6)), 20, 100, 18, GREEN);
            
            DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}