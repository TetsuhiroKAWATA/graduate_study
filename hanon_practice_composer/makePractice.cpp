#include "makePractice.h"

makePractice::makePractice() {
	std::cout << "基礎練習(1～20)の練習作った。\n";
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	for (int i = 0; i < MusicNum; i++) {
		Ind[i] = new Individual();
	}
}

makePractice::~makePractice() {

}

void makePractice::printResult() {
	std::cout << "ぷりんとりざると\n";
}