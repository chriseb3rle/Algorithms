#include <iostream>
#include <vector>
#include <memory>
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

class Quadtree{
public:
    Quadtree(double* boundary, int capacity) : depth(15) {
        //initialize class variables
        isDivided = false;
        if (capacity < 1) {
            std::cout << "Invalid capacity, defaulting to 1: " << std::endl;
            capacity = 1;
        }
        this->capacity = capacity;
        //initialize class boundary array
        this->boundary[0] = boundary[0];
        this->boundary[1] = boundary[1];
        this->boundary[2] = boundary[2];
        this->boundary[3] = boundary[3];
        //Initialize children to null
        children[0] = nullptr;
        children[1] = nullptr;
        children[2] = nullptr;
        children[3] = nullptr;
    }
    bool insert(Obj& particle) {
        //If point is not within bounds than do not insert
        if(!contains(particle)) {
            return false;
        }
        //If capacity is not reached then add particle to points vector
        if (points.size() <= capacity) {
            points.push_back(&particle);
            return true;
        }
        //If max depth is reached than end the insertion
        if (depth == 0) {
            points.push_back(&particle);
            return false;
        }
        //If capacity is reached than subdivide
        if (!isDivided) {
            subdivide();
            //Insert points into all children
            for (auto& point : points){
                for (int i = 0; i < 4;i++){
                    if (children[i]->insert(*point)) {
                        break;
                    }
                }
            }
        }
        //Insert the particle into all four children
        for(int i = 0; i < 4;i++){
            if (children[i]->insert(particle)) {
                return true;
            }
        }
        return false;
    }
    void update(std::vector<Obj>& particle) {
        isDivided = false;
        points.clear();
        for (int i = 0; i < particle.size();i++){
            insert(particle[i]);
        }
        //TraverseTree
    }
private:
//Private member variables
bool isDivided;
double boundary[4];
int capacity;
int depth;
std::vector<Obj*> points;
std::unique_ptr<Quadtree> children[4];
//Private member functions
void subdivide() {
    //Calculate the midpoint of the current node
    double xMid = (boundary[0] + boundary[2]) / 2;
    double yMid = (boundary[1] + boundary[3]) / 2;
    //Create the new boundaries for the subquadrants
    double nw[] = { boundary[0], boundary[1],xMid,yMid };
    double ne[] = { xMid, boundary[1],boundary[2],yMid };
    double sw[] = { boundary[0], yMid,xMid,boundary[3] };
    double se[] = { xMid, yMid,boundary[2],boundary[3] };
    //Create instances of the new quadtrees for all four children
    children[0] = std::make_unique<Quadtree>(nw, this->capacity);
    children[1] = std::make_unique<Quadtree>(ne, this->capacity);
    children[2] = std::make_unique<Quadtree>(sw, this->capacity);
    children[3] = std::make_unique<Quadtree>(se, this->capacity);
    //Set the depth of the children quadtrees
    for (int i = 0; i < 4;i++) {
        children[i]->depth = this->depth - 1;
    }
    //Subdivision has occured, so isDivided is set to true
    isDivided = true;
}
bool contains(Obj& particle) {
    double px = particle.currentPos[0];
    double py = particle.currentPos[1];
    if (px > boundary[0] && px < boundary[2] && py > boundary[1] && py < boundary[3]) {
        return true;
    }
    else {
        return false;
    }
}
};

int main(){
    //Initialization
    double bound[4] = {0,0,500,500};
    Quadtree tree(bound,2);
    bool run = true;
    while(run){
        //Program loop
    }
    //cleanup/exit
    return 0;
}