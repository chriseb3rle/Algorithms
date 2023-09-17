#include <iostream>
#include <vector>
#include <cmath>

class Obj {
public:
//Constructor
Obj(double xp,double yp){
    currentPos[0] = xp;
    currentPos[1] = yp;
}
double currentPos[2];
private:
};

class GridPartition {
public:
    GridPartition(double* boundary, int gridSize) {
        this->boundary[0] = boundary[0];
        this->boundary[1] = boundary[1];
        this->boundary[2] = boundary[2];
        this->boundary[3] = boundary[3];
        this->size = gridSize;
        //Calculate the width and height of each grid cell
        cellWidth = (boundary[2] - boundary[0]) / size;
        cellHeight = (boundary[3] - boundary[1]) / size;
        //Compute inverse cell width and height to avoid redundant calculations
        invCellWidth = 1.0 / cellWidth;
        invCellHeight = 1.0 / cellHeight;
        //Initialize the grid cells as a 1D vector
        grids.resize(size*size);
    }

    bool insert(Obj& obj){}
    void collision(){}
    void resolveCollisionsInCell(std::vector<Obj*>& cell) {}
    void resolveNeighbourCollisions(int row, int col) {}
    void resolveCollisionsBetweenCells(std::vector<Obj*>& cellA, std::vector<Obj*>& cellB) {}
    void remove() {}
    void update(std::vector<Obj>& objects) {}
private:
    double boundary[4];
    int size;
    double cellWidth;
    double cellHeight;
    double invCellWidth;
    double invCellHeight;
    //1D vector to represent grid cells
    std::vector<std::vector<Obj*>> grids;
    //hash table
    std::unordered_map<int, std::vector<Obj*>> spatialHash;
};

int main(){
    double boundary[4] = {0,0,500,500};
    GridPartition grid(boundary, 100);
    return 0;
}