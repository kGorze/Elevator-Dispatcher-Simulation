#pragma once
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>

class ElevatorCar {
	
	//bool isMoving;
	//bool isMovingUp;


	int capacity,currentFloor ,currentLoad ,number;
	//int destination
	enum ElevatorCarDirection {
		UP,DOWN,IDLE
	};
	ElevatorCarDirection direction;
	//IDLE (->) minFloor
	
	// W przysz�o�ci mo�e by� podzielone na segmenty
	//currentFloor
	//startFloor
	//endFloor

public:
	ElevatorCar();
	ElevatorCar(int number_a ,int capacity_a, int currentFloor_a = 0, ElevatorCarDirection ElevatorCarDirection_a = IDLE);
	~ElevatorCar();
	ElevatorCar createElevator(int number_a);
	void moveToFloor(int floor_a);

	int getCapacity();
	int getCurrentFloor();
	int getNumber();
	ElevatorCarDirection getDirection();


};
#endif