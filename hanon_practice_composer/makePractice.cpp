#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "�߂����Ղ炭�Ă���\n";
	//������
	toRead = NULL;
	
	//data_controller�͂����ň��ĂсA�ȍ~��public�̃f�[�^�����|�C���^�Ŏw�肵�ĉ]�X
	Cont = new data_controller();

	Cont->selectedNum = selectNum;//���̔ԍ��̗��K��邼

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "���\n";
		Ind[i] = new Individual(Cont);
		newInd[i] = new Individual(Cont);

		//�����W�c�쐬�������ł�����Ⴆ�I
		Ind[i]->firstTake(Cont->selectedNum);
	}
}

makePractice::~makePractice() {
	for (int i = 0; i < MusicNum; i++) {
		delete Ind[i];
		delete newInd[i];
	}

	//delete Cont;->���������̂��H
}

void makePractice::dataPrepare() {
	switch (Cont->selectedNum) {
	case 0:
		Cont->chromLen = 128;

		//�R�[�h�i�s���߂�B
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
		Cont->readData(makePass, toRead, 3, noteHNum);//2:�E��ƍ���@12:�������̂�8�����ǁA�̈�̑傫���������Ȃ��Ƃ����Ȃ����߁A12
		std::cout << "�m�F";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < noteHNum; j++) {

				std::cout << Cont->hanon[i][j];
			}
			std::cout << '\n';
		}

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
		std::cout << "���͂��ꂽ�������Ԉ���Ă��܂��B\n";
		exit(1);
	}
}

void makePractice::printResult() {
	std::cout << "�Ղ��Ƃ肴���\n";
}