#include <iostream>
#include "raylib.h"
#include <vector>
#include <string>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // Terrain Generation
    std::vector<std::vector<int>> terrain;
    std::vector<int> terrainRow;
    int prevTile = 1;
    srand(std::__cxx11::stoi(argv[3]));
    for (int x=0;x<std::__cxx11::stoi(argv[1]);x++){
	for (int y=0;y<std::__cxx11::stoi(argv[2]);y++) {
		int randTile = rand() % 4;
		if (randTile == 0) {
		    terrainRow.push_back(0);
		    prevTile = 0;
		} else if (randTile == 1){
		    terrainRow.push_back(1);
		    prevTile = 1;
		} else if (randTile == 2){
		    terrainRow.push_back(prevTile);
		} else if (randTile == 3){
		    if (x==0) {
			terrainRow.push_back(1);
			prevTile = 1;	
	 	    } else {
			terrainRow.push_back(terrain[x-1][y]);
			prevTile = terrain[x-1][y];
		    }
		}
	    }
      	    std::cout << "\n";
	    terrain.push_back(terrainRow);
	    terrainRow.clear();
    }
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "PixVille");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------	
    Texture2D groundTiles = LoadTexture("res/ground-tiles.png");
    Rectangle groundTile = {0,0,14,7};
    Camera2D camera = { 0 };
    camera.zoom = 5;
    float posXmulti = 6;
    float posYmulti = 3;


    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
	    BeginMode2D(camera);
                for (int x=0;x<terrain.size();x++){
			for (int y=0;y<terrain[x].size();y++){
				groundTile = {terrain[x][y]*14,0,14,7};
				float posX = x+y; // y, x increases xpos
				float posY = terrain[x].size()-y+x; // x, terrain[x].size() increases ypos. y decreases ypos
				DrawTextureRec(groundTiles, groundTile, Vector2({posX*posXmulti,(posY*posYmulti)-3}), WHITE);
			}
		}
	    EndMode2D();
	    if (IsKeyDown(KEY_D)) {
                DrawText(std::to_string(posXmulti).c_str(), 20, 50, 20, BLACK);
                DrawText(std::to_string(posYmulti).c_str(), 20, 90, 20, BLACK);
		DrawText(std::to_string(atoi(argv[3])).c_str(), 20, 130, 20, BLACK);
	    }
	    
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(groundTiles);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
