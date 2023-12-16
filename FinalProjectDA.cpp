// FinalProjectDA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

//Set grid cells, width and height
const int sizegridCell = 10;
const int gridWidth = 90;
const int gridHeight = 90;

//Load the grid
void gridLoad(int grid[gridWidth][gridHeight]) {
    for (int i = 0; i < gridWidth; i++) { //Load cells. Cells random
        for (int j = 0; j < gridHeight; j++) {
            int cellvalueRandom = (1 & rand());
            if (cellvalueRandom == 0) {
                grid[i][j] = 0;
            }
            else {
                grid[i][j] = 1;
            }
        }
    }
}


//Number of alive & dead cells. Takes into account cells that are next to each other
int numCellLive(int grid[gridWidth][gridHeight], int x, int y) {
    int num = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int cellnextX = x + i; //Cell X
            int cellnextY = y + j; //Cell Y
            if (cellnextX >= 0 && cellnextX < gridWidth && cellnextY >= 0 && cellnextY < gridHeight && !(i == 0 && j == 0)) {
                num = num + grid[cellnextX][cellnextY];
            }
        }
    }
    return num;
}

int cellNextAlive(0);

//New grid with added parameters
void gridRefresh(int grid[gridWidth][gridHeight]) {
    int gridNew[gridWidth][gridHeight] = { 0 };

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            int cellnextAlive = numCellLive(grid, i, j);
            if (grid[i][j]) {
                if (cellnextAlive == 2 || cellnextAlive == 3) {
                    gridNew[i][j] = 1;
                }
                else {
                    gridNew[i][j] = 0;
                }
            }
            else {
                if (cellnextAlive == 3) {
                    gridNew[i][j] = 1;
                }
                else {
                    gridNew[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            grid[i][j] = gridNew[i][j];
        }
    }
}

//Display grid
void gridDisplay(RenderWindow& window, int grid[gridWidth][gridHeight]) {
    RectangleShape pixelStart(Vector2f(sizegridCell, sizegridCell));
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            pixelStart.setPosition(i * sizegridCell, j * sizegridCell);
            if (grid[i][j]) {
                pixelStart.setFillColor(Color::Red); // Color of the cells that are alive
            }
            else {
                pixelStart.setFillColor(Color::Blue); // Color of the cells that are dead
            }
            window.draw(pixelStart);
        }
    }
}


//Display window
int main() {
    RenderWindow window(VideoMode(gridWidth * sizegridCell, gridHeight * sizegridCell), "Conway's Game of Life: ReImagined");

    int grid[gridHeight][gridHeight] = { 0 }; // Grid will load evolution

    gridLoad(grid);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();

            }
        }


        window.clear();
        gridRefresh(grid);
        gridDisplay(window, grid);
        window.display();
    }


}
