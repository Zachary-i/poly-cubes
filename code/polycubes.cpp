#include <iostream>

struct Cube {
  int x;
  int y;
  int z;
};

struct Shape {
  int numCubes;
  Cube* shapeCubesPtr;

  void tryToAddCube(){
    
  }
  
};

int calculateTotalShapes(int n, Cube* shapesPtr, int mapLength){
  return 5;

}

void printShapes(Cube* shapesPtr){
  std::cout << "[0,0,0]";
}

int main(){
  std::cout << "Enter the number of cubes you would" <<
    " like to make shapes from: \n";
  int n;
  std::cin >> n;

  Cube* shapesPtr = new Cube[n*n];
  std::cout << "Total number of shapes: " <<
    calculateTotalShapes(n, shapesPtr, n*n) <<
    "\nWould you like to print the shapes? (y/n) ";
  char printChoice;
  std::cin >> printChoice;
  if(printChoice=='y'){printShapes(shapesPtr);};
  
  return 0;
}
