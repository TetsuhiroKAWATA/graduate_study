#include "makePractice.h"

makePractice::makePractice() {
	Cont = new data_controller();
	std::cout << "基礎練習(1〜20)の練習作った。\n";
}

makePractice::~makePractice() {

}

void makePractice::printResult() {
	std::cout << "ぷりんとりざると\n";
}