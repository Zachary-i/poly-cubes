#include <iostream>

struct Cube {
  int x;
  int y;
  int z;
  Cube(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z){
  }
};

struct Shape {
  int numCubes;
  Cube* shapeCubesPtr;
  int totalDistance;
  Shape(int nCubes = 1, Cube* cubesPtr = new Cube(),
	int distance = 0):numCubes(nCubes),
			       shapeCubesPtr(cubesPtr),
			       totalDistance(distance){
    if(totalDistance == 0){
      totalDistance = calculateTotalDistance();
    }
  }

private:
  int calculateTotalDistance(){
    int result = 0;
    for (int i=0; i < numCubes; i++){
      result += ((shapeCubesPtr+i)->x * (shapeCubesPtr+i)->x +
		 (shapeCubesPtr+i)->y * (shapeCubesPtr+i)->y +
		 (shapeCubesPtr+i)->z * (shapeCubesPtr+i)->z);
    }
    return result;
  }
};

int calculateShapes(int n, Shape*& shapesPtr){

  if(n <= 1){
    shapesPtr = new Shape();
    return 1;
  } else {
    
    int mapLength = n*n;
    shapesPtr = new Shape[mapLength];
    Shape* previousShapesPtr = nullptr;
    int previousLength = (n-1) * (n-1);
    int totalNumShapes = 0;

    calculateShapes(n-1, previousShapesPtr);
    
    for(int i = 0; i < previousLength; i++){

      Shape* currentShapePtr = (previousShapesPtr + i); 
      Cube* endCubePtr = (currentShapePtr->shapeCubesPtr +
			  (currentShapePtr->numCubes - 1));

      int endX = endCubePtr->x;
      int endY = endCubePtr->y;
      int endZ = endCubePtr->z;

      char testAdditions = 0;
      // 1 = +x; 2 = -x; 4 = +y; 8 = -y; 16 = +z; 32 = -z;
      
      for(int j = 0; j < currentShapePtr->numCubes; j++){
	Cube* currentCubePtr = currentShapePtr->shapeCubesPtr+j;
	int x = currentCubePtr->x;
	int y = currentCubePtr->y;
	int z = currentCubePtr->z;
	
	if (endX+1 == x && endY == y && endZ == z){
	  testAdditions |= 1;
	}

	if (endX-1 == x && endY == y && endZ == z){
	  testAdditions |= 2;
	}

	if (endX == x && endY+1 == y && endZ == z){
	  testAdditions |= 4;
	}

	if (endX == x && endY-1 == y && endZ == z){
	  testAdditions |= 8;
	}

	if (endX == x && endY == y && endZ+1 == z){
	  testAdditions |= 16;
	}

	if (endX == x && endY == y && endZ-1 == z){
	  testAdditions |= 32;
	}
      }

      if(testAdditions & 1 == 1){

      }
      
    }
    delete[] previousShapesPtr;
    return totalNumShapes;
  }
}

void tryToAddCube(Cube* cubePtr, Shape* baseShapePtr, Shape* shapesPtr){

}

void printShapes(int n, Shape* shapesPtr){
  for(int i = 0; i < (n*n); i++){
    for(int j = 0; j < (shapesPtr+i)->numCubes; j++){
      std::cout << "[" << ((shapesPtr+i)->shapeCubesPtr + j)->x
		<< ", " << ((shapesPtr+i)->shapeCubesPtr + j)->y
		<< ", " << ((shapesPtr+i)->shapeCubesPtr + j)->z
		<< "], ";
    }
    std::cout << "\n";
  }
}

int main(){
  std::cout << "Enter the number of cubes you would" <<
    " like to make shapes from: \n";
  int n;
  std::cin >> n;

  Shape* shapesPtr = nullptr;
  std::cout << "Total number of shapes: " <<
    calculateShapes(n, shapesPtr) <<
    "\nWould you like to print the shapes? (y/n) ";
  
  char printChoice;
  std::cin >> printChoice;

  if(printChoice=='y'){printShapes(n, shapesPtr);};
  
  return 0;
}
