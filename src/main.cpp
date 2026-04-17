#include "raylib.h"
#include "Body.hpp"
#include <vector>

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Simulador de Mecanica Orbital");

    Camera3D camera = { 0 };
    camera.position = { 20.0f, 20.0f, 20.0f }; 
    camera.target = { 0.0f, 0.0f, 0.0f };      
    camera.up = { 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;

    double scale = 1e-6; 

    Phys::Body earth("Tierra", 5.972e24, Phys::Vector3(0, 0, 0), Phys::Vector3(0, 0, 0));
    Phys::Body sat("Sputnik", 1000.0, Phys::Vector3(8000000, 0, 0), Phys::Vector3(0, 7500, 0));

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        double dt = 100.0; 
        
        Phys::Vector3 force = sat.calculateGravitationalForce(earth);
        sat.applyForce(force);
        sat.update(dt);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                
                DrawSphere({0, 0, 0}, 2.0f, BLUE); 
                DrawSphereWires({0, 0, 0}, 2.1f, 16, 16, DARKBLUE);

                Vector3 satPos = Vector3{ 
                    static_cast<float>(sat.position.x * scale), 
                    static_cast<float>(sat.position.y * scale), 
                    static_cast<float>(sat.position.z * scale) 
                };
                
                DrawSphere(satPos, 0.3f, RED);
                DrawGrid(20, 1.0f);

            EndMode3D();

            DrawText("Simulacion Orbital v0.1", 10, 10, 20, RAYWHITE);
            DrawFPS(10, 40);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}