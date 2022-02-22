#include "DispatcherUnit.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

//definicja klasy DU

DispatcherUnit::DispatcherUnit() {};


//POMOCNICZE
template <typename T>
bool contains(std::vector<T> vec, const T& elem)
{
	bool result = false;
	if (find(vec.begin(), vec.end(), elem) != vec.end())
	{
		result = true;
	}
	return result;
}

//PIETRA
void DispatcherUnit::createFloorVector() {
	fillFloorVector(floorStatus);
}
void DispatcherUnit::displayFloorVector() {
	printFloorVector(floorStatus);
	printFloorVariables();
}
void DispatcherUnit::sortFloorVector() {
	sortVector(floorStatus);
}
void DispatcherUnit::eraseFloorVector() {
	if (floorStatus.empty()) {
		std::cout << "Wektor jest obecnie pusty. Nadus ENTER";
		return;
	}
	std::cout << "Wektor zostala usuniety. Nadus ENTER";
	floorStatus.clear();
}
void DispatcherUnit::addFloorVectorElement() {
	addFloor(floorStatus);
}
void DispatcherUnit::eraseFloorVectorElement() {
	eraseFloor(floorStatus);
}
void DispatcherUnit::eraseGroupFloorVector() {
	eraseGroupFloor(floorStatus);
}


//WINDA
void DispatcherUnit::addElevatorToVector() {


	//std::cin.clear();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//std::string reminder;
	//std::getline(std::cin, reminder);
	//std::cout << "POZOSTALOSCI :" << reminder << std::endl;

	int number_a, capacity_a;
	unsigned int size = allElevators.size();
	do {
		std::cout << "Wpisz numer windy(od 1 w gore): ";
		std::cin >> number_a;
	} while (number_a == 0);
	for (int i = 0; i < size; i++) {
		while (number_a == allElevators[i].getNumber()) {
			std::cout << "Winda z podanym numerem juz jest aktywna. " << std::endl;
			std::cout << "Podaj nowy numer: ";
			std::cin >> number_a;
		}
	}
	std::cout << "Wpisz ilosc miejsca: ";
	std::cin >> capacity_a;
	ElevatorCar temporary = ElevatorCar1.createElevator(number_a, capacity_a);
	allElevators.push_back(temporary);
}
void DispatcherUnit::displayElevatorVector() {
	unsigned int size = allElevators.size();
	printFloorVariables();
	if (allElevators.empty()) {
		std::cout << "Brak wind." << std::endl;
		return;
	}
	/*for (std::map<int, ElevatorCar>::iterator it = allElevators.begin(); it != allElevators.end(); ++it) {
		if (it->first == 0) {
			std::cout << "jest pentla";
			allElevators.erase(it);
		}
	}
	for (unsigned int i = 0; i < size; i++) {
		if (size > 1) {
			it = allElevators.find(0);
			allElevators.erase(it);
		}
	}
	std::map<int, ElevatorCar>::iterator it;
	it = allElevators.find(0);
	allElevators.erase(it);
	*/

	std::cout << "Mapa posiada obecnie: " << size << " , wind." << std::endl;
	for (unsigned int i = 0; i < size; i++) {
		std::cout << "Winda nr: " << allElevators[i].getNumber() << " Ktora obecnie jest na: " << allElevators[i].getCurrentFloor() << " pietrze." << std::endl;
		std::cout << "Ma pojemnosc: " << allElevators[i].getCapacity() << " Jest w stanie: " << allElevators[i].getDirection() << std::endl;
		std::cout << "Ktora pracuje od: " << allElevators[i].getMinFloorElev() << ", do: " << allElevators[i].getMaxFloorElev() <<", pietra." << std::endl;
	}
};
void DispatcherUnit::clearElevatorVector() {
	if (allElevators.empty()) {
		std::cout << "Wektor wind jest obecnie pusty. Nadus ENTER";
		return;
	}
	std::cout << "Wektor wind zostal usunienty. Nadus ENTER";
	allElevators.clear();
}


