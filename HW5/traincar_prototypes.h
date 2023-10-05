// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

void PushBack(TrainCar *&oldTrain, TrainCar *newTrain);

void PushFront(TrainCar *&oldTrain, TrainCar *newTrain);

TrainCar *eraseCar(TrainCar *&oldTrain, TrainCar *pnt);

void DeleteAllCars(TrainCar *&theTrain);

std::vector<TrainCar *> ShipFreight(TrainCar *&all_engines, TrainCar *&all_freight, int speed, int max_cars);

bool freightCanPush(TrainCar *theTrain, int newWeight, float minSpd);

int ClosestEngineToSleeperCar(TrainCar* theTrain);

void TotalWeightAndCountCars(TrainCar *trainCar, int &totalWeight, int &numEngine, int &numFreight, int &numPass,
                             int &numDin, int &numSleep);

float calculateSpeedAfter(TrainCar *theTrain, int newWeight);

float CalculateSpeed(TrainCar *theTrain);

float AverageDistanceToDiningCar(TrainCar *theTrain);

void Separate(TrainCar *&train1, TrainCar *&train2, TrainCar *&train3);

void eraseEngineFromT1toT2(TrainCar* &newTrainOne, TrainCar* &newTrainTwo);

void eraseEngineFromT2toT1(TrainCar* &newTrainOne, TrainCar* &newTrainTwo);

void eraseOtherFromT1toT2(TrainCar* &newTrainOne, TrainCar* &newTrainTwo);

void eraseOtherFromT2toT1(TrainCar* &newTrainOne, TrainCar* &newTrainTwo);