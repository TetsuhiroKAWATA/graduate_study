#include "makePractice.h"

makePractice::makePractice(int selectNum) {
	//std::cout << "�߂����Ղ炭�Ă���\n";
	
	//data_controller�͂����ň��ĂсA�ȍ~��public�̃f�[�^�����|�C���^�Ŏw�肵�ĉ]�X
	Cont = new data_controller();

	//�X�R�[�v�I�ȈӖ��ł߂�ǂ���������V�������
	int selectedNum = selectNum;//���̔ԍ��̗��K��邼

	//�f�[�^����������B�֐��ɂ��Ă��ǂ��������ǂ��̕ӂ�1�񂵂��M��񂵁E�E�E
	switch (selectedNum) {
	case 0:
		Cont->chromLen = 128;

		//�R�[�h�i�s���߂�B8�ȏ�ɂ������Ƃ��͂����M���ƂȂ��
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
		std::cout << "���͂��ꂽ�������Ԉ���Ă��܂��B\n";
		exit(1);
	}
	//�����܂�

	for (int i = 0; i < MusicNum; i++) {
		//std::cout << i << "���\n";
		Ind[i] = new Individual(Cont);
		newInd[i] = new Individual(Cont);

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