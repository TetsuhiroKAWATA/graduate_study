#include "Individual.h"

Individual::Individual(data_controller* d) {
	//std::cout << "個体作った\n";
	data = d;
	//char doNotUse = d->key[0][0];
	//std::cout << "Eが出たら正解:" << data->notes[2] << "\n";
	
	//個体ナンバー管理(Ind[i]のiでやったほうが早そうだけどなんか別のこと考えてたんだよねたぶん・・・)
	data->GproductSum+=0.5;
	productNum = (int)data->GproductSum;
	point = -1;
	//初期化
	for (int i = 0; i < 128; i++) {
		chrom[i] = "-999";
	}
}

Individual::~Individual() {
}

void Individual::firstTake(int selectNum) {
	//std::cout << "初期個体作成\n";//makePractice.cppで任意の数読んでるので大丈夫
	//std::cout << "Debug::selectedNum = " << selectNum << '\n';

	int noteNum;//音数を入れる
	int tmp, tmp2 = 0;//tmp
	int PT[7];//PTが入る場所を格納
	int noteRange[2];//小節ごとの音域入れとくやつ
	std::string tmpS;
	std::string nowChord[3];//今の小節の和音
	int nowChordNum[3];//小節の和音の構成音がnotes[]の何処に入ってるか覚えるやつ
	std::string randomTable[30];

	//Xを入れる
	for (int i = 1; i <= data->Xceil; i++) {
		randomTable[i] = "X";
		randomTable[i] += std::to_string(i);
	}

	switch (selectNum) {
	case 0:
		std::cout << "1~20の初期作成\n";
		std::cout << "productNum = " << productNum << '\n';

		//初期集団作る
		// 初期化
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			for (int j = 0; j < meloMakeNum; j++) {
				//コード設定
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					if (tmp > 6)
						tmp -= 7;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp;
					std::cout << nowChordNum[k];
				}

				//音数
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);

				//リズム
				//1でT,2でPを入れるようになっている
				tmp = data->noteNum[1] - noteNum;//PTの数
				for (int k = 0; k < tmp; k++) {
					do {
						int l;
						PT[k] = decideNoteNum(j * data->noteNum[1] + (i * 65) + 1, j * data->noteNum[1] + (i * 65) + 7);
						for (l = 0; l < k; l++) {
							if (PT[l] == PT[k])
								break;
						}
						if(l == k)
							break;
					} while (1);
				}

				for (int k = 0; k < tmp; k++) {
					if (decideNoteNum(1, 2) == 1)
						chrom[PT[k]] = "T";
					else
						chrom[PT[k]] = "P";
				}

				//始めの音決める
				tmp = decideNoteNum(0, 2);//和音の第何音を始めの音に利用するか
				tmp2 = data->chordProg[j] - '0';//現在の小節の和音が何度か
				tmp2 += (tmp * 2);//始めの音の度数(1スタート。適切なタイミングで0スタートに変換)
				chrom[j * data->noteNum[1] + (i * 65)] = data->notes[(tmp2-1) % 7];

				if (tmp2 < 8) {
					chrom[j * data->noteNum[1] + i * 65] += "4";
				}
				else if (tmp2 < 16) {
					chrom[j * data->noteNum[1] + i * 65] += "5";
				}
				else {
					std::cout << "バグってますね\n";
					exit(1);
				}

				//音域決定
				noteRange[0] = data->hanon[2][0] - '0';
				noteRange[1] = data->hanon[2][1] - '0';
				if (noteRange[1] < tmp2 || noteRange[0] > tmp2) {
					noteRange[0] += (tmp2 - noteRange[1]);
					noteRange[1] += (tmp2 - noteRange[1]);
				}
				if (noteRange[1] <= 10) {
					if (tmp2 - noteRange[0] < 10 - noteRange[1]) {
						tmp = decideNoteNum(0, tmp2 - noteRange[0]);
					}
					else {
						tmp = decideNoteNum(0, 10 - noteRange[1]);
					}
					if (tmp <= noteRange[1] - noteRange[0]) {
						noteRange[0] += tmp;
						noteRange[1] += tmp;
					}
				}
				//std::cout << "音域:" << noteRange[0] << " ～ " << noteRange[1] << '\n';

				//音繋げフェーズ
				for (int k = 1; k < 8; k++) {
					if (chrom[j * data->noteNum[1] + (i * 65) + k] ==  "-999") {
						//このif文内で処理をする
						tmpS = chrom[j * data->noteNum[1] + (i * 65) + k - 1].substr(0, 1);//一個前の遺伝子の最初の文字
						if (tmpS == nowChord[0]
							|| tmpS == nowChord[1]
							|| tmpS == nowChord[2]) {
							//和音の構成音、或いは隣接音から選択
							//Yを繋げる処理もこの中でやる
							//音を数字に変換
							//ここに隣接音の処理を入れる
							if (tmpS == nowChord[0]) {
								randomTable[data->Xceil] = data->notes[nowChordNum[1]];
								randomTable[data->Xceil + 1] = data->notes[nowChordNum[2]];
								std::cout << "randomTable = ";
								std::cout << randomTable[data->Xceil] << ' ' << randomTable[data->Xceil + 1] << '\n';
							}
							else if (tmpS == nowChord[1]) {
								randomTable[data->Xceil] = data->notes[nowChordNum[0]];
								randomTable[data->Xceil + 1] = data->notes[nowChordNum[2]];
								std::cout << randomTable[data->Xceil] << ' ' << randomTable[data->Xceil + 1] << '\n';
							}
							else {
								randomTable[data->Xceil] = data->notes[nowChordNum[0]];
								randomTable[data->Xceil + 1] = data->notes[nowChordNum[1]];
								std::cout << randomTable[data->Xceil] << ' ' << randomTable[data->Xceil + 1] << '\n';
							}
						}
						else {
							//隣接音から選択
							std::cout << "構成音じゃない";
						}
					}
				}

				//中身確認
				for (int k = 0; k < 8;k++){
					std::cout << chrom[j * data->noteNum[1] + (i * 65) + k];
				}
				std::cout << '\n';
			}
		}

		break;
	case 1:
		//std::cout << "スケールの初期集団作成\n";
		break;
	case 2:
		//std::cout << "アルペジオの初期集団作成\n";
		break;
	case 3:
		//std::cout << "オクターブの初期集団作成\n";

		break;
	case 4:
		//std::cout << "半音階の初期集団作成\n";

		break;
	default:
		std::cout << "正しくない値\n";
		break;
	}
}

int Individual::decideNoteNum(int lower, int upper) {
	int res = lower + rand() % (upper - lower + 1);
	return res;
}