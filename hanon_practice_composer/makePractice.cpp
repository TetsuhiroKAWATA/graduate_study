#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "めいくぷらくてぃす\n";
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	//スコープ的な意味でめんどくさいから新しく作る
	int selectedNum = selectNum;//この番号の練習作るぞ

	//データ整備をする。関数にしても良かったけどこの辺は1回しか弄らんし・・・
	switch (selectedNum) {
	case 0:
		Cont->chromLen = 128;

		//コード進行決める。8以上にしたいときはここ弄らんとならん
		Cont->chordProg[0] = '1';
		Cont->chordProg[1] = '4';
		Cont->chordProg[2] = '1';
		Cont->chordProg[3] = '5';
		Cont->chordProg[4] = '1';
		Cont->chordProg[5] = '4';
		Cont->chordProg[6] = '5';
		Cont->chordProg[7] = '1';

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
	//ここまで

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

void makePractice::printResult() {
	std::cout << "ぷりんとりざると\n";
}