//ZAPYTANIA
void DispatcherUnit::addEnquiryToVector() {
	fillEnquiryVector(Enquiries);
}
void DispatcherUnit::displayEnquiries() {
	printVector(Enquiries);
}
void DispatcherUnit::addOneEnquiry() {
	addEnquiry(Enquiries);
}
void DispatcherUnit::eraseOneEnquiryDisplay() {
	int index;
	displayEnquiries();
	std::cout << "Podaj index ktory chce usunac: " << std::endl;
	std::cin >> index;
	eraseEnquiryByIndex(Enquiries, index);
}

//SYMULACJA
void DispatcherUnit::createDefaultRequirements() {
	std::cout << "---- TWORZENIE MAPY PIETER ----" << std::endl;
	createFloorVector();
	if (floorStatus.size() == 0) {
		std::cout << "--- BLAD W TWORZENIU MAPY PIETER ---" << std::endl;
	}
	std::cout << "---- MAPA PIETER STWORZONA ----" << std::endl;

	std::cout << "---- TWORZENIE WINDY ----" << std::endl;
	addElevatorToVector();
	if (allElevators.size() == 0) {
		std::cout << "--- BLAD W TWORZENIU WINDY ---" << std::endl;
	}
	std::cout << "---- WINDA STWORZONA ----" << std::endl;

	std::cout << "---- TWORZENIE ZAPYTAN ----" << std::endl;
	addEnquiryToVector();
	if (Enquiries.size() == 0) {
		std::cout << "--- BLAD W TWORZENIU ZAPYTAN ---" << std::endl;
	}
	std::cout << "---- ZAPYTANIA STWORZONE ----" << std::endl;

}
void DispatcherUnit::moveElevatorCarToManual() {
	int number, floor;
	bool flag = true;
	displayElevatorVector();
	if (allElevators.empty()) {
		std::cout << "Wektor wind jest pusty";
		return;
	}
	do {
		std::cout << "Wybierz numer windy ktora ma wykonac ruch: " << std::endl;
		std::cin >> number;
		auto it = std::find_if(allElevators.begin(), allElevators.end(), [&number](ElevatorCar& obj) {return obj.getNumber() == number; });
		if (it != allElevators.end())
		{
			flag = false;
			ElevatorCar Elevator = *it;
			std::cout << "Podaj pietro na ktore ma sie przeniesc: " << std::endl;
			std::cin >> floor;
			Elevator.moveToFloor(floor);
			//auto index = std::distance(allElevators.begin(), it);
			//allElevators[index].moveToFloor(floor);
			return;
		}
		std::cout << "Winda o podanym numerze nie istnieje." << std::endl;
	} while (flag);
}
void DispatcherUnit::goWithMoveQueue(){
	int number, floor = 0,counter = 0;
	bool flag = true;
	if (allElevators.empty()) {
		std::cout << "Wektor wind jest pusty";
		return;
	}
	if (moveQueue.empty()) {
		std::cout << "Wektor ruchu windy jest pusty";
		return;
	}
	do{
		std::cout << "Wybierz numer windy ktora ma wykonac ruch: " << std::endl;
		std::cin >> number;
		auto it = std::find_if(allElevators.begin(), allElevators.end(), [&number](ElevatorCar& obj) {return obj.getNumber() == number; });
		if (it != allElevators.end())
		{
			flag = false;
			ElevatorCar Elevator = *it;
			for (int move : moveQueue) {
				std::cout << counter << "\t";
				if(counter <= BestOsobnik.Fitness) {
					if (move) {
						floor++;
					}
					else {
						floor--;
					}
					std::cout << "Aktualnie winda znajduje sie na: " << Elevator.getCurrentFloor() << " pietrze." << std::endl;
					Elevator.moveToFloor(floor);
					std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
				}
				counter++;
				if (counter == 19) {
					Sleep(30000);
					return;
				}
			}
			return;
		}
		std::cout << "Winda o podanym numerze nie istnieje." << std::endl;
	}while(flag);
}

//ALGORYTMY
void DispatcherUnit::callCrossover() {
	CrossoverView(Enquiries, moveQueue);
}
void DispatcherUnit::callTest() {
	Testowa();
}
void DispatcherUnit::printMoveQueue() {
	if (moveQueue.empty()) {
		std::cout << "Wektor ruchu windy jest pusty.";
		return;
	}
	else {
		for (int i : moveQueue) {
			std::cout << i << " ";
		}
	}
}