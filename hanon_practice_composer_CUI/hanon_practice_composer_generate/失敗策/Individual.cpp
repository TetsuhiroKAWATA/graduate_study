#include "Individual.h"

Individual::Individual(data_controller* d) {
	//std::cout << "�̍����\n";
	data = d;

	point = -1;
	//������
	for (int i = 0; i < 128; i++) {
		chrom[i] = "-999";
	}
}

Individual::~Individual() {
}

void Individual::firstTake(int selectNum) {

	int noteNum;//����������
	int tmp, tmp2 = 0, tmp3;//tmp
	int PT[7];//PT������ꏊ���i�[
	int noteRange[2];//���߂��Ƃ̉������Ƃ����
	std::string tmpS;
	std::string nowChord[3];//���̏��߂̘a��
	int nowChordNum[3];//���߂̘a���̍\������notes[]�̉����ɓ����Ă邩�o������
	std::string randomTable[35];
	std::string randomTableEnd[5];
	int counter;
	int noteHei = 4;//C4��c5����4�C5�̂Ƃ��������

	switch (selectNum) {
	case 0:
		//X������
		for (int i = 1; i <= data->Xceil; i++) {
			randomTable[i - 1] = "X";
			randomTable[i - 1] += std::to_string(i);
		}

		std::cout << "1~20�̏����쐬\n";
		//std::cout << "productNum = " << productNum << '\n';

		//�����W�c���
		// ������
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			for (int j = 0; j < meloMakeNum; j++) {
				//�F�X������
				counter = data->Xceil;
				chrom[j * data->noteNum[1] + (i * 64) + 1] = "-999";

				//std::cout << "nowChordNum = ";
				//�R�[�h�ݒ�A�x���\�L(0����ł͂Ȃ�)
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp+1;
					//std::cout << nowChordNum[k] << ' ';
				}
				//std::cout << '\n';

				//����
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);
				tmp = data->noteNum[1] - noteNum;//PT�̐�
				decidePT(tmp, j * data->noteNum[1] + (i * 64) + 1, j * data->noteNum[1] + (i * 64) + 7);

				//�n�߂̉����߂�
				tmp = decideNoteNum(0, 2);//�a���̑扽�����n�߂̉��ɗ��p���邩
				tmp2 = data->chordProg[j] - '0';//���݂̏��߂̘a�������x��
				tmp2 += (tmp * 2);//�n�߂̉��̓x��(1�X�^�[�g�B�v���O�����͊�{0�n�܂肾���A�x������1�n�܂�)
				chrom[j * data->noteNum[1] + (i * 64)] = data->notes[(tmp2-1) % 7];

				if (tmp2 < 8) {
					chrom[j * data->noteNum[1] + i * 64] += "4";
				}
				else if (tmp2 < 16) {
					chrom[j * data->noteNum[1] + i * 64] += "5";
				}
				else {
					std::cout << "�o�O���Ă܂���\n";
					exit(1);
				}

				//���挈��
				//1�n�܂�̂͂�
				noteRange[0] = data->hanon[2][0] - '0';
				noteRange[1] = data->hanon[2][1] - '0';
				noteRange[0] += nowChordNum[0];
				noteRange[1] += nowChordNum[0];
				noteRange[0]--;
				noteRange[1]--;
				/*�v�ɂȂ����A�����_���Ō��߂�p�^�[��
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
				//std::cout << "����:" << noteRange[0] << " �` " << noteRange[1] << '\n';

				//���q���t�F�[�Y
				tmp = 0;
				for (int k = 1; k < 8; k++) {
					counter -= tmp;
					tmp = 0;
					if (chrom[j * data->noteNum[1] + (i * 64) + k] ==  "-999") {
						//����if�����ŏ���������
						tmpS = chrom[j * data->noteNum[1] + (i * 64) + k - 1].substr(0, 1);//��O�̈�`�q�̍ŏ��̕���
						
						//���O��TP�ȊO�̗v�f��T��
						//tmpS�ɒ��O�̉�(C4�Ƃ�)������K�v�����邽�߁AY�������牺�ŏ������s��
						int X = seekTP(tmpS, j * data->noteNum[1] + (i * 64) + k);
						tmpS = chrom[X].substr(0, 1);

						//Y���������̏���
						if (tmpS == "Y") {
							int l = 1;
							do {
								if (chrom[X - l].substr(0, 1) == "X") {
									tmp2 = stoi(chrom[X - l].substr(1));
									break;
								}
								l++;
							} while (1);
							
							if (1 <= tmp2 && tmp2 <= 7) {
								char tmpC = data->hanon[0][tmp2 - 1 + 1];
								tmp3 = int(tmpC - '0');
							}
							else if (8 <= tmp2 && tmp2 <= 13) {
								char tmpC = data->hanon[0][tmp2 - 7 - 1 + 2];
								tmp3 = int(tmpC - '0');
							}
							else if (14 <= tmp2 && tmp2 <= 20) {
								char tmpC = data->hanon[1][tmp2 - 13 - 1 + 1];
								tmp3 = int(tmpC - '0');
							}
							else if (21 <= tmp2 && tmp2 <= 26) {
								char tmpC = data->hanon[1][tmp2 - 20 - 1 + 2];
								tmp3 = int(tmpC - '0');
							}
							else {
								std::cout << "���O��Y���������̏�������肭�����Ă��܂���\n";
							}
							tmp3 += nowChordNum[0];
							tmp3 -= 1;
							tmpS = data->notes[tmp3 - 1];
							//std::cout << "tmp2 = " << tmp2 << ", tmp3 = " << tmp3 << ", tmpS = " << tmpS << '\n';
						}

						//�R�[�h�̍\�������������̏���
						if (tmpS == nowChord[0]
							|| tmpS == nowChord[1]
							|| tmpS == nowChord[2]) {
							//�a���̍\�����A�����͗אډ�����I��
							//Y���q���鏈�������̒��ł��
							//���𐔎��ɕϊ�
							if (tmpS == nowChord[0]) {
								if (noteRange[0] <= nowChordNum[1] && nowChordNum[1] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[1] - 1];
									tmp++;
									if (nowChordNum[1] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[2] && nowChordNum[2] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[2] - 1];
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
									randomTable[counter++] = data->notes[nowChordNum[0] - 1];
									tmp++;
									if (nowChordNum[0] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[2] && nowChordNum[2] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[2] - 1];
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
									randomTable[counter++] = data->notes[nowChordNum[0] - 1];
									tmp++;
									if (nowChordNum[0] <= 7) {
										randomTable[counter - 1] += "4";
									}
									else {
										randomTable[counter - 1] += "5";
									}
								}
								if (noteRange[0] <= nowChordNum[1] && nowChordNum[1] <= noteRange[1]) {
									randomTable[counter++] = data->notes[nowChordNum[1] - 1];
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

						//�אډ���I��p�e�[�u���ɒǉ�
						//��������R�[�h��������
						//std::cout << "tmpS = " << tmpS << '\n';
						tmp2 = defNoteNum(tmpS, X);

						//���̉�
						if (2 <= tmp2 && tmp2 <= 10 && noteRange[0] <= tmp2-1 && tmp2-1 <= noteRange[1]) {
							randomTable[counter++] = data->notes[tmp2 - 2];
							tmp++;
							if (tmp2-1 < 8)
								randomTable[counter - 1] += "4";
							else
								randomTable[counter - 1] += "5";
						}

						//��̉�
						if (1 <= tmp2 && tmp2 <= 9 && noteRange[0] <= tmp2+1 && tmp2+1 <= noteRange[1]) {
							randomTable[counter++] = data->notes[tmp2];
							tmp++;
							if (tmp2+1 < 8)
								randomTable[counter - 1] += "4";
							else
								randomTable[counter - 1] += "5";
						}

						//�I��œ����
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[j * data->noteNum[1] + (i * 64) + k] = randomTable[tmp2];

						//Y���q���鏈��
						if (randomTable[tmp2].substr(0, 1) == "X") {
							int l = 0;
							do {
								l++;
								if (chrom[j * data->noteNum[1] + (i * 64) + k + l] == "-999") {
									chrom[j * data->noteNum[1] + (i * 64) + k + l] = "Y";
									break;
								}
							} while (1);

							tmp3 = stoi(randomTable[tmp2].substr(1));
							if ((8 <= tmp3 && tmp3 <= 13) || (21 <= tmp3 && tmp3 <= 26)) {
								do {
									l++;
									if (chrom[j * data->noteNum[1] + (i * 64) + k + l] == "-999") {
										chrom[j * data->noteNum[1] + (i * 64) + k + l] = "Y";
										break;
									}
								} while (1);
							}
						}
					}
				}

				//���g�m�F
				/*for (int k = 0; k < 8; k++) {
					std::cout << chrom[j * data->noteNum[1] + (i * 65) + k] << ", ";
				}
				std::cout << "\n\n";*/
			}
			//8.16���ߖڂ��쐬
			//��������
			noteNum = decideNoteNum(data->noteNumEnd[0], data->noteNumEnd[1]);
			//std::cout << "�Ō�̏��߂̉���:" << noteNum << '\n';

			chrom[i * 64 + 56] = "-999";
			chrom[i * 64 + 57] = "-999";

			//�Ō�̉���P��T��
			tmp = decideNoteNum(0, 1);
			if (tmp == 0)
				chrom[i * 64 + 63] = "T";
			else if (tmp == 1)
				chrom[i * 64 + 63] = "P";

			//�c���PT�̈ʒu�����߂�
			tmp = data->beat * 2 - noteNum - 1;//PT�̐�
			decidePT(tmp, i * 64 + 57, i * 64 + 62);

			//�������߂�A�����1�`8
			tmp = noteNum;
			for (int j = 7; j > 0; j--) {
				counter = 0;
				if (chrom[i * 64 + 55 + j] == "-999") {
					if (tmp == noteNum) {
						tmp2 = decideNoteNum(0, 1);
						if (tmp2 == 1)
							chrom[i * 64 + 55 + j] = "c4";
						else
							chrom[i * 64 + 55 + j] = "c5";
						tmp--;
					}
					else {
						//���̉��������H
						tmpS = chrom[i * 64 + 55 + j + 1].substr(0, 1);
						int X = 1;
						do {
							if (tmpS == "T" || tmpS == "P") {
								X++;
								tmpS = chrom[i * 64 + 55 + j + X].substr(0, 1);
							}
							else {
								break;
							}
						} while (1);
						//���𐔎���
						tmp2 = defNoteNum(tmpS, i * 64 + 55 + j + X);
						//std::cout << i * 64+55+j << ":tmpS = " << tmpS << ", tmp2 = " << tmp2 << '\n';

						//�א�
						if (1 <= tmp2 + 1 && tmp2 + 1 <= 8) {
							randomTableEnd[counter++] = data->notes[tmp2];
							if (tmp2 + 1 == 8)
								randomTableEnd[counter - 1] += "5";
							else
								randomTableEnd[counter - 1] += "4";
						}
						if (1 <= tmp2 - 1 && tmp2 - 1 <= 8) {
							randomTableEnd[counter++] = data->notes[tmp2 - 2];
							randomTableEnd[counter - 1] += "4";
						}
						//�\����
						if (tmp2 == 1) {
							randomTableEnd[counter++] = data->notes[2];
							randomTableEnd[counter - 1] += "4";
							randomTableEnd[counter++] = data->notes[4];
							randomTableEnd[counter - 1] += "4";
						}
						else if (tmp2 == 3) {
							randomTableEnd[counter++] = data->notes[0];
							randomTableEnd[counter - 1] += "4";
							randomTableEnd[counter++] = data->notes[4];
							randomTableEnd[counter - 1] += "4";
						}
						else if (tmp2 == 5) {
							randomTableEnd[counter++] = data->notes[0];
							randomTableEnd[counter - 1] += "4";
							randomTableEnd[counter++] = data->notes[2];
							randomTableEnd[counter - 1] += "4";
						}

						//�I��
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[i * 64 + 55 + j] = randomTableEnd[tmp2];
					}
				}
			}
		}

		//printChrom();

		break;
	case 1:
		std::cout << "�X�P�[���̏����W�c�쐬\n";
		//pt������
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			//����
			noteRange[0] = 1;
			noteRange[1] = scaleRange;
			for (int j = 0; j < meloMakeNum; j++) {

				//std::cout << "nowChordNum = ";
				//�R�[�h�ݒ�A�x���\�L(0����ł͂Ȃ�)
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp + 1;
					//std::cout << nowChordNum[k] << ' ';
				}
				//std::cout << '\n';

				//�R�[�h��1�Ȃ�X�ɂȂ�
				if (nowChordNum[0] == 1) {
					chrom[j * data->noteNum[1] + (i * 64)] = "X";
					tmp2 = decideNoteNum(1, 2);
					chrom[j * data->noteNum[1] + (i * 64)] += std::to_string(tmp2);

					//y�ǉ�
					for (int k = 1; k < data->noteNum[1]; k++)
						chrom[j * data->noteNum[1] + (i * 64) + k] = "Y";
					//continue;
					if (tmp2 == 2)
						noteRange[1] = 5;
					else
						noteRange[0] = 5;
				}
				else {//�R�[�h��1�łȂ��Ƃ��̕���
					//�����A���Y��
					noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);
					tmp = data->noteNum[1] - noteNum;
					decidePT(tmp, j* data->noteNum[1] + (i * 64) + 1, j* data->noteNum[1] + (i * 64) + 7);

					//�n�߂̉������߂�
					do {
						tmp = decideNoteNum(0, 2);
						if (noteRange[0] <= nowChordNum[tmp] && nowChordNum[tmp] <= noteRange[1])
							break;
					} while (1);
					chrom[j * data->noteNum[1] + (i * 64)] = data->convNotes[nowChordNum[tmp] - 1];
					if (nowChordNum[tmp] + data->heiDiff > 7)
						chrom[j * data->noteNum[1] + (i * 64)] += "5";
					else
						chrom[j * data->noteNum[1] + (i * 64)] += "4";
					tmpS = chrom[j * data->noteNum[1] + (i * 64)];

					noteRange[0] = 1;
					noteRange[1] = scaleRange;

					//�����q����
					for (int k = 1; k < 8; k++) {
						if (chrom[j * data->noteNum[1] + (i * 64) + k] == "-999") {
							noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
							counter = seekNote(randomTable, tmpS, nowChordNum, noteRange, noteHei);
							tmp = decideNoteNum(0, counter - 1);
							chrom[j * data->noteNum[1] + (i * 64) + k] = randomTable[tmp];
							tmpS = chrom[j * data->noteNum[1] + (i * 64) + k];
						}
					}
				}
			}
			//8���ߖ�
			//���Y��
			noteNum = decideNoteNum(data->noteNumEnd[0], data->noteNumEnd[1]);
			tmp = decideNoteNum(0, 1);
			if (tmp == 0)
				chrom[i * 64 + 63] = "T";
			else if (tmp == 1)
				chrom[i * 64 + 63] = "P";

			tmp = data->beat*2 - noteNum - 1;
			decidePT(tmp, i * 64 + 57, i * 64 + 62);

			//������
			tmp = noteNum;
			for (int j = 7; j > 0; j--) {
				counter = 0;
				if (chrom[i * 64 + 55 + j] == "-999") {
					if (tmp == noteNum) {
						tmp2 = decideNoteNum(0, 1);
						if (tmp2 == 1) {
							chrom[i * 64 + 55 + j] = data->convNotes[0];
							chrom[i * 64 + 55 + j] += "4";
						}
						else {
							chrom[i * 64 + 55 + j] = data->convNotes[7];
							chrom[i * 64 + 55 + j] += "5";
						}
						tmpS = chrom[i * 64 + 55 + j];
						tmp--;
					}
					else {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTableEnd, tmpS, nowChordNum, noteRange, noteHei);

						//�I��
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[i * 64 + 55 + j] = randomTableEnd[tmp2];
						tmpS = chrom[i * 64 + 55 + j];
					}
				}
			}
		}

		//printChrom();

		break;
	case 2:
		//std::cout << "�A���y�W�I�̏����W�c�쐬\n";
		//pt������
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			//����
			noteRange[0] = 1;
			noteRange[1] = arpeRange;
			for (int j = 0; j < meloMakeNum; j++) {

				//std::cout << "nowChordNum = ";
				//�R�[�h�ݒ�A�x���\�L(0����ł͂Ȃ�)
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp + 1;
					//std::cout << nowChordNum[k] << ' ';
				}
				//std::cout << '\n';
				// 
				//�����A���Y��
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);
				tmp = data->noteNum[1] - noteNum;
				decidePT(tmp, j * data->noteNum[1] + (i * 48) + 1, j * data->noteNum[1] + (i * 48) + 5);

				//�n�߂̉������߂�
				do {
					tmp = decideNoteNum(0, 2);
					if (noteRange[0] <= nowChordNum[tmp] && nowChordNum[tmp] <= noteRange[1])
						break;
				} while (1);
				chrom[j * data->noteNum[1] + (i * 48)] = data->convNotes[nowChordNum[tmp] - 1];
				if (nowChordNum[tmp] + data->heiDiff > 7)
					chrom[j * data->noteNum[1] + (i * 48)] += "5";
				else
					chrom[j * data->noteNum[1] + (i * 48)] += "4";
				tmpS = chrom[j * data->noteNum[1] + (i * 48)];

				//�����q����
				for (int k = 1; k < 6; k++) {
					if (chrom[j * data->noteNum[1] + (i * 48) + k] == "-999") {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTable, tmpS, nowChordNum, noteRange, noteHei);
						tmp = decideNoteNum(0, counter - 1);
						chrom[j * data->noteNum[1] + (i * 48) + k] = randomTable[tmp];
						tmpS = chrom[j * data->noteNum[1] + (i * 48) + k];
					}
				}
			}
			//8���ߖ�
			//���Y��
			noteNum = decideNoteNum(data->noteNumEnd[0], data->noteNumEnd[1]);
			tmp = decideNoteNum(0, 1);
			if (tmp == 0)
				chrom[i * 48 + 47] = "T";
			else if (tmp == 1)
				chrom[i * 48 + 47] = "P";

			tmp = data->beat * 2 - noteNum - 1;
			decidePT(tmp, i * 48 + 43, i * 48 + 46);

			//������
			tmp = noteNum;
			for (int j = 5; j > 0; j--) {
				counter = 0;
				if (chrom[i * 48 + 41 + j] == "-999") {
					if (tmp == noteNum) {
						tmp2 = decideNoteNum(0, 1);
						if (tmp2 == 1) {
							chrom[i * 48 + 41 + j] = data->convNotes[0];
							chrom[i * 48 + 41 + j] += "4";
						}
						else {
							chrom[i * 48 + 41 + j] = data->convNotes[7];
							chrom[i * 48 + 41 + j] += "5";
						}
						tmpS = chrom[i * 48 + 41 + j];
						tmp--;
					}
					else {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTableEnd, tmpS, nowChordNum, noteRange, noteHei);

						//�I��
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[i * 48 + 41 + j] = randomTableEnd[tmp2];
						tmpS = chrom[i * 48 + 41 + j];
					}
				}
			}
		}
		break;
	case 3:
		//std::cout << "�I�N�^�[�u�̏����W�c�쐬\n";
		//pt������
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			//����
			noteRange[0] = 1;
			noteRange[1] = octRange;
			for (int j = 0; j < meloMakeNum; j++) {

				//std::cout << "nowChordNum = ";
				//�R�[�h�ݒ�A�x���\�L(0����ł͂Ȃ�)
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp + 1;
					//std::cout << nowChordNum[k] << ' ';
				}
				//std::cout << '\n';
				// 
				//�����A���Y��
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);
				tmp = data->noteNum[1] - noteNum;
				decidePT(tmp, j * data->noteNum[1] + (i * 64) + 1, j * data->noteNum[1] + (i * 64) + 7);

				//�n�߂̉������߂�
				do {
					tmp = decideNoteNum(0, 2);
					if (noteRange[0] <= nowChordNum[tmp] && nowChordNum[tmp] <= noteRange[1])
						break;
				} while (1);
				chrom[j * data->noteNum[1] + (i * 64)] = data->convNotes[nowChordNum[tmp] - 1];
				if (nowChordNum[tmp] + data->heiDiff > 7)
					chrom[j * data->noteNum[1] + (i * 64)] += "5";
				else
						chrom[j * data->noteNum[1] + (i * 64)] += "4";
				tmpS = chrom[j * data->noteNum[1] + (i * 64)];

				//�����q����
				for (int k = 1; k < 8; k++) {
					if (chrom[j * data->noteNum[1] + (i * 64) + k] == "-999") {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTable, tmpS, nowChordNum, noteRange, noteHei);
						tmp = decideNoteNum(0, counter - 1);
						chrom[j * data->noteNum[1] + (i * 64) + k] = randomTable[tmp];
						tmpS = chrom[j * data->noteNum[1] + (i * 64) + k];
					}
				}
			}
			//8���ߖ�
			//���Y��
			noteNum = decideNoteNum(data->noteNumEnd[0], data->noteNumEnd[1]);
			tmp = decideNoteNum(0, 1);
			if (tmp == 0)
				chrom[i * 64 + 63] = "T";
			else if (tmp == 1)
				chrom[i * 64 + 63] = "P";

			tmp = data->beat * 2 - noteNum - 1;
			decidePT(tmp, i * 64 + 57, i * 64 + 62);

			//������
			tmp = noteNum;
			for (int j = 7; j > 0; j--) {
				counter = 0;
				if (chrom[i * 64 + 55 + j] == "-999") {
					if (tmp == noteNum) {
						tmp2 = decideNoteNum(0, 1);
						if (tmp2 == 1) {
							chrom[i * 64 + 55 + j] = data->convNotes[0];
							chrom[i * 64 + 55 + j] += "4";
						}
						else {
							chrom[i * 64 + 55 + j] = data->convNotes[7];
							chrom[i * 64 + 55 + j] += "5";
						}
						tmpS = chrom[i * 64 + 55 + j];
						tmp--;
					}
					else {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTableEnd, tmpS, nowChordNum, noteRange, noteHei);

						//�I��
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[i * 64 + 55 + j] = randomTableEnd[tmp2];
						tmpS = chrom[i * 64 + 55 + j];
					}
				}
			}
		}
		break;
	case 4:
		//std::cout << "�����K�̏����W�c�쐬\n";
		for (int k = 0; k < 7; k++) {
			PT[k] = -999;
		}

		for (int i = 0; i < meloMakeRep; i++) {
			//����
			noteRange[0] = 1;
			noteRange[1] = chroRange;
			for (int j = 0; j < meloMakeNum; j++) {

				//std::cout << "nowChordNum = ";
				//�R�[�h�ݒ�A�x���\�L(0����ł͂Ȃ�)
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp + 1;
					//std::cout << nowChordNum[k] << ' ';
				}
				//std::cout << '\n';

				//�R�[�h��1�Ȃ�X�ɂȂ�
				if (nowChordNum[0] == 1) {
					chrom[j * data->noteNum[1] + (i * 48)] = "X";
					tmp2 = decideNoteNum(1, 2);
					chrom[j * data->noteNum[1] + (i * 48)] += std::to_string(tmp2);

					//y�ǉ�
					for (int k = 1; k < data->noteNum[1]; k++)
						chrom[j * data->noteNum[1] + (i * 48) + k] = "Y";
					continue;
				}
				else {//�R�[�h��1�łȂ��Ƃ��̕���
					//�����A���Y��
					noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);
					tmp = data->noteNum[1] - noteNum;
					decidePT(tmp, j * data->noteNum[1] + (i * 48) + 1, j * data->noteNum[1] + (i * 48) + 5);

					//�n�߂̉������߂�
					//std::cout << chrom[j * data->noteNum[1] + (i * 48) - 1];
					if (chrom[j * data->noteNum[1] + (i * 48) - 1] == "Y") {
						chrom[j * data->noteNum[1] + (i * 48)] = data->convNotes[-1 + (data->hanon[0][0] - '0')];
						if (chrom[j * data->noteNum[1] + (i * 48) - 6] == "X1") {
							chrom[j * data->noteNum[1] + (i * 48)] += "5";
						}
						else {
							chrom[j * data->noteNum[1] + (i * 48)] += "4";
						}
					}
					else {
						do {
							tmp = decideNoteNum(0, 2);
							if (noteRange[0] <= nowChordNum[tmp] && nowChordNum[tmp] <= noteRange[1])
								break;
						} while (1);
						chrom[j * data->noteNum[1] + (i * 48)] = data->convNotes[nowChordNum[tmp] - 1];
						if (nowChordNum[tmp] + data->heiDiff > 7)
							chrom[j * data->noteNum[1] + (i * 48)] += "5";
						else
							chrom[j * data->noteNum[1] + (i * 48)] += "4";
					}
					tmpS = chrom[j * data->noteNum[1] + (i * 48)];

					//�����q����
					for (int k = 1; k < 6; k++) {
						if (chrom[j * data->noteNum[1] + (i * 48) + k] == "-999") {
							noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
							counter = seekNote(randomTable, tmpS, nowChordNum, noteRange, noteHei);
							tmp = decideNoteNum(0, counter - 1);
							chrom[j * data->noteNum[1] + (i * 48) + k] = randomTable[tmp];
							tmpS = chrom[j * data->noteNum[1] + (i * 48) + k];
						}
					}
				}
			}
			//8���ߖ�
			//���Y��
			noteNum = decideNoteNum(data->noteNumEnd[0], data->noteNumEnd[1]);
			tmp = decideNoteNum(0, 1);
			if (tmp == 0)
				chrom[i * 48 + 47] = "T";
			else if (tmp == 1)
				chrom[i * 48 + 47] = "P";

			tmp = data->beat * 2 - noteNum - 1;
			decidePT(tmp, i * 48 + 43, i * 48 + 46);

			//������
			tmp = noteNum;
			for (int j = 5; j > 0; j--) {
				counter = 0;
				if (chrom[i * 48 + 41 + j] == "-999") {
					if (tmp == noteNum) {
						tmp2 = decideNoteNum(0, 1);
						if (tmp2 == 1) {
							chrom[i * 48 + 41 + j] = data->convNotes[0];
							chrom[i * 48 + 41 + j] += "4";
						}
						else {
							chrom[i * 48 + 41 + j] = data->convNotes[7];
							chrom[i * 48 + 41 + j] += "5";
						}
						tmpS = chrom[i * 48 + 41 + j];
						tmp--;
					}
					else {
						noteHei = std::stoi(tmpS.substr(tmpS.length() - 1));
						counter = seekNote(randomTableEnd, tmpS, nowChordNum, noteRange, noteHei);

						//�I��
						tmp2 = decideNoteNum(0, counter - 1);
						chrom[i * 48 + 41 + j] = randomTableEnd[tmp2];
						tmpS = chrom[i * 48 + 41 + j];
					}
				}
			}
		}

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

