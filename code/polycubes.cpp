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
  int averageDeviation;
  Shape* nextShapePtr;
  
  Shape(int nCubes = 1, Cube* cubesPtr = new Cube[1],
	Shape* nShapePtr = nullptr):numCubes(nCubes),
				    shapeCubesPtr(cubesPtr),
				    nextShapePtr(nShapePtr){
    calculateTotalCoords();
    calculateAverageDeviation();
  }

  ~Shape (){
    delete[] shapeCubesPtr;
    delete nextShapePtr;
  }

  Shape* operator+(Cube* addedCube){
    Cube* cubesPtr = new Cube[numCubes+1];
    for(int i = 0; i < numCubes; i++){
      (cubesPtr+i)->x = (shapeCubesPtr+i)->x;
      (cubesPtr+i)->y = (shapeCubesPtr+i)->y;
      (cubesPtr+i)->z = (shapeCubesPtr+i)->z;
    }
    (cubesPtr+numCubes)->x = addedCube->x;
    (cubesPtr+numCubes)->y = addedCube->y;
    (cubesPtr+numCubes)->z = addedCube->z;
    return new Shape(numCubes+1, cubesPtr, nullptr);
  }

private:

  int totalX = 0;
  int totalY = 0;
  int totalZ = 0;

  void calculateTotalCoords(){
    for(int i = 0; i < numCubes; i++){
      totalX += (shapeCubesPtr+i)->x;
      totalY += (shapeCubesPtr+i)->y;
      totalZ += (shapeCubesPtr+i)->z;
    }
  }

  void calculateAverageDeviation(){
    int averageX = totalX / numCubes;
    int averageY = totalY / numCubes;
    int averageZ = totalZ / numCubes;
    int totalDeviantDistSq = 0;
    
    for(int i = 0; i< numCubes; i++){
      totalDeviantDistSq += ((averageX - (shapeCubesPtr+i)->x) *
			     (averageX - (shapeCubesPtr+i)->x) +
			     (averageY - (shapeCubesPtr+i)->y) *
			     (averageY - (shapeCubesPtr+i)->y) +
			     (averageZ - (shapeCubesPtr+i)->z) *
			     (averageZ - (shapeCubesPtr+i)->z));
    }

    averageDeviation = totalDeviantDistSq * totalDeviantDistSq / numCubes;
  }
  
};

bool tryToAddCube(Cube* cubePtr, Shape* baseShapePtr, int n, Shape* shapesPtr){
  Shape* potentialShapePtr = *baseShapePtr + cubePtr;
  int index = (potentialShapePtr->averageDeviation % (n*n));
  
  if((shapesPtr + index)->numCubes != n){
    *(shapesPtr + index) = *potentialShapePtr;
    return true;
  } else if(true){
    Shape* endShapePtr = (shapesPtr + index);

    while(endShapePtr->nextShapePtr){
      endShapePtr = endShapePtr->nextShapePtr;
    }
    
    endShapePtr->nextShapePtr = potentialShapePtr;
    return true;
  }
  delete potentialShapePtr;
  return false;
}

void buildShapeArray(Shape* currentShapePtr, int n, int& totalNumShapes, Shape* shapesPtr){
  while(currentShapePtr){
    if(currentShapePtr->numCubes == (n-1)){
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
    
      if((testAdditions & 1) != 1){
	totalNumShapes += tryToAddCube(new Cube(endX+1, endY, endZ),
				       currentShapePtr, n, shapesPtr);
      }
    
      if((testAdditions & 2) != 2){
	totalNumShapes += tryToAddCube(new Cube(endX-1, endY, endZ),
				       currentShapePtr, n, shapesPtr);
      }
    
      if((testAdditions & 4) != 4){
	totalNumShapes += tryToAddCube(new Cube(endX, endY+1, endZ),
				       currentShapePtr, n, shapesPtr);
      }
    
      if((testAdditions & 8) != 8){
	totalNumShapes += tryToAddCube(new Cube(endX, endY-1, endZ),
				       currentShapePtr, n, shapesPtr);
      }
    
      if((testAdditions & 16) != 16){
	totalNumShapes += tryToAddCube(new Cube(endX, endY, endZ+1),
				       currentShapePtr, n, shapesPtr);
      }
    
      if((testAdditions & 32) != 32){
	totalNumShapes += tryToAddCube(new Cube(endX, endY, endZ-1),
				       currentShapePtr, n, shapesPtr);
      }
    }
  
    currentShapePtr= currentShapePtr->nextShapePtr;

  }
}

int calculateShapes(int n, Shape*& shapesPtr){

  delete[] shapesPtr;
  shapesPtr = (n <= 1) ? new Shape[1] : nullptr;
  Shape* previousShapesPtr = (n <= 1) ? nullptr : new Shape[1];
  int totalNumShapes = 1;

  for(int i = 1; i < n; i++){
    int previousLength = i * i;
    int mapLength = (i + 1) * (i + 1);
    shapesPtr = new Shape[mapLength];
    totalNumShapes = 0;

    for(int j = 0; j < previousLength; j++){
      buildShapeArray(previousShapesPtr + j, i+1, totalNumShapes, shapesPtr);
    }
    
    delete[] previousShapesPtr;
    previousShapesPtr = shapesPtr;
  }

  return totalNumShapes;
}

void printShape(Shape* shapePtr){
  for(int j = 0; j < shapePtr->numCubes; j++){
    std::cout << "[" << (shapePtr->shapeCubesPtr + j)->x
	      << ", " << (shapePtr->shapeCubesPtr + j)->y
	      << ", " << (shapePtr->shapeCubesPtr + j)->z
	      << "], ";
  }
  std::cout << "\n";
  if(shapePtr->nextShapePtr){
    printShape(shapePtr->nextShapePtr);
  }
}

void printShapes(int n, Shape* shapesPtr){
  for(int i = 0; i < (n*n); i++){
    if((shapesPtr+i)->numCubes == n){
      printShape(shapesPtr+i);
    }
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
