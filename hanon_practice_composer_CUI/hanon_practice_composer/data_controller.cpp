#include "data_controller.h"

data_controller::data_controller() {
	//std::cout << "�f�[�^��ǂݍ���\n";
	//��b�f�[�^�ǂ�
	tmpp = (char*)key;
	readData("../data/foundation/key.csv", tmpp, Kstuck, Kline);
	tmpp = (char*)scaleTKeynote;
	readData("../data/foundation/scale_tmp_keynote.csv", tmpp, Sstuck, Sline);
}

data_controller::~data_controller() {
}


void data_controller::readData(std::string fileName, char* p, int chunkNum, int lineNum) {
	//std::cout << "Debug::readData:" << fileName << "\n";
	//�t�@�C���J��
	fin.open(fileName);
	if (!fin) {
		std::cout << "file open error\n";
		exit(1);
	}

	//�Ȃ�₩��⏈������
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

//string�^���S�Đ������m���߂�Ղ낮���
bool data_controller::checkInt(std::string input) {
	if (std::all_of(input.cbegin(), input.cend(), isdigit)) {
		return true;
	}
	return false;
}

void data_controller::makeScale() {
	//�Ⴄ���@���肻�������ǂ�����Ɩ���
	int tmp = 0, tmp2 = 0, counter = 0;
	char tmpKey[2] = {'X',0};
	char tmpC[2] = {'X',0 };

	tmpKey[0] = key[chordNum][0];//���AchordNum�������Ă�����
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
		std::cout << "�������Ⴂ�܂�\n";
	
	for (int i = 0; i < 7; i++) {
		convNotes[i] = notes[i + heiDiff];
	}

	tmpC[0] = scaleTKeynote[typeofChord][0];
	//�Վ��L���Ƀt���b�g���t�����Ƃ͍l�����Ă��܂���B���󑶍݂��Ȃ�����ˎd���Ȃ���
	if (strcmp(tmpC, "#") == 0) {
		tmp = scaleTKeynote[typeofChord][++counter] - '0';
		for (int j = 0; j < tmp; j++) {
			counter++;
			tmp2 = scaleTKeynote[typeofChord][counter] - '0';
			convNotes[tmp2 - 1] += "#";
		}
	}

	//�f��
	for (int i = 0; i < 7; i++) {
		convNotes[i + 7] = convNotes[i];
	}

	//�ǉ���
	convNotes[14] = convNotes[0];

	std::cout << "res:";
	for (int i = 0; i < 15; i++) {
		std::cout << convNotes[i] << ", ";
	}
	std::cout << '\n';
}



void data_controller::confirmCorrect(int tate, int yoko) {
	for (int i = 0; i < tate; i++) {
		for (int j = 0; j < yoko; j++) {
			std::cout << scaleTKeynote[i][j] << ' ';
		}
		std::cout << '\n';
	}	
}