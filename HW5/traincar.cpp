// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

/// push_back a new car to the train
/// \param oldTrain the original train
/// \param newTrain the new car
void PushBack(TrainCar *&oldTrain, TrainCar *newTrain) {
    if (oldTrain == NULL) {
        oldTrain = newTrain;
        return;
    }
    TrainCar *curCar = oldTrain;
    while (curCar->next != NULL) {
        curCar = curCar->next;
    }
    curCar->next = newTrain;
    newTrain->prev = curCar;
    newTrain->next = NULL;
}

/// push_front a new car to the train
/// \param oldTrain the original train
/// \param newTrain the new car
void PushFront(TrainCar *&oldTrain, TrainCar *newTrain) {
    if (oldTrain == NULL) {
        oldTrain = newTrain;
        return;
    }
    oldTrain->prev = newTrain;
    newTrain->next = oldTrain;
    newTrain->prev = NULL;
    oldTrain = newTrain;
}

/// erase a car from the train
/// \param oldTrain the target train
/// \param pnt a pointer points to the element will be erased
/// \return the erased element
TrainCar *eraseCar(TrainCar *&oldTrain, TrainCar *pnt) {
    if (oldTrain == NULL) {
        return NULL;
    }
    // remove the only element in the train
    if (oldTrain->next == NULL) {
        TrainCar *tempTrain = oldTrain;
        oldTrain = NULL;
        return tempTrain;
    }
    // remove the first element in the train
    if (pnt->prev == NULL) {
        TrainCar *tempTrain = oldTrain;
        oldTrain = oldTrain->next;
        tempTrain->next = NULL;
        oldTrain->prev = NULL;
        return tempTrain;
    }
    // remove the last element in the train
    if (pnt->next == NULL) {
        TrainCar *tempTrain = pnt;
        (pnt->prev)->next = NULL;
        tempTrain->prev = NULL;
        return tempTrain;
    }

    // general case
    (pnt->prev)->next = pnt->next;
    (pnt->next)->prev = pnt->prev;
    pnt->next = NULL;
    pnt->prev = NULL;
    return pnt;
}

/// delete all the cars in the train
/// \param theTrain the train need to be deleted
void DeleteAllCars(TrainCar *&theTrain) {
    if (theTrain == NULL) {
        return;
    }
    if (theTrain->next == NULL) {
        delete theTrain;
        return;
    }
    TrainCar *curTrain = theTrain;
    while (curTrain != NULL) {
        TrainCar *temp = curTrain;
        curTrain = curTrain->next;
        delete temp;
    }
}

/// allocate the train given a bunch of engines and freight
/// \param all_engine the list of engine
/// \param all_freight the list of freight
/// \param speed the speed requirement of the newly allocated trains
/// \param max_cars the max number of cars in the newly allocated trains
/// \return vectors containing all the newly allocated trains
std::vector<TrainCar *> ShipFreight(TrainCar *&all_engine, TrainCar *&all_freight, int speed, int max_cars) {
    std::vector<TrainCar *> outputTrains;
    int trainNum = 0;
    while (all_engine != NULL && all_freight != NULL) {
        outputTrains.push_back(NULL);
        TrainCar *tempEngine = all_engine;
        all_engine = all_engine->next;
        if (all_engine != NULL) {
            all_engine->prev = NULL;
        }
        tempEngine->next = NULL;
        tempEngine->prev = NULL;
        // every train will start by an engine
        PushBack(outputTrains[trainNum], tempEngine);
        int curTrainCar = 1;
        while (curTrainCar < max_cars) {
            if (all_freight == NULL || all_engine == NULL) {
                break;
            }
            curTrainCar++;
            // check if the current train can push more freight
            bool canPush = freightCanPush(outputTrains[trainNum], all_freight->getWeight(), speed);
            if (canPush) {
                // push a freight car
                TrainCar *tempFrei = all_freight;
                all_freight = all_freight->next;
                if (all_freight != NULL) {
                    all_freight->prev = NULL;
                }
                tempFrei->next = NULL;
                tempFrei->prev = NULL;
                PushBack(outputTrains[trainNum], tempFrei);
            } else {
                // push an engine car
                TrainCar *tempEngine = all_engine;
                all_engine = all_engine->next;
                if (all_engine != NULL) {
                    all_engine->prev = NULL;
                }
                tempEngine->next = NULL;
                tempEngine->prev = NULL;
                PushBack(outputTrains[trainNum], tempEngine);
            }
        }
        trainNum++;
    }
    return outputTrains;
}

/// check if there are more freights can be pushed to the current train
/// \param theTrain the train to check
/// \param newWeight the weight the freight will be added
/// \param minSpd the min speed requirement of the train
/// \return
bool freightCanPush(TrainCar *theTrain, int newWeight, float minSpd) {
    float newSpd = calculateSpeedAfter(theTrain, newWeight);
    if (newSpd > minSpd) {
        return true;
    } else {
        return false;
    }
}

