#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	std::cout << "めいくぷらくてぃす\n";
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	//スコープ的な意味でめんどくさいから新しく作る
	int selectedNum = selectNum;//この番号の練習作るぞ

	//調を決定する(data_controllerここで定義するのやめたほうが良いかも・・・)
	if (selectedNum == 0 || selectedNum == 3 || selectedNum == 4) {
		musicChord = 'C';
		std::cout << "楽曲の調は、" << musicChord << "dur です。\n";
	}
	else if (selectedNum == 1) {
		std::cout << "楽曲の調が可変です。\n任意の調を以下から選択してください。\n";
	}
	else if (selectedNum == 2) {
		std::cout << "楽曲の調が可変です。\n任意の調を以下から選択してください。\n";
	}
	else {
		std::cout << "番号選択が間違っています。\n";
		exit(1);
	}

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