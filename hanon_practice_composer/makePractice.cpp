#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "めいくぷらくてぃす\n";
	//初期化
	toRead = NULL;
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	//スコープ的な意味でめんどくさいから新しく作る
	int selectedNum = selectNum;//この番号の練習作るぞ

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "回目\n";
		Ind[i] = new Individual(Cont);
		newInd[i] = new Individual(Cont);

		//初期集団作成もここでやっちゃえ！
		Ind[i]->firstTake(selectedNum);
	}
}

makePractice::~makePractice() {
	for (int i = 0; i < MusicNum; i++) {
		delete Ind[i];
		delete newInd[i];
	}

	//delete Cont;->こいついらんのか？
}

void makePractice::dataPrepare() {
	switch (selectedNum) {
	case 0:
		Cont->chromLen = 128;

		//コード進行決める。
		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/fingertrain/chordProg.csv", toRead, 1, barNum);

		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 1;
		Cont->noteNumEnd[1] = 6;

		Cont->beat = 4;

		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/fingertrain/accompany.csv", toRead, chordKinds, 6);

		toRead = (char*)(Cont->hanon);
		makePass = "../data/fingertrain/practice_" + std::to_string(Cont->hanonNum);
		makePass += ".csv";

		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		std::cout << "入力された数字が間違っています。\n";
		exit(1);
	}
}

void makePractice::printResult() {
	std::cout << "ぷりんとりざると\n";
}