/// calculate the speed of the train
/// \param theTrain the train
/// \return the speed of the train as float, to prevent overflow.
float CalculateSpeed(TrainCar *theTrain) {
    int total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars;
    TotalWeightAndCountCars(theTrain, total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars,
                            num_sleeping_cars);
    float hp = (num_engines) * 3000;
    float spd = hp * 550 * 3600;
    spd /= (20 * 2 * 5280 * total_weight);
    return spd;
}

/// calculate the speed of the train after the new freight is added
/// \param theTrain the train
/// \param newWeight the weight of the freight
/// \return speed of the train if added
float calculateSpeedAfter(TrainCar *theTrain, int newWeight) {
    int total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars;
    TotalWeightAndCountCars(theTrain, total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars,
                            num_sleeping_cars);
    float hp = (num_engines) * 3000;
    float spd = hp * 550 * 3600;
    spd /= (20 * 2 * 5280 * (total_weight + newWeight));
    return spd;
}

/// count the weight & each type of cars in the train
/// \param trainCar the train
/// \param totalWeight the total weight
/// \param numEngine the number of engine
/// \param numFreight the number of freight cars
/// \param numPass the number of passengers cars
/// \param numDin the number of dining cars
/// \param numSleep the number of sleep cars
void TotalWeightAndCountCars(TrainCar *trainCar, int &totalWeight, int &numEngine, int &numFreight, int &numPass,
                             int &numDin, int &numSleep) {
    totalWeight = 0;
    numEngine = 0;
    numFreight = 0;
    numPass = 0;
    numDin = 0;
    numSleep = 0;
    while (trainCar != NULL) {
        totalWeight += trainCar->getWeight();
        if (trainCar->isEngine()) {
            numEngine++;
        } else if (trainCar->isFreightCar()) {
            numFreight++;
        } else if (trainCar->isPassengerCar()) {
            numPass++;
        } else if (trainCar->isDiningCar()) {
            numDin++;
        } else if (trainCar->isSleepingCar()) {
            numSleep++;
        }
        trainCar = trainCar->next;
    }
}

/// calculate the average distance to the dining car
/// \param theTrain the train
/// \return the average distance as float
float AverageDistanceToDiningCar(TrainCar *theTrain) {
    TrainCar *curTrain = theTrain;
    float numPass = 0;
    float totalDis = 0;

    while (curTrain != NULL) {
        if (curTrain->isPassengerCar()) {
            // check each passenger cars
            numPass++;
            bool haveSearch = false;
            float curDis = 1;
            // search the front of the passenger cars
            TrainCar *frontPtr = curTrain->prev;
            while (frontPtr != NULL && !frontPtr->isFreightCar() && !frontPtr->isEngine()) {
                if (frontPtr->isDiningCar()) {
                    haveSearch = true;
                    break;
                } else {
                    curDis++;
                    frontPtr = frontPtr->prev;
                }
            }
            // search the back of the passenger cars
            if (!haveSearch) {
                curDis = 1;
                TrainCar *backPtr = curTrain->next;
                while (backPtr != NULL && !backPtr->isFreightCar() && !backPtr->isEngine()) {
                    if (backPtr->isDiningCar()) {
                        haveSearch = true;
                        break;
                    } else {
                        curDis++;
                        backPtr = backPtr->next;
                    }
                }
            }
            // if both doesn't find dining, the current passenger car cannot access to any dining car
            if (!haveSearch) {
                return -1;
            } else {
                totalDis += curDis;
            }
            curTrain = curTrain->next;
        } else {
            curTrain = curTrain->next;
        }
    }
    return (totalDis / numPass);
}

/// find the closest engine between the sleeper cars and engine
/// \param theTrain the train
/// \return the distance
int ClosestEngineToSleeperCar(TrainCar *theTrain) {
    TrainCar *curTrain = theTrain;
    int total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars;
    TotalWeightAndCountCars(theTrain, total_weight, num_engines, num_freight_cars, num_passenger_cars,
                            num_dining_cars, num_sleeping_cars);
    int totalCar = num_engines + num_freight_cars + num_passenger_cars + num_dining_cars + num_sleeping_cars;
    // set the min distance to the car number in the train, which is the maximum possible distance
    int minDis = totalCar;
    while (curTrain != NULL) {
        if (curTrain->isSleepingCar()) {
            // check each sleep car
            int curDis = 1;
            // search the front of the sleep cars
            TrainCar *frontPtr = curTrain->prev;
            while (frontPtr != NULL) {
                if (frontPtr->isEngine()) {
                    minDis = std::min(minDis, curDis);
                    break;
                } else {
                    curDis++;
                    frontPtr = frontPtr->prev;
                }
            }
            // search the back of the sleep cars
            curDis = 1;
            TrainCar *backPtr = curTrain->next;
            while (backPtr != NULL) {
                if (backPtr->isEngine()) {
                    minDis = std::min(minDis, curDis);
                    break;
                } else {
                    curDis++;
                    backPtr = backPtr->next;
                }
            }
            curTrain = curTrain->next;
        } else {
            curTrain = curTrain->next;
        }
    }
    return minDis;
}

