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
	int tmp, tmp2 = 0, tmp3;//tmp
	int PT[7];//PTが入る場所を格納
	int noteRange[2];//小節ごとの音域入れとくやつ
	std::string tmpS;
	std::string nowChord[3];//今の小節の和音
	int nowChordNum[3];//小節の和音の構成音がnotes[]の何処に入ってるか覚えるやつ
	std::string randomTable[35];
	int counter;

	//Xを入れる
	for (int i = 1; i <= data->Xceil; i++) {
		randomTable[i-1] = "X";
		randomTable[i-1] += std::to_string(i);
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
				//色々初期化
				counter = data->Xceil;
				chrom[j * data->noteNum[1] + (i * 65) + 1] = "-999";

				//std::cout << "nowChordNum = ";
				//コード設定
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp+1;
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
					if (decideNoteNum(1, restProb) == 1)
						chrom[PT[k]] = "P";
					else
						chrom[PT[k]] = "T";
				}

				//始めの音決める
				tmp = decideNoteNum(0, 2);//和音の第何音を始めの音に利用するか
				tmp2 = data->chordProg[j] - '0';//現在の小節の和音が何度か
				tmp2 += (tmp * 2);//始めの音の度数(1スタート。プログラムは基本0始まりだが、度数だけ1始まり)
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
				//1始まりのはず
				noteRange[0] = data->hanon[2][0] - '0';
				noteRange[1] = data->hanon[2][1] - '0';
				noteRange[0] += nowChordNum[0];
				noteRange[1] += nowChordNum[0];
				noteRange[0]--;
				noteRange[1]--;
				/*没になった、ランダムで決めるパターン
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
				}*/
				std::cout << "音域:" << noteRange[0] << " 〜 " << noteRange[1] << '\n';

				//音繋げフェーズ
				tmp = 0;
				for (int k = 1; k < 8; k++) {
					counter -= tmp;
					tmp = 0;
					if (chrom[j * data->noteNum[1] + (i * 65) + k] ==  "-999") {
						//このif文内で処理をする
						tmpS = chrom[j * data->noteNum[1] + (i * 65) + k - 1].substr(0, 1);//一個前の遺伝子の最初の文字
						
						//直前のTP以外の要素を探す
						//tmpSに直前の音(C4とか)が入る必要があるため、Yだったら下で処理を行う
						int X = 1;
						do {
							if (tmpS == "T" || tmpS == "P") {
								X++;
								tmpS = chrom[j * data->noteNum[1] + (i * 65) + k - X].substr(0, 1);
							}
							else {
								break;
							}
						} while (1);

						//Yだった時の処理
						if (tmpS == "Y") {
							int l = 1;
							do {
								if (chrom[j * data->noteNum[1] + (i * 65) + k - X - l].substr(0, 1) == "X") {
									tmp2 = stoi(chrom[j * data->noteNum[1] + (i * 65) + k - X - l].substr(1));
									break;
								}
								l++;
							} while (1);
							
							if (1 <= tmp2 && tmp2 <= 7) {
								char tmpC = data->hanon[0][tmp2 - 1];
								tmp3 = int(tmpC - '0');
							}
							else if (8 <= tmp2 && tmp2 <= 13) {
								char tmpC = data->hanon[0][tmp2 - 7 - 1];
								tmp3 = int(tmpC - '0');
							}
							else if (14 <= tmp2 && tmp2 <= 20) {
								char tmpC = data->hanon[1][tmp2 - 13 - 1];
								tmp3 = int(tmpC - '0');
							}
							else if (21 <= tmp2 && tmp2 <= 26) {
								char tmpC = data->hanon[1][tmp2 - 20 - 1];
								tmp3 = int(tmpC - '0');
							}
							else {
								std::cout << "直前がYだった時の処理が上手くいっていません\n";
							}
							//tmp3に入るのがXの中身になっており、Yの中身になっていない
							tmp3 += nowChordNum[0];
							tmp3 -= 1;
							tmpS = data->notes[tmp3 - 1];
							//std::cout << "tmp2 = " << tmp2 << ", tmp3 = " << tmp3 << '\n';
						}

						//コードの構成音だった時の処理
						if (tmpS == nowChord[0]
							|| tmpS == nowChord[1]
							|| tmpS == nowChord[2]) {
							//和音の構成音、或いは隣接音から選択
							//Yを繋げる処理もこの中でやる
							//音を数字に変換
							if (tmpS == nowChord[0]) {
								if (noteRange[0] <= nowChordNum[1] && nowChordNum[1] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[1]-1];
									tmp++;
									if (nowChordNum[1] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[2] && nowChordNum[2] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[2]-1];
									tmp++;
									if (nowChordNum[2] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
							}
							else if (tmpS == nowChord[1]) {
								if (noteRange[0] <= nowChordNum[0] && nowChordNum[0] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[0]-1];
									tmp++;
									if (nowChordNum[0] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[2] && nowChordNum[2] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[2]-1];
									tmp++;
									if (nowChordNum[2] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
							}
							else {
								if (noteRange[0] <= nowChordNum[0] && nowChordNum[0] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[0]-1];
									tmp++;
									if (nowChordNum[0] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[1] && nowChordNum[1] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[1]-1];
									tmp++;
									if (nowChordNum[1] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
							}
						}

						//隣接音を選択用テーブルに追加
						//汚すぎるコード直したい
						//std::cout << "tmpS = " << tmpS << '\n';
						if (tmpS == "C")
							tmp2 = 1;
						else if (tmpS == "D")
							tmp2 = 2;
						else if (tmpS == "E")
							tmp2 = 3;
						else if (tmpS == "F")
							tmp2 = 4;
						else if (tmpS == "G")
							tmp2 = 5;
						else if (tmpS == "A")
							tmp2 = 6;
						else if (tmpS == "H")
							tmp2 = 7;
						else
							std::cout << "要素が不正です。\n";

						if (chrom[j * data->noteNum[1] + (i * 65) + k - X].substr(0, 1) != "Y"
							&& chrom[j * data->noteNum[1] + (i * 65) + k - X].substr(1, 1) == "5") {
							tmp2 += 7;
						}

						//下の音
						if (2 <= tmp2 && tmp2 <= 10 && noteRange[0] <= tmp2-1 && tmp2-1 <= noteRange[1]) {
							randomTable[counter++] = data->notes[tmp2 - 2];
							tmp++;
							if (tmp2-1 < 8)
								randomTable[counter - 1] += "4";
							else
								randomTable[counter - 1] += "5";
						}

						//上の音
						if (1 <= tmp2 && tmp2 <= 9 && noteRange[0] <= tmp2+1 && tmp2+1 <= noteRange[1]) {
							randomTable[counter++] = data->notes[tmp2];
							tmp++;
							if (tmp2+1 < 8)
								randomTable[counter - 1] += "4";
							else
								randomTable[counter - 1] += "5";
						}

						//選んで入れる
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[j * data->noteNum[1] + (i * 65) + k] = randomTable[tmp2];

						//Yを繋げる処理
						if (randomTable[tmp2].substr(0, 1) == "X") {
							int l = 0;
							do {
								l++;
								if (chrom[j * data->noteNum[1] + (i * 65) + k + l] == "-999") {
									chrom[j * data->noteNum[1] + (i * 65) + k + l] = "Y";
									break;
								}
							} while (1);

							tmp3 = stoi(randomTable[tmp2].substr(1));
							if ((8 <= tmp3 && tmp3 <= 13) || (21 <= tmp3 && tmp3 <= 26)) {
								do {
									l++;
									if (chrom[j * data->noteNum[1] + (i * 65) + k + l] == "-999") {
										chrom[j * data->noteNum[1] + (i * 65) + k + l] = "Y";
										break;
									}
								} while (1);
							}
						}
					}
				}

				//中身確認
				for (int k = 0; k < 8;k++){
					std::cout << chrom[j * data->noteNum[1] + (i * 65) + k] << ", ";
				}
				std::cout << "\n\n";
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