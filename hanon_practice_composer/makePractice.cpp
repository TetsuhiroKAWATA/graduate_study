#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	std::cout << "�߂����Ղ炭�Ă���\n";
	
	//data_controller�͂����ň��ĂсA�ȍ~��public�̃f�[�^�����|�C���^�Ŏw�肵�ĉ]�X
	Cont = new data_controller();

	//�X�R�[�v�I�ȈӖ��ł߂�ǂ���������V�������
	int selectedNum = selectNum;//���̔ԍ��̗��K��邼

	//�������肷��(data_controller�����Œ�`����̂�߂��ق����ǂ������E�E�E)
	if (selectedNum == 0 || selectedNum == 3 || selectedNum == 4) {
		musicChord = 'C';
		std::cout << "�y�Ȃ̒��́A" << musicChord << "dur �ł��B\n";
	}
	else if (selectedNum == 1) {
		std::cout << "�y�Ȃ̒����ςł��B\n�C�ӂ̒����ȉ�����I�����Ă��������B\n";
	}
	else if (selectedNum == 2) {
		std::cout << "�y�Ȃ̒����ςł��B\n�C�ӂ̒����ȉ�����I�����Ă��������B\n";
	}
	else {
		std::cout << "�ԍ��I�����Ԉ���Ă��܂��B\n";
		exit(1);
	}

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "���\n";
		Ind[i] = new Individual();
		newInd[i] = new Individual();

		//�����W�c�쐬�������ł�����Ⴆ�I
		Ind[i]->firstTake(selectedNum);
	}
}

makePractice::~makePractice() {
	for (int i = 0; i < MusicNum; i++) {
		delete Ind[i];
		delete newInd[i];
	}

	//delete Cont;->���������̂��H
}

void makePractice::printResult() {
	std::cout << "�Ղ��Ƃ肴���\n";
}