/// separate the train as given
/// \param oldTrain
/// \param newTrainOne
/// \param newTrainTwo
void Separate(TrainCar *&oldTrain, TrainCar *&newTrainOne, TrainCar *&newTrainTwo) {
    //Initializing train 1 and train 2
    newTrainOne = NULL;
    newTrainTwo = NULL;
    // dividing old train into two new train by its middle car
    int total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars;
    TotalWeightAndCountCars(oldTrain, total_weight, num_engines, num_freight_cars, num_passenger_cars,
                            num_dining_cars, num_sleeping_cars);
    int numCarOld = num_engines + num_freight_cars + num_passenger_cars + num_dining_cars + num_sleeping_cars;
    int numOtherOld = numCarOld - num_engines;
    int midNum = numCarOld / 2;
    int curNum = 0;

    // right-train favour dividing when there are odd number of cars
    while (oldTrain != NULL) {
        if (curNum < midNum) {
            // push to newTrainOne
            TrainCar *tempTrain = oldTrain;
            oldTrain = oldTrain->next;
            if (oldTrain != NULL) {
                oldTrain->prev = NULL;
            }
            tempTrain->prev = NULL;
            tempTrain->next = NULL;
            PushBack(newTrainOne, tempTrain);
        } else {
            TrainCar *tempTrain = oldTrain;
            oldTrain = oldTrain->next;
            if (oldTrain != NULL) {
                oldTrain->prev = NULL;
            }
            tempTrain->prev = NULL;
            tempTrain->next = NULL;
            PushBack(newTrainTwo, tempTrain);
        }
        curNum++;
    }

    // get the car statistic of the left train
    int totalWeightOne, numEngineOne, numFreightOne, numPassOne, numDinOne, numSleepOne;
    TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                            numDinOne, numSleepOne);
    int numOtherOne = numFreightOne + numPassOne + numDinOne + numSleepOne;

    // get the car statistics of the right train
    int totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo, numDinTwo, numSleepTwo;
    TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                            numDinTwo, numSleepTwo);
    int numOtherTwo = numFreightTwo + numPassTwo + numDinTwo + numSleepTwo;

    // When it is perfect after one middle cut
    if (numCarOld % 2 == 0 && numEngineOne == numEngineTwo && numOtherOne == numOtherTwo) {
        return;
    }

    // Consider the case of left-train-favour when car number is odd
    if (numCarOld % 2 == 1 && newTrainTwo ->isEngine()){
        // push the engine from train 2 to train 1
        eraseEngineFromT2toT1(newTrainOne, newTrainTwo);
        TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                                numDinOne, numSleepOne);
        numOtherOne = numFreightOne + numPassOne + numDinOne + numSleepOne;
        TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                                numDinTwo, numSleepTwo);
        numOtherTwo = numFreightTwo + numPassTwo + numDinTwo + numSleepTwo;
        if (numEngineOne == numEngineTwo && (numOtherOne == numOtherTwo + 1 || numOtherOne == numOtherTwo)){
            return;
        }
        if (numEngineOne == numEngineTwo + 1 && (numOtherOne == numOtherTwo + 1 || numOtherOne == numOtherTwo)){
            return;
        }
        // if the left-favour one cut does not work, recover to the right-cut favour
        eraseEngineFromT1toT2(newTrainOne, newTrainTwo);
    }

    // balancing the engine of 2 trains
    if (num_engines % 2 == 0) {
        int engineMove = 0;
        // recalculate number of engines in both train in each loop
        while (numEngineOne != numEngineTwo) {
            engineMove ++;
            if (numEngineOne > numEngineTwo) {
                // erase engine from train 1 from its tail to head, push-front to train 2
                eraseEngineFromT1toT2(newTrainOne, newTrainTwo);
            } else {
                // erase engine from train 2 from its head to tail, push-back to train 1
                eraseEngineFromT2toT1(newTrainOne, newTrainTwo);
            }
            // update the train's statistics for each time
            TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                                    numDinOne, numSleepOne);
            TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                                    numDinTwo, numSleepTwo);
        }
    } else {
        while (numEngineTwo - numEngineOne != 1) {
            if (numEngineOne > numEngineTwo) {
                // erase engine from train 1 from its tail to head, push-front to train 2
                eraseEngineFromT1toT2(newTrainOne, newTrainTwo);
            } else {
                // erase engine from train 2 from its head to tail, push-back to train 1
                eraseEngineFromT2toT1(newTrainOne, newTrainTwo);
            }
            TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                                    numDinOne, numSleepOne);
            TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                                    numDinTwo, numSleepTwo);
        }
    }

    // balancing the other cars in train2
    if (numOtherOld % 2 == 0) {
        while (numOtherOne != numOtherTwo) {
            if (numOtherOne > numOtherTwo) {
                //erase the car from train 1 from its tail to head, push-front to train 2
                eraseOtherFromT1toT2(newTrainOne, newTrainTwo);
            } else {
                //erase the car from train 2 from its head to tail, push-back to train 1
                eraseOtherFromT2toT1(newTrainOne, newTrainTwo);
            }
            TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                                    numDinOne, numSleepOne);
            numOtherOne = numFreightOne + numPassOne + numDinOne + numSleepOne;
            TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                                    numDinTwo, numSleepTwo);
            numOtherTwo = numFreightTwo + numPassTwo + numDinTwo + numSleepTwo;
        }
    } else {
        while (numOtherTwo - numOtherOne != 1) {
            if (numOtherOne > numOtherTwo) {
                //erase car from train 1 from its tail to head, pus-front ot train 2
                eraseOtherFromT1toT2(newTrainOne, newTrainTwo);
            } else {
                //erase the car from train 2 from its head to tail, push-back to train 1
                eraseOtherFromT2toT1(newTrainOne, newTrainTwo);
            }
            TotalWeightAndCountCars(newTrainOne, totalWeightOne, numEngineOne, numFreightOne, numPassOne,
                                    numDinOne, numSleepOne);
            numOtherOne = numFreightOne + numPassOne + numDinOne + numSleepOne;
            TotalWeightAndCountCars(newTrainTwo, totalWeightTwo, numEngineTwo, numFreightTwo, numPassTwo,
                                    numDinTwo, numSleepTwo);
            numOtherTwo = numFreightTwo + numPassTwo + numDinTwo + numSleepTwo;
        }
    }
}

