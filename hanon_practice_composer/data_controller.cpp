#include "data_controller.h"

data_controller::data_controller() {
	std::cout << "データを読み込んだ\n";
	//基礎データ読む
	tmpp = (char*)key;
	readData("../data/foundation/key.csv", tmpp, Kstuck, Kline);
	tmpp = (char*)scaleTKeynote;
	readData("../data/foundation/scale_tmp_keynote.csv", tmpp, Sstuck, Sline);


}

data_controller::~data_controller() {
}


void data_controller::readData(std::string fileName, char* p, int chunkNum, int lineNum) {
	std::cout << "Debug::readData:" << fileName << "\n";
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
			for (int j = 0; j < lineNum*2; j+=2) {
				p[lineNum * i + j/2] = textHolder[j];
			}
		}
	}
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