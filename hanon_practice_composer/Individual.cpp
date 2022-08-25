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

	int noteNum;//����������
	int tmp, tmp2 = 0;//tmp
	int PT[7];//PT������ꏊ���i�[
	int noteRange[2];//���߂��Ƃ̉������Ƃ����
	std::string tmpS;

	switch (selectNum) {
	case 0:
		std::cout << "1~20�̏����쐬\n";
		std::cout << "productNum = " << productNum << '\n';

		//�����W�c���
		// ������
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			for (int j = 0; j < meloMakeNum; j++) {
				//����
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);

				//���Y��
				//1��T,2��P������悤�ɂȂ��Ă���
				tmp = data->noteNum[1] - noteNum;//PT�̐�
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

				//�n�߂̉����߂�
				tmp = decideNoteNum(0, 2);//�a���̑扽�����n�߂̉��ɗ��p���邩
				tmp2 = data->chordProg[j] - '0';//���݂̏��߂̘a�������x��
				tmp2 += (tmp * 2);//�n�߂̉��̓x��(1�X�^�[�g�B�K�؂ȃ^�C�~���O��0�X�^�[�g�ɕϊ�)
				chrom[j * data->noteNum[1] + (i * 65)] = data->notes[(tmp2-1) % 7];

				if (tmp2 < 8) {
					chrom[j * data->noteNum[1] + i * 65] += "4";
				}
				else if (tmp2 < 16) {
					chrom[j * data->noteNum[1] + i * 65] += "5";
				}
				else {
					std::cout << "�o�O���Ă܂���\n";
					exit(1);
				}

				//���挈��
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
				std::cout << "����:" << noteRange[0] << " �` " << noteRange[1] << '\n';

				//���q���t�F�[�Y

				//���g�m�F
				for (int k = 0; k < 8;k++){
					std::cout << chrom[j * data->noteNum[1] + (i * 65) + k];
				}
				std::cout << '\n';
			}
		}

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

int Individual::decideNoteNum(int lower, int upper) {
	int res = lower + rand() % (upper - lower + 1);
	return res;
}