/// erase the closest engine in train 1 related train 2, push_front it to train 2
/// \param newTrainOne train 1 list
/// \param newTrainTwo train 2 list
void eraseEngineFromT1toT2(TrainCar* &newTrainOne, TrainCar *&newTrainTwo) {
    TrainCar *tempTrain = newTrainOne;
    while (tempTrain->next != NULL) {
        tempTrain = tempTrain->next;
    }
    TrainCar *firstTail = tempTrain;
    while (firstTail != NULL) {
        if (firstTail->isEngine()) {
            TrainCar *erasedEngine = eraseCar(newTrainOne, firstTail);
             PushFront(newTrainTwo, erasedEngine);
            break;
        }
        firstTail = firstTail->prev;
    }
}

/// erase the closest engine in train 2 related to train 1, push_back it to train 1
/// \param newTrainOne train 1 list
/// \param newTrainTwo train 2 list
void eraseEngineFromT2toT1(TrainCar* &newTrainOne, TrainCar* &newTrainTwo) {
    TrainCar *tempTrain = newTrainTwo;
    while (tempTrain != NULL) {
        if (tempTrain->isEngine()) {
            TrainCar *erasedEngine = eraseCar(newTrainTwo, tempTrain);
            PushBack(newTrainOne, erasedEngine);
            break;
        }
        tempTrain = tempTrain->next;
    }
}

/// erase the closest not-engine car in train 1 related to train 2, push_front it to train 2
/// \param newTrainOne train 1 list
/// \param newTrainTwo train 2 list
void eraseOtherFromT1toT2(TrainCar* &newTrainOne, TrainCar* &newTrainTwo) {
    TrainCar *tempTrain = newTrainOne;
    while (tempTrain->next != NULL) {
        tempTrain = tempTrain->next;
    }
    TrainCar *firstTail = tempTrain;
    while (firstTail != NULL) {
        if (!firstTail->isEngine()) {
            TrainCar *erasedEngine = eraseCar(newTrainOne, firstTail);
             PushFront(newTrainTwo, erasedEngine);
            break;
        }
        firstTail = firstTail->prev;
    }
}

/// erase the closest non-engine car in train 2 related to train1, push_back it to train 1
/// \param newTrainOne
/// \param newTrainTwo
void eraseOtherFromT2toT1(TrainCar* &newTrainOne, TrainCar* &newTrainTwo) {
    TrainCar *tempTrain = newTrainTwo;
    while (tempTrain != NULL) {
        if (!tempTrain->isEngine()) {
            TrainCar *erasedEngine = eraseCar(newTrainTwo, tempTrain);
            PushBack(newTrainOne, erasedEngine);
            break;
        }
        tempTrain = tempTrain->next;
    }
}