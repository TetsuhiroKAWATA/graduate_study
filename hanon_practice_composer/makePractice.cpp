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
		Cont->readData("../data/fingertrain/chordProg.csv", toRead, 1, barNum*2);

		//����
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;//1�̗\�肾�������Ǔs����2�ɕύX
		Cont->noteNumEnd[1] = 6;

		//���q
		Cont->beat = 4;

		//����̌`
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/fingertrain/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		//�n�m���̐����ǂݍ���
		toRead = (char*)(Cont->hanon);
		makePass = "../data/fingertrain/practice_" + std::to_string(Cont->hanonNum);
		makePass += ".csv";
		Cont->readData(makePass, toRead, 3, noteHNum);//3:���A����A����@12:�������̂�8�����ǁA�̈�̑傫���������Ȃ��Ƃ����Ȃ����߁A12
		
		//X�͈͎̔w��
		Cont->Xceil = 26;

		break;
	case 1:
		Cont->chromLen = 128;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/scale/chordProg.csv", toRead, 1, barNum * 2);

		//����
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//���q
		Cont->beat = 4;

		//����
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/scale/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		//�n�m���ǂݍ���(�X�P�[��������)
		toRead = (char*)(Cont->hanon);
		Cont->readData("../data/scale/hanon.csv", toRead, 3, noteHNum);

		Cont->Xceil = 2;

		break;
	case 2:
		//�A���y�W�I
		Cont->chromLen = 96;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/arpeggio/chordProg.csv", toRead, 1, barNum * 2);

		//����
		Cont->noteNum[0] = 3;
		Cont->noteNum[1] = 6;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		Cont->beat = 3;

		//����(�A���y�W�I)
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/arpeggio/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 6;

		Cont->Xceil = 0;
		Cont->tempo = 120;

		break;
	case 3:
		//�I�N�^�[�u
		Cont->chromLen = 128;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/octave/chordProg.csv", toRead, 1, barNum * 2);

		//����
		Cont->noteNum[0] = 4;
		Cont->noteNum[1] = 8;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//���q
		Cont->beat = 4;

		//����
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/octave/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 4;

		Cont->Xceil = 0;
		Cont->tempo = 120;

		break;
	case 4:
		Cont->chromLen = 96;

		toRead = (char*)(Cont->chordProg);
		Cont->readData("../data/chromaticscale/chordProg.csv", toRead, 1, barNum * 2);

		//����
		Cont->noteNum[0] = 3;
		Cont->noteNum[1] = 6;
		Cont->noteNumEnd[0] = 2;
		Cont->noteNumEnd[1] = 6;

		//���q
		Cont->beat = 3;

		//����
		toRead = (char*)(Cont->accompany);
		Cont->readData("../data/chromaticscale/accompany.csv", toRead, chordKinds, leftMax);
		Cont->accNoteNum = 3;

		toRead = (char*)(Cont->hanon);
		Cont->readData("../data/chromaticscale/hanon.csv", toRead, 3, noteHNum);

		Cont->tempo /= 2;
		Cont->Xceil = 2;
		break;
	default:
		std::cout << "���͂��ꂽ�������Ԉ���Ă��܂��B\n";
		exit(1);
	}
}

void makePractice::firstTake() {
	for (int i = 0; i < MusicNum; i++) {
		Ind[i]->firstTake(Cont->selectedNum);
	}
}

void makePractice::sort(int lb, int ub) {
	int i, j, k;
	double pivot;
	Individual* tmp;

	if (lb < ub) {
		k = (lb + ub) / 2;
		pivot = Ind[k]->point;
		i = lb;
		j = ub;

		do {
			while (Ind[i]->point < pivot)
				i++;
			while (Ind[j]->point > pivot)
				j--;
			if (i <= j) {
				tmp = Ind[i];
				Ind[i] = Ind[j];
				Ind[j] = tmp;
				i++;
				j--;
			}
		} while (i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}

void makePractice::alternate() {
	Individual* tmp;
	int p1, p2;//���e
	int pointSum = 0, Sum = 0;//�_���̍��v�A���v��ۑ����Ă����ꏊ

	//�_�������v
	for (int i = 0; i < MusicNum; i++)
		Sum += Ind[i]->point;

	//�e�̂�I���A����
	for (int i = 0; i < MusicNum; i++) {
		pointSum = Sum;
		//�e1
		p1 = select(pointSum, -1);

		//�e2
		pointSum -= Ind[p1]->point;
		p2 = select(pointSum, p1);
		//std::cout << i << "��ڐe" << p1 << ", " << p2 << '\n';

		//����������
		newInd[i]->cross(Ind[p1], Ind[p2]);
	}


	//������
	for (int i = 0; i < MusicNum; i++) {
		tmp = Ind[i];
		Ind[i] = newInd[i];
		newInd[i] = tmp;
	}

	//�ˑR�ψ�
	for (int i = 0; i < MusicNum; i++) {
		Ind[i]->mutate();
	}

	//�\��
	/*for (int i = 0; i < MusicNum; i++) {
		std::cout << i + 1 << "�Ȗ�\n";
		Ind[i]->printChrom();
	}*/
}

void makePractice::printResult(int Num) {
	std::cout << "�Ղ��Ƃ肴���:" << Num << "\n";
	Ind[Num]->printResult();
}

void makePractice::printMusic(int Num) {
	Ind[Num]->printMusic(Num);
}

int makePractice::select(int pointSum, int p1Num) {
	double prob, r;//prob:�I�΂��m��������ꏊ�@r:0�ȏ�1�ȉ��̎��������������B
	int res = 0;

	r = ((double)rand() / RAND_MAX);

	for (int j = 0; j < MusicNum; j++) {
		prob = Ind[j]->point / (double)pointSum;
		if (j != p1Num && r <= prob) {
			res = j;
			break;
		}
		r -= prob;
	}

	return res;
}