#include "Individual.h"

Individual::Individual(data_controller* d) {
	//std::cout << "�̍����\n";
	data = d;
	//char doNotUse = d->key[0][0];
	//std::cout << "E���o���琳��:" << data->notes[2] << "\n";
	
	//�̃i���o�[�Ǘ�(Ind[i]��i�ł�����ق��������������ǂȂ񂩕ʂ̂��ƍl���Ă��񂾂�˂��Ԃ�E�E�E)
	data->GproductSum+=0.5;
	productNum = (int)data->GproductSum;
	point = -1;
	//������
	for (int i = 0; i < 128; i++) {
		chrom[i] = "-999";
	}
}

Individual::~Individual() {
}

void Individual::firstTake(int selectNum) {
	//std::cout << "�����̍쐬\n";//makePractice.cpp�ŔC�ӂ̐��ǂ�ł�̂ő��v
	//std::cout << "Debug::selectedNum = " << selectNum << '\n';
	switch (selectNum) {
	case 0:
		//std::cout << "1~20�̏����쐬\n";


		break;
	case 1:
		//std::cout << "�X�P�[���̏����W�c�쐬\n";
		break;
	case 2:
		//std::cout << "�A���y�W�I�̏����W�c�쐬\n";
		break;
	case 3:
		//std::cout << "�I�N�^�[�u�̏����W�c�쐬\n";

		break;
	case 4:
		//std::cout << "�����K�̏����W�c�쐬\n";

		break;
	default:
		std::cout << "�������Ȃ��l\n";
		break;
	}
}