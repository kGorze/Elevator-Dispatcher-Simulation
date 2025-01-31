#include "DispatcherUnit.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "../Header Files/PlatformUtils.h"

//definicja klasy DU

DispatcherUnit::DispatcherUnit() {};

//----------------------------------------------------------------------------------
static bool work_Finished = false;
//----------------------------------------------------------------------------------

// Na początku pliku, po include'ach
const int DEFAULT_MIN_FLOOR = 0;
const int DEFAULT_MAX_FLOOR = 10;
const int DEFAULT_ELEVATOR_CAPACITY = 5;
const int DEFAULT_ELEVATOR_NUMBER = 1;

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
	size_t size = allElevators.size();
	do {
		std::cout << "Wpisz numer windy(od 1 w gore): ";
		std::cin >> number_a;
	} while (number_a == 0);
	for (size_t i = 0; i < size; i++) {
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
	//CZAS
		void DispatcherUnit::incrementSimulationTime() {
			this->simulationTimePtr->incrementTime();

		}
		void DispatcherUnit::resetSimulationTime() {
			this->simulationTimePtr->setTime(0);
		}
		int DispatcherUnit::getTime() {
			return this->simulationTimePtr->getTime();
		}
		void DispatcherUnit::runTimer() {
			using namespace std::literals::chrono_literals;
			this->simulationTimePtr->setTime(0);
			while(!work_Finished) {
				this->incrementSimulationTime();
				std::this_thread::sleep_for(1s);
			}
		}
	//TWORZENIE PODSTAW
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
			std::cout << "------------------------------------------------------------------------" << std::endl;
			std::cout << "---- CROSSOVER VIEW ----" << std::endl;
			CrossoverView(Enquiries, moveQueue);
			std::cout << "---- CROSSOVER VIEW SKONCZONE ----" << std::endl;
			std::cout << "------------------------------------------------------------------------" << std::endl;
			std::cout << "---- URUCHAMIANIE WINDY ----" << std::endl;
			goWithMoveQueue();
			std::cout << "---- PRACA SKONCZONA ----" << std::endl;
			std::cout << "------------------------------------------------------------------------" << std::endl;

		}
		void DispatcherUnit::usePreconfiguratedSymulation() {
			try {
				// Podstawowa konfiguracja budynku i windy
				fillFloorVectorXY(floorStatus, 0, 8);  // Mniejszy budynek
				allElevators.push_back(ElevatorCar1.createElevator(1, 4));  // Mniejsza pojemność
				
				// Bardziej realistyczne zapytania
				Enquiries = {
					Zapytanie(0, 3),  // Krótsze dystanse
					Zapytanie(3, 5),
					Zapytanie(2, 4),
					Zapytanie(5, 1)
				};

				CrossoverView(Enquiries, moveQueue);
				goWithMoveQueueX(0);
			} catch (const std::exception& e) {
				std::cout << "Błąd podczas symulacji: " << e.what() << std::endl;
			}
		}
	//RUCH WINDY
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
						if(counter <= BestOsobnik.MovesAmount) {
							if (move && floor < maxFloor) {
								Elevator.setDirection(1);
								floor++;
							}
							else if (move && floor == maxFloor) {
								Elevator.setDirection(2);
								continue;
							}
							else if(move == 0 && floor > minFloor) {
								Elevator.setDirection(0);
								floor--;
							}
							else if(move == 0 && floor == minFloor){
								Elevator.setDirection(2);
								continue;
							}
							std::cout << "Aktualnie winda znajduje sie na: " << Elevator.getCurrentFloor() << " pietrze w kierunku: "<<Elevator.getDirectionString()<<"."<< std::endl;
							Elevator.moveToFloor(floor);
							std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
						}
						counter++;
						if (counter == BestOsobnik.MovesAmount +1) {
							Sleep(30000);
							return;
						}
					}
					return;
				}
				std::cout << "Winda o podanym numerze nie istnieje." << std::endl;
			}while(flag);
		}
		void DispatcherUnit::goWithMoveQueueX(int x) {
			int counter = 1;
			int floor = 0;
			ElevatorCar Elevator = allElevators[x];
			std::vector<int> peopleOnFloors(maxFloor + 1, 0);  // Liczba osób na każdym piętrze
			
			// Inicjalizacja liczby osób na piętrach na podstawie zapytań
			for (const auto& query : Enquiries) {
				peopleOnFloors[query.getMiejsceP()]++;
			}

			auto drawBuilding = [&](int currentFloor, const char* direction) {
				ClearScreen();
				std::cout << "\nSymulacja windy - Krok " << counter << " z " << BestOsobnik.MovesAmount << "\n\n";
				
				// Rysowanie budynku od góry do dołu
				for (int f = maxFloor; f >= minFloor; f--) {
					std::cout << std::setw(2) << f << " |";
					
					// Rysowanie windy lub pustej przestrzeni
					if (f == currentFloor) {
						std::cout << "[■]"; // Winda
					} else {
						std::cout << "   "; // Pusta przestrzeń
					}
					
					// Rysowanie osób czekających
					std::cout << " ";
					for (int p = 0; p < peopleOnFloors[f]; p++) {
						std::cout << "○"; // Osoba czekająca
					}
					
					std::cout << "\n";
				}
				
				std::cout << "---+-------------------\n";
				std::cout << "Kierunek: " << direction << "\n";
				std::cout << "Osoby w windzie: " << Elevator.getCapacity() << "\n";
				Sleep(500); // Opóźnienie dla lepszej wizualizacji
			};

			for (int move : moveQueue) {
				if (counter <= BestOsobnik.MovesAmount) {
					if (move && floor < maxFloor) {
						Elevator.setDirection(1);
						floor++;
						// Aktualizacja osób na piętrach
						for (auto it = Enquiries.begin(); it != Enquiries.end();) {
							if (it->getMiejsceP() == floor) {
								peopleOnFloors[floor]--;
								it = Enquiries.erase(it);
							} else {
								++it;
							}
						}
					}
					else if (move && floor == maxFloor) {
						Elevator.setDirection(2);
						continue;
					}
					else if (move == 0 && floor > minFloor) {
						Elevator.setDirection(0);
						floor--;
					}
					else if (move == 0 && floor == minFloor) {
						Elevator.setDirection(2);
						continue;
					}
					
					Elevator.moveToFloor(floor);
					drawBuilding(floor, Elevator.getDirectionString());
				}
				counter++;
				if (counter == BestOsobnik.MovesAmount + 1) {
					return;
				}
			}
		}
	//SYMULACJA
		void DispatcherUnit::runSimulation() {
			int preconfigurationTime,configurationTime,algorithmTime,moveTime;
			std::thread timeCounting;
			timeCounting = std::thread([this] {this->runTimer(); });
			preconfigurationTime = this->simulationTimePtr->getTime();

			fillFloorVectorXY(floorStatus, 0, 20);
			allElevators.push_back(ElevatorCar1.createElevator(1, 4));
			Data1.runDefault(Enquiries);
			configurationTime = this->simulationTimePtr->getTime() - preconfigurationTime;
			AlgorithmObliczania(Enquiries, moveQueue, allElevators[0].getCapacity());
			algorithmTime = this->simulationTimePtr->getTime() - configurationTime - preconfigurationTime;
			std::cout << std::endl;
			goWithMoveQueueX(0);
			work_Finished = true;
			moveTime = this->simulationTimePtr->getTime() - algorithmTime - configurationTime - preconfigurationTime;
			std::cout <<"Caosc trawla: " << this->simulationTimePtr->getTime() << " sekund." << std::endl;
			std::cout << "Czas wykonywania przed konfiguracja: " << preconfigurationTime << ", czas wykonywania konfiguracji: " << configurationTime
				<< ", czas wykonywania algorytmu: " << algorithmTime << ", czas wykonywania ruchu: " << moveTime << std::endl;
			timeCounting.join();
		}
		void DispatcherUnit::resetSimulation() { 
			floorStatus.clear();
			allElevators.clear();
			Enquiries.clear();
			ClearData(); // Algorytm
			//potrzebne jeszcze czyszczenie algorytmu i chyba troche innych // Dopisaem
		}//FUNKCJA POZWALAJCA PRZYWROCI ZMIENNE DO STANU POCZTKOWEGO 

//ALGORYTMY
void DispatcherUnit::callCrossover() {
	CrossoverView(Enquiries, moveQueue);
}
void DispatcherUnit::callAlgorithmConfiguration() {
	AlgorithmConfiguration();
}
void DispatcherUnit::simulationTest() {
	int preconfigurationTime, configurationTime, algorithmTime;
	std::thread timeCounting;
	timeCounting = std::thread([this] {this->runTimer(); });
	preconfigurationTime = this->simulationTimePtr->getTime();
	std::vector<Zapytanie> fileEnquiries;
	Data1.setEnquiryDataFile("Enquiries.csv");
	Data1.loadEnquiryDataFromFile(fileEnquiries);
	fillFloorVectorXY(floorStatus, 0, 20);
	allElevators.push_back(ElevatorCar1.createElevator(1, 4));
	Data1.runDefault(Enquiries);
	configurationTime = this->simulationTimePtr->getTime() - preconfigurationTime;
	SymulationFromFile(fileEnquiries, moveQueue, allElevators[0].getCapacity());
	algorithmTime = this->simulationTimePtr->getTime() - configurationTime - preconfigurationTime;
	std::cout << std::endl;
	goWithMoveQueueX(0);
	work_Finished = true;
	std::cout << "Caosc trawla: " << this->simulationTimePtr->getTime() << " sekund." << std::endl;
	std::cout << "Czas wykonywania przed konfiguracja: " << preconfigurationTime << ", czas wykonywania konfiguracji: " << configurationTime
		<< ", czas wykonywania algorytmu: " << algorithmTime << std::endl;
	timeCounting.join();
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
void DispatcherUnit::printDNA() {
	PrintRandomDNAForPopulation(AlgorithmPopulationSize());
	Sleep(30000); //GDY JU NIE BDZIESZ MUSIAL NICZEGO SPRAWDZAC TO USUN SLEEP
}
void DispatcherUnit::fileTest() {
}

//DANE
void DispatcherUnit::callDane() {
	Data1.runDefault(Enquiries);
}
void DispatcherUnit::callSaveEnquries() {
	Data1.saveEnquiryOutput(Enquiries);
}