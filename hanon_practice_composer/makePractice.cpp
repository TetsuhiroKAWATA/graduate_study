#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "めいくぷらくてぃす\n";
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	//スコープ的な意味でめんどくさいから新しく作る
	int selectedNum = selectNum;//この番号の練習作るぞ

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "回目\n";
		Ind[i] = new Individual();
		newInd[i] = new Individual();

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

void makePractice::printResult() {
	std::cout << "ぷりんとりざると\n";
}