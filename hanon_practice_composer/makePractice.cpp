#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "めいくぷらくてぃす\n";
	//初期化
	toRead = NULL;
	
	//data_controllerはここで一回呼び、以降はpublicのデータだけポインタで指定して云々
	Cont = new data_controller();

	Cont->selectedNum = selectNum;//この番号の練習作るぞ

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "回目\n";
		Ind[i] = new Individual(Cont);
		newInd[i] = new Individual(Cont);
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
	switch (Cont->selectedNum) {
	case 0:
		Cont->chromLen = 128;

		//コード進行決める。
		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/fingertrain/chordProg.csv", toRead, 1, barNum*2);

		//音数
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;//1の予定だったけど都合上2に変更
		Cont->noteNumEnd[1] = 6;

		//拍子
		Cont->beat = 4;

		//左手の形
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/fingertrain/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		//ハノンの旋律読み込み
		toRead = (char*)(Cont->hanon);
		makePass = "../data/fingertrain/practice_" + std::to_string(Cont->hanonNum);
		makePass += ".csv";
		Cont->readData(makePass, toRead, 3, noteHNum);//3:上り、下り、音域　12:音数自体は8だけど、領域の大きさを書かないといけないため、12
		
		//Xの範囲指定
		Cont->Xceil = 26;

		break;
	case 1:
		Cont->chromLen = 128;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/scale/chordProg.csv", toRead, 1, barNum * 2);

		//音数
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//拍子
		Cont->beat = 4;

		//左手
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/scale/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		//ハノン読み込み(スケールだけど)
		toRead = (char*)(Cont->hanon);
		Cont->readData("../data/scale/hanon.csv", toRead, 3, noteHNum);

		Cont->Xceil = 2;

		break;
	case 2:
		//アルペジオ
		Cont->chromLen = 96;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/arpeggio/chordProg.csv", toRead, 1, barNum * 2);

		//音数
		Cont->noteNum[0] = 3;
		Cont->noteNum[1] = 6;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		Cont->beat = 3;

		//左手(アルペジオ)
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/arpeggio/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 6;

		Cont->Xceil = 0;
		Cont->tempo = 120;

		break;
	case 3:
		//オクターブ
		Cont->chromLen = 128;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/octave/chordProg.csv", toRead, 1, barNum * 2);

		//音数
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//拍子
		Cont->beat = 4;

		//左手
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/octave/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		Cont->Xceil = 0;
		Cont->tempo = 120;

		break;
	case 4:
		Cont->chromLen = 96;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/chromaticscale/chordProg.csv", toRead, 1, barNum * 2);

		//音数
		Cont->noteNum[0] = 3;
		Cont->noteNum[1] = 6;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//拍子
		Cont->beat = 3;

		//左手
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/chromaticscale/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 3;

		toRead = (char*)(Cont->hanon);
		Cont->readData("../data/chromaticscale/hanon.csv", toRead, 3, noteHNum);

		Cont->tempo /= 2;
		Cont->Xceil = 2;
		break;
	default:
		std::cout << "入力された数字が間違っています。\n";
		exit(1);
	}
}

void makePractice::firstTake() {
	for (int i = 0; i < MusicNum; i++) {
		Ind[i]->firstTake(Cont->selectedNum);
	}
}

void makePractice::sort(int lb, int ub) {
	int i, j, k;
	double pivot;
	Individual* tmp;

	if (lb < ub) {
		k = (lb + ub) / 2;
		pivot = Ind[k]->point;
		i = lb;
		j = ub;

		do {
			while (Ind[i]->point < pivot)
				i++;
			while (Ind[j]->point > pivot)
				j--;
			if (i <= j) {
				tmp = Ind[i];
				Ind[i] = Ind[j];
				Ind[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

void makePractice::alternate() {
	Individual* tmp;
	int p1, p2;//両親
	int pointSum = 0, Sum = 0;//点数の合計、合計を保存しておく場所

	//点数を合計
	for (int i = 0; i < MusicNum; i++)
		Sum += Ind[i]->point;

	//親個体を選択、交叉
	for (int i = 0; i < MusicNum; i++) {
		pointSum = Sum;
		//親1
		p1 = select(pointSum, -1);

		//親2
		pointSum -= Ind[p1]->point;
		p2 = select(pointSum, p1);
		//std::cout << i << "回目親" << p1 << ", " << p2 << '\n';

		//交叉させる
		newInd[i]->cross(Ind[p1], Ind[p2]);
	}


	//世代交代
	for (int i = 0; i < MusicNum; i++) {
		tmp = Ind[i];
		Ind[i] = newInd[i];
		newInd[i] = tmp;
	}

	//突然変異
	for (int i = 0; i < MusicNum; i++) {
		Ind[i]->mutate();
	}

	//表示
	/*for (int i = 0; i < MusicNum; i++) {
		std::cout << i + 1 << "曲目\n";
		Ind[i]->printChrom();
	}*/
}

void makePractice::printResult(int Num) {
	std::cout << "ぷりんとりざると:" << Num << "\n";
	Ind[Num]->printResult();
}

void makePractice::printMusic(int Num) {
	Ind[Num]->printMusic(Num);
}

int makePractice::select(int pointSum, int p1Num) {
	double prob, r;//prob:選ばれる確率が入る場所　r:0以上1以下の実数乱数を入れるやつ。
	int res = 0;

	r = ((double)rand() / RAND_MAX);

	for (int j = 0; j < MusicNum; j++) {
		prob = Ind[j]->point / (double)pointSum;
		if (j != p1Num && r <= prob) {
			res = j;
			break;
		}
		r -= prob;
	}

	return res;
}