//�n���������扽�����Ԃ��֐�,char�ɂ��Ή����Ă��邯��1~20�ł����g���Ă˂�
int Individual::defNoteNum(std::string tmpS, int num) {
	int tmp = 0;

	if (tmpS == "c")
		tmp = 1;
	else if (tmpS == "d")
		tmp = 2;
	else if (tmpS == "e")
		tmp = 3;
	else if (tmpS == "f")
		tmp = 4;
	else if (tmpS == "g")
		tmp = 5;
	else if (tmpS == "a")
		tmp = 6;
	else if (tmpS == "b")
		tmp = 7;
	else
		std::cout << "�v�f���s���ł��B\n";

	if (chrom[num].substr(0, 1) != "Y"
		&& chrom[num].substr(1, 1) == "5") {
		tmp += 7;
	}

	return tmp;
}

//���O��TP�ȊO�̗v�f�̓Y������Ԃ��֐�
int Individual::seekTP(std::string tmpS, int num) {
	int X = 1;
	do {
		if (tmpS == "T" || tmpS == "P") {
			X++;
			tmpS = chrom[num - X].substr(0, 1);
		}
		else {
			break;
		}
	} while (1);

	return num - X;
}

int Individual::seekNote(std::string* randomTable, std::string tmpS, int* nowChordNum, int* noteRange, int noteHei) {
	int tmp = -999;
	int counter = 0;

	//tmpS��c#4�Ƃ��̉��������Ă��āA����̗אڂ����߂�
	//noteHei��C#4�Ƃ���4�̕����������Ă���͂�
	//1.���̉��������ڂ����߂�
	for (int i = 0; i < 7; i++) {
		if (tmpS.substr(0,tmpS.length()-1) == data->convNotes[i]) {
			tmp = i + 1;
			break;
		}
	}

	//std::cout << "tmp = " << tmp << '\n';

	//2.�a���̍\�������ۂ�(nowChordNum�ɉ���𒴉߂���(�����8�܂łȂ̂ɑ��オ����Ƃ�)�͍l������Ă��Ȃ�)
	if (tmp == nowChordNum[0] || tmp + 7 == nowChordNum[0]) {//����
		randomTable[counter] = data->convNotes[nowChordNum[1] - 1];
		if (nowChordNum[1] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[1] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";

		randomTable[counter] = data->convNotes[nowChordNum[2] - 1];
		if (nowChordNum[2] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[2] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";
	}
	else if (tmp == nowChordNum[1] || tmp + 7 == nowChordNum[1]) {//��3��
		randomTable[counter] = data->convNotes[nowChordNum[0] - 1];
		if (nowChordNum[0] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[0] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";

		randomTable[counter] = data->convNotes[nowChordNum[2] - 1];
		if (nowChordNum[2] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[2] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";
	}
	else if (tmp == nowChordNum[2] || tmp + 7 == nowChordNum[2]) {//��5��
		randomTable[counter] = data->convNotes[nowChordNum[1] - 1];
		if (nowChordNum[1] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[1] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";

		randomTable[counter] = data->convNotes[nowChordNum[0] - 1];
		if (nowChordNum[0] + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (nowChordNum[0] + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";
	}

	//tmp�̏���(1~7��1~10��)
	if (data->heiDiff <= 4) {//C~G
		if (noteHei == 5 && tmp + data->heiDiff < 8)
			tmp += 7;
	}
	else {//A,B
		if (noteHei == 6)
			tmp += 7;
		else if (noteHei == 5 && tmp + data->heiDiff < 8)
			tmp += 7;
	}

	//�אډ�(��)
	if (tmp - 1 >= noteRange[0] && tmp - 1 <= noteRange[1]) {
		randomTable[counter] = data->convNotes[tmp - 1 - 1];

		if (tmp - 1 + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (tmp - 1 + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";
	}

	//�אډ�(��)
	if (tmp + 1 >= noteRange[0] && tmp + 1 <= noteRange[1]) {
		randomTable[counter] = data->convNotes[tmp];
		
		if (tmp + 1 + data->heiDiff >= 15)
			randomTable[counter++] += "6";
		else if (tmp + 1 + data->heiDiff >= 8)
			randomTable[counter++] += "5";
		else
			randomTable[counter++] += "4";
	}
	return counter;
}

void Individual::decidePT(int PTnum, int range1, int range2) {
	int PT[7];

	//���Y��
	for (int k = 0; k < PTnum; k++) {
		do {
			int l;
			PT[k] = decideNoteNum(range1, range2);
			for (l = 0; l < k; l++) {
				if (PT[l] == PT[k])
					break;
			}
			if (l == k)
				break;
		} while (1);
	}

	//TP����
	for (int k = 0; k < PTnum; k++) {
		if (decideNoteNum(1, restProb) == 1)
			chrom[PT[k]] = "P";
		else
			chrom[PT[k]] = "T";
	}
}

void Individual::printResult(int Num) {
	//�������Ɉ�`�q�̒��g���o��
	//chromX.csv�����A���̊y�Ȋ֘A�t�@�C���ƈ����0�n�܂�(��������ł�������ł����ǂˁE�E�E�B)
	std::string path = "../chrom/chrom";
	std::ofstream fout;
	path += std::to_string(Num);
	path += ".csv";

	std::cout << path << '\n';

	fout.open(path);
	if (!fout)
		std::cout << "�t�@�C���I�[�v���G���[\n";

	for (int i = 0; i < data->chromLen; i++) {
		fout << chrom[i] << ',';
	}
	fout << '\n';
	fout.close();
}

void Individual::printChrom() {

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << i * 8 + j << "= " << chrom[i * 8 + j] << ", ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

}