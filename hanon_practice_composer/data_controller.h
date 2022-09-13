#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

//Individual��print�֐��ł͌��\�萔���g���Ă���̂Ń����f�B�쐬���Ƃ��ς������͂�����ւ���ύX���K�v

//�萔(�|�C���^�Ŏ����Ȃ��Ă��g�����ق����ǂ����)
//�������ɕϐ��͒u���Ȃ��B�S��const������
const int Lega = 3;//�Œ��̒���(���������)
const int Stac = 1;//�ŒZ�̒P��(���������)
const int meloMakeNum = 7;//�����f�B�쐬�����v
const int meloMakeFrag = 2;//��x�ɍ쐬���郁���f�B(���ߐ�)
const int meloMakeRep = 2;//�����f�B�쐬�J��Ԃ���(�E��ƍ����2�̈Ӗ��B��{�I�ɕς��Ȃ��Ǝv��)
const static int barNum = 8;//�쐬���鏬�ߐ�(�������{�I�ɕς��Ȃ��̂ł�)

const static int Kstuck = 24;//key.csv�ǂݍ��ݗp��2�����z��̗v�f������1,�ő�l��30
const static int Kline = 4;//��ɓ�������2
const static int Sstuck = 3;//scale_tmp_keynote.csv�ǂݍ��ݗp��2�����z��̗v�f������1
const static int Sline = 18;//��ɓ�������2
const static int MusicNum = 5;//�쐬������K�Ȃ̐��B���R�ŏ��l��2
const static int leftMax = 6;//�����1���߉����ő�
const static int chordKinds = 3;//�y�ȓ��Ŏg�p�����R�[�h�̎�ސ�
const static int noteHNum = 12;//�n�m���̌��Ȃɂ����āA1���߂Ɋ܂܂��ő�̉���


const static double mutateProb = 0.01;//�ˑR�ψيm��
const static int crossNum = 10;//crossNum�_����
const static int restProb = 4;//restProb����1��P���I�΂��(individual.cpp��TP���߂̍�Ƃ̎��g����)

class data_controller {
public:
	//�f�[�^
	int selectedNum = -999;//�ǂ̎��(��b�A�X�P�[��etc.)�̗��K�����邩�B

	char chord[4] = { '1','3','5', 0};
	char notes[15] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 0};
	std::string convNotes[14];//���ɕϊ�����Note������
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'f', 'c', 'g', 'd', 'a', 'e', 'b'},{'b', 'e', 'a', 'd', 'g', 'c', 'f'} };
	char key[Kstuck][Kline];
	//chord:�a���̉��̈ʒu�A�x���\�L, key;���̖��O�ƒ����̎�ނƐ��A�O������ǂނ�, keynoteOrder:�����̂���, 
	//notes:7��, scaleTKeynote:�X�P�[���̗Վ��L���̐��Əꏊ(�x���\�L)�A�O������ǂ�

	//float GproductSum = 0.5;//�쐬�����Individual�ɔԍ������邽�߂Ɏg���Ă鐔�B
	int chromLen;//��`�q�̒���
	int typeofChord;//�a��or����
	int hanonNum;//1~20�Ŏg�p����y�Ȕԍ�
	int chordNum;//�I�����ꂽ����key�̉��Ԗڂ̗v�f�ł��邩
	char chordProg[barNum*2];//�R�[�h�i�s(14151451�Ƃ�)

	int noteNum[2];//[0]���ŏ������A[1]���ő剹���BnoteNum[1]�͕K�����̏��߂ɍŏ����߂ōő�܂ŉ�����ꂽ���̉����ɂ��Ȃ��Ƃ����Ȃ�(4���q�Ȃ�8�A3���q�Ȃ�6)
	int noteNumEnd[2];
	int beat;//���q
	char accompany[chordKinds][leftMax];//���t�̓x��
	int accNoteNum;//���t�̉���
	char hanon[3][noteHNum];//�n�m�����Ȃ�����ꏊ,hanon[2][0]���Œቹ�̓x���Ahanon[2][1]���ō����̓x��

	int Xceil = -999;//X�̏��(1�`20��26�����݂̍ō��l)

	int tempo = 150;

	//�֐�
	data_controller();
	~data_controller();
	bool checkInt(std::string input);
	void readData(std::string fileName, char* databox, int chunkNum, int lineNum);//linenum:key[30][3]��3�̂ق�
	void makeScale();
private:
	//�萔�n

	//�ϐ�
	std::ifstream fin;
	std::string passer;
	char* tmpp;
	char textHolder[80];
	
	//�֐�
	
	//�m�F�p��3�b�ō�����֐��A�{�؂ɂ͊֌W�Ȃ��B
	//�G�ɍ�����̂Ŋm�F�̓x�Ɋm�F�������z��̖��O���v���O��������w�肷��K�v������Ƃ��������ׂ�����܂�
	void confirmCorrect(int tate, int yoko);
};