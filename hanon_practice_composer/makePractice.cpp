#include "makePractice.h"

makePractice::makePractice() {
	std::cout << "��b���K(1�`20)�̗��K������B\n";
	
	//data_controller�͂����ň��ĂсA�ȍ~��public�̃f�[�^�����|�C���^�Ŏw�肵�ĉ]�X
	Cont = new data_controller();

	for (int i = 0; i < MusicNum; i++) {
		Ind[i] = new Individual();
	}
}

makePractice::~makePractice() {

}

void makePractice::printResult() {
	std::cout << "�Ղ��Ƃ肴���\n";
}