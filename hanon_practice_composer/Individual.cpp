#include "Individual.h"

Individual::Individual(data_controller* d) {
	//std::cout << "�̍����\n";
	data = d;
	//char doNotUse = d->key[0][0];
	//std::cout << "E���o���琳��:" << data->notes[2] << "\n";
	
	//�̃i���o�[�Ǘ�(Ind[i]��i�ł�����ق��������������ǂȂ񂩕ʂ̂��ƍl���Ă��񂾂�˂��Ԃ�E�E�E)
	//data->GproductSum+=0.5;
	//productNum = (int)data->GproductSum;
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

	//X������
	for (int i = 1; i <= data->Xceil; i++) {
		randomTable[i-1] = "X";
		randomTable[i-1] += std::to_string(i);
	}

	switch (selectNum) {
	case 0:
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
				//�R�[�h�ݒ�
				for (int k = 0; k < 3; k++) {
					tmp = (data->chord[k] - '0') + (data->chordProg[j] - '0') - 2;
					nowChord[k] = data->notes[tmp];
					nowChordNum[k] = tmp+1;
				}

				//����
				noteNum = decideNoteNum(data->noteNum[0], data->noteNum[1]);

				//���Y��
				tmp = data->noteNum[1] - noteNum;//PT�̐�
				for (int k = 0; k < tmp; k++) {
					do {
						int l;
						PT[k] = decideNoteNum(j * data->noteNum[1] + (i * 64) + 1, j * data->noteNum[1] + (i * 64) + 7);
						for (l = 0; l < k; l++) {
							if (PT[l] == PT[k])
								break;
						}
						if(l == k)
							break;
					} while (1);
				}

				//TP����
				for (int k = 0; k < tmp; k++) {
					if (decideNoteNum(1, restProb) == 1)
						chrom[PT[k]] = "P";
					else
						chrom[PT[k]] = "T";
				}

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
			for (int j = 0; j < tmp; j++) {
				do {
					int k;
					PT[j] = decideNoteNum(i * 64 + 57, i* 64 + 62);
					for (k = 0; k < j; k++) {
						if (PT[j] == PT[k])
							break;
					}
					if (j == k)
						break;
				} while (1);
			}

			//���߂��ʒu�ɓ����
			for (int j = 0; j < tmp; j++) {
				if (decideNoteNum(1, restProb) == 1)
					chrom[PT[j]] = "P";
				else
					chrom[PT[j]] = "T";
			}

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

//�n���������扽�����Ԃ��֐�
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

void Individual::cross(Individual* p1, Individual* p2) {
	int X = 0, counter = 0;

	for (int i = 0; i < crossNum; i++) {
		points[i] = decideNoteNum(0, data->chromLen - 1);
	}
	//���ёւ�
	//����������2��I�΂�邱�Ƃ����邯�ǁA�܂��A����͂���Ƃ������Ƃ�
	sort(0, crossNum - 1);

	//�V����a���̏u��
	for (int i = 0; i < data->chromLen; i++) {
		if (i == points[counter]) {
			X = X * (-1) + 1;
			counter++;
		}

		if (X == 0) {
			chrom[i] = p1->chrom[i];
		}
		else if (X == 1) {
			chrom[i] = p2->chrom[i];
		}
		else {
			std::cout << "�v�Z���Ԉ���Ă��܂�";
			exit(1);
		}
	}
}

void Individual::sort(int lb, int ub) {
	int i, j, k;
	double pivot;
	int tmp;

	if (lb < ub) {
		k = (lb + ub) / 2;
		pivot = points[k];
		i = lb;
		j = ub;

		do {
			while (points[i] < pivot)
				i++;
			while (points[j] > pivot)
				j--;
			if (i <= j) {
				tmp = points[i];
				points[i] = points[j];
				points[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

void Individual::printResult() {
	std::string fileName = "../result/music";
	fileName += ".mml";
	print(fileName);
}

void Individual::printMusic(int Num){
	std::string fileName = "../music/music";
	fileName += std::to_string(Num + 1);
	fileName += ".mml";
	print(fileName);
}

void Individual::print(std::string fileName) {
	std::ofstream fout;

	printChrom();

	fout.open(fileName, std::ios_base::trunc);
	if (!fout) {
		std::cout << "file open Error\n";
	}

	//�S�̂̃f�[�^
	fout << "Include(stdmsg.h)\n";
	fout << "System.MeasureShift(1)\n";
	fout << "Copyright = { \"Tetsuhiro KAWATA\" }\n";
	fout << "TrackName = { \"music\" }\n\n";

	fout << "Time(0:1:0)\nResetXG();ResetGS();ResetGM();\n\n";

	fout << "TimeSignature(" << data->beat << ",4)\n";
	fout << "Tempo(" << data->tempo << ")\n";

	//�E��
	fout << "Track(1)\n";
	fout << "Channel(1)\n";
	fout << "Time(1:1:0)\nVoice(1)\n\n";

	fout << "l8o4v150\n";

//	fout.close();

	//�{��
	//�E��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			//2���߂��Ƃɏo��(2���߂��Ƃɉ��s���悤�Ƃ��Ă����̖��c)
			printMelody(fileName, i, j,fout);
		}
	}

	fout << "\no5v80\n";

	//���t
	for (int i = 0; i < 8; i++) {
		printAccom(fileName, i, fout);
		fout << '\n';
	}

	//����
	fout << "\nTrack(2)\n";
	fout << "Channel(2)\n";
	fout << "Time(1:1:0)\nVoice(1)\n\n";

	fout << "l8o3v80\n";

	//���t
	for (int i = 0; i < 8; i++) {
		//���߂���
		printAccom(fileName, i, fout);
		fout << '\n';
	}
	fout << "\nv150\n";

	//����
	for (int i = 4; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			printMelody(fileName, i, j,fout);
		}
	}

	fout.close();
}

void Individual::printMelody(std::string fileName, int i, int j, std::ofstream& fout) {//&�ŎQ�ƁA�Ƃ������Ă���炵���B���ׂ���
	int tmp2, tmp3, tmp4;
	int nowChordinP;
	std::string recentX[2];//���O��X
	std::string tmp;
	std::string recentC = "x";//���O�̉�
	int recentCount = 0;//X�̂ǂ̗v�f���g���Ă��邩�B

	tmp2 = i * 2 + j;
	nowChordinP = data->chordProg[tmp2] - '0';
	nowChordinP--;

	tmp2 = j * data->noteNum[1] + i * data->noteNum[1] * 2;//2���߂̍ŏ��̗v�f�̓Y����

	tmp4 = data->hanon[0][0] - '0';
	tmp4 += nowChordinP;
	recentX[0] = data->notes[tmp4 - 1];
	tmp4 = data->hanon[0][1] - '0';
	tmp4 += nowChordinP;
	recentX[1] = data->notes[tmp4 - 1];

	for (int k = 0; k < data->noteNum[1]; k++) {

		//�o�͂���v�f�̒��o
		if (chrom[k + tmp2].substr(1, 1) == "#") {//�V���[�v�����Ă�ꍇ
			tmp = chrom[k + tmp2].substr(0, 2);

			if (chrom[k + tmp2].substr(2, 1) == "5") {
				fout << ">";
				fout << tmp;
				fout << "<";
				recentC = ">" + tmp + "<";
			}
			else {
				fout << tmp;
				recentC = tmp;
			}
		}
		else if (chrom[k + tmp2].substr(0, 1) == "X") {//X�̏ꍇ
			tmp = chrom[k + tmp2];
			tmp3 = std::stoi(tmp.substr(1));//X�ɂ��Ă�ԍ�(X1��1,X20��20)

			if (data->selectedNum == 4) {
				//�����K��X���o������������
			}
			else if (data->selectedNum == 0) {
				//1~20�̏ꍇ�A�g���܂킵���ցI
				if (1 <= tmp3 && tmp3 <= 7) {
					tmp4 = data->hanon[0][tmp3 - 1] - '0';//�n�m���̉��Ԗڂ����߂�
					tmp4 += nowChordinP;//�R�[�h��������
					tmp = data->notes[tmp4 - 1];

					recentCount = 1;

					if (tmp4 >= 8) {
						fout << ">" << tmp << "<";
						recentX[0] = ">" + tmp + "<";
					}
					else {
						fout << tmp;
						recentX[0] = tmp;
					}

					tmp4 = data->hanon[0][tmp3] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[1] = ">" + tmp + "<";
					}
					else
						recentX[1] = tmp;
				}
				else if (8 <= tmp3 && tmp3 <= 13) {
					tmp4 = data->hanon[0][tmp3 - 1 - 7] - '0';//�n�m���̉��Ԗڂ����߂�
					tmp4 += nowChordinP;//�R�[�h��������
					tmp = data->notes[tmp4 - 1];

					recentCount = 0;

					if (tmp4 >= 8) {
						fout << ">" << tmp << "<";
					}
					else {
						fout << tmp;
					}

					//Y�̏���
					tmp4 = data->hanon[0][tmp3 - 7] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[0] = ">" + tmp + "<";
					}
					else
						recentX[0] = tmp;

					tmp4 = data->hanon[0][tmp3 - 7 + 1] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[1] = ">" + tmp + "<";
					}
					else
						recentX[1] = tmp;
				}
				else if (14 <= tmp3 && tmp3 <= 20) {
					tmp4 = data->hanon[1][tmp3 - 1 - 13] - '0';//�n�m���̉��Ԗڂ����߂�
					tmp4 += nowChordinP;//�R�[�h��������
					tmp = data->notes[tmp4 - 1];

					recentCount = 1;

					if (tmp4 >= 8) {
						fout << ">" << tmp << "<";
						recentX[0] = ">" + tmp + "<";
					}
					else {
						fout << tmp;
						recentX[0] = tmp;
					}

					tmp4 = data->hanon[1][tmp3 - 13] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[1] = ">" + tmp + "<";
					}
					else
						recentX[1] = tmp;
				}
				else if (21 <= tmp3 && tmp3 <= 26) {
					tmp4 = data->hanon[1][tmp3 - 1 - 20] - '0';//�n�m���̉��Ԗڂ����߂�
					tmp4 += nowChordinP;//�R�[�h��������
					tmp = data->notes[tmp4 - 1];

					recentCount = 0;

					if (tmp4 >= 8) {
						fout << ">" << tmp << "<";
						recentX[0] = ">" + tmp + "<";
					}
					else {
						fout << tmp;
						recentX[0] = tmp;
					}

					tmp4 = data->hanon[1][tmp3 - 20] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[0] = ">" + tmp + "<";
					}
					else
						recentX[0] = tmp;

					tmp4 = data->hanon[1][tmp3 - 20 + 1] - '0';
					tmp4 += nowChordinP;
					tmp = data->notes[tmp4 - 1];
					if (tmp4 >= 8) {
						recentX[1] = ">" + tmp + "<";
					}
					else
						recentX[1] = tmp;
				}
			}
			else {
				//�X�P�[��
			}
		}
		else {//�V���[�v�����ĂȂ��ꍇ�A�܂���T,P,Y�̏ꍇ
			tmp = chrom[k + tmp2].substr(0, 1);

			if (tmp == "T") {
				if (chrom[k + tmp2 - 1] != "P")
					fout << "^";
				else
					fout << recentC;
			}
			else if (tmp == "P") {
				fout << "r";
			}
			else if (tmp == "Y") {
				fout << recentX[recentCount];
				recentCount = recentCount * (-1) + 1;
			}
			else {
				if (chrom[k + tmp2].substr(1, 1) == "5") {
					fout << ">";
					fout << tmp;
					fout << "<";
					recentC = ">" + tmp + "<";
				}
				else {
					fout << tmp;
					recentC = tmp;
				}
			}
		}

	}
	fout << "\n";
}

void Individual::printAccom(std::string fileName, int i, std::ofstream& fout) {
	std::string tmp = "";
	int nowChordinP;

	nowChordinP = data->chordProg[i] - '0';
	nowChordinP--;

	//�x����ԍ��ɕϊ�
	if (nowChordinP == 3)
		nowChordinP = 1;
	else if (nowChordinP == 4)
		nowChordinP = 2;

	for (int i = 0; i < data->accNoteNum; i++) {
		tmp = data->notes[data->accompany[nowChordinP][i] - '0' - 1];
		fout << tmp << "^";
	}
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