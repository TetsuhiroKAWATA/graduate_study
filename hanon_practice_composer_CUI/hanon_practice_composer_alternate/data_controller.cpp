#include "data_controller.h"

data_controller::data_controller() {
	//std::cout << "データを読み込んだ\n";
	//基礎データ読む
	tmpp = (char*)key;
	readData("hpc/data/foundation/key.csv", tmpp, Kstuck, Kline);
	tmpp = (char*)scaleTKeynote;
	readData("hpc/data/foundation/scale_tmp_keynote.csv", tmpp, Sstuck, Sline);
}

data_controller::~data_controller() {
}


void data_controller::readData(std::string fileName, char* p, int chunkNum, int lineNum) {
	//std::cout << "Debug::readData:" << fileName << "\n";
	//ファイル開く
	fin.open(fileName);
	if (!fin) {
		std::cout << "file open error\n";
		exit(1);
	}

	//なんやかんや処理する
	for (int i = 0; i < chunkNum; i++) {
		if (!(fin.getline(textHolder, 80))) {
			break;
		}
		else {
			//std::cout << textHolder <<'\n';
			for (int j = 0; j < lineNum*2; j+=2) {
				p[lineNum * i + j/2] = textHolder[j];
				textHolder[j] = NULL;
			}
		}
	}
	fin.close();
}

//string型が全て数字か確かめるぷろぐらむ
bool data_controller::checkInt(std::string input) {
	if (std::all_of(input.cbegin(), input.cend(), isdigit)) {
		return true;
	}
	return false;
}

void data_controller::makeScale() {
	//違う方法ありそうだけどちょっと無理
	int tmp = 0, tmp2 = 0, counter = 0;
	char tmpKey[2] = {'X',0};
	char tmpC[2] = {'X',0 };

	tmpKey[0] = key[chordNum][0];//調、chordNumから取ってこられる
	//std::cout << "tmpKey = " << tmpKey << '\n';

	if (strcmp(tmpKey, "C") == 0 || strcmp(tmpKey, "c") == 0)
		heiDiff = 0;
	else if (strcmp(tmpKey, "D") == 0 || strcmp(tmpKey, "d") == 0)
		heiDiff = 1;
	else if (strcmp(tmpKey, "E") == 0 || strcmp(tmpKey, "e") == 0)
		heiDiff = 2;
	else if (strcmp(tmpKey, "F") == 0 || strcmp(tmpKey, "f") == 0)
		heiDiff = 3;
	else if (strcmp(tmpKey, "G") == 0 || strcmp(tmpKey, "g") == 0)
		heiDiff = 4;
	else if (strcmp(tmpKey, "A") == 0 || strcmp(tmpKey, "a") == 0)
		heiDiff = 5;
	else if (strcmp(tmpKey, "H") == 0 || strcmp(tmpKey, "h") == 0)
		heiDiff = 6;
	else
		std::cout << "何かが違います\n";
	
	for (int i = 0; i < 7; i++) {
		convNotes[i] = notes[i + heiDiff];
	}

	tmpC[0] = scaleTKeynote[typeofChord][0];
	//臨時記号にフラットが付くことは考慮していません。現状存在しないからね仕方ないね
	if (strcmp(tmpC, "#") == 0) {
		tmp = scaleTKeynote[typeofChord][++counter] - '0';
		for (int j = 0; j < tmp; j++) {
			counter++;
			tmp2 = scaleTKeynote[typeofChord][counter] - '0';
			convNotes[tmp2 - 1] += "#";
		}
	}

	//映し
	for (int i = 0; i < 7; i++) {
		convNotes[i + 7] = convNotes[i];
	}

	//追加分
	convNotes[14] = convNotes[0];

	std::cout << "res:";
	for (int i = 0; i < 15; i++) {
		std::cout << convNotes[i] << ", ";
	}
	std::cout << '\n';
}

void data_controller::loadSNum() {
	std::ifstream fin;
	std::string path = "hpc/data/selectedNum/selectedNum.csv";

	fin.open(path);
	if (!fin) {
		std::cout << "ファイルオープンエラー";
	}

	fin >> selectedNum;
	std::cout << "selectedNum:" << selectedNum << '\n';
	fin.close();
}

void data_controller::loadMusicNum() {
	std::ifstream fin;
	std::string path = "hpc/data/musicNum/musicNum.csv";

	fin.open(path);
	if (!fin) {
		std::cout << "ファイルオープンエラー";
	}

	fin >> hanonNum;
	std::cout << "hanonNum:" << hanonNum << '\n';
	fin.close();
}

void data_controller::loadChordNum() {
	std::ifstream fin;
	std::string path = "hpc/data/chordNum/chordNum.csv";
	std::string tmp, tmp2;

	fin.open(path);
	if (!fin) {
		std::cout << "ファイルオープンエラー";
	}

	fin >> tmp;
	std::cout << tmp.substr(2,1);
	if (tmp.size() == 4) {
		tmp2 = tmp.substr(0, 2);
		chordNum = std::stoi(tmp);
		tmp2 = tmp.substr(3, 1);
		typeofChord = std::stoi(tmp2);
	}
	else {
		chordNum = std::stoi(tmp.substr(0, 1));
		typeofChord = std::stoi(tmp.substr(2, 1));
	}
	std::cout << "typeofChord:" << typeofChord << "\nchordNum:" << chordNum << '\n';
	fin.close();
}


void data_controller::confirmCorrect(int tate, int yoko) {
	for (int i = 0; i < tate; i++) {
		for (int j = 0; j < yoko; j++) {
			std::cout << scaleTKeynote[i][j] << ' ';
		}
		std::cout << '\n';
	}	
}