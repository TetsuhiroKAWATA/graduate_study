#include "data_controller.h"

data_controller::data_controller() {
	std::cout << "データを読み込んだ\n";
	for (int i = 0; i < dataNum; i++) {
		readData(toRead[i]);
	}

}

data_controller::~data_controller() {

}


void data_controller::readData(std::string fileName) {
	std::cout << "Debug::readData:" << fileName << "\n";
	
}