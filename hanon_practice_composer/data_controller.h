#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

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
const static int MusicNum = 5;//�쐬������K�Ȃ̐�

//�O���[�o���ϐ��n
/*
static int chromLen = -999;//���F�̂̒����B�����W�c���Ƃ��ɐݒ肳���
static char musicChord = NULL;//��
static int typeofChord = -999;//�a���Z���Kor�����Z���K�B�a����0�A������1�łЂƂ܂��l���Ă���
static int hanonNum = -999;//�n�m��1�`20�̊y�Ȃ̍ۂɂ̂ݎg�p����A�y�Ȕԍ������Ă����ꏊ
*/

class data_controller {
public:
	//�f�[�^
	char chord[3] = { '1','3','5' }, notes[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'H' };
	char scaleTKeynote[Sstuck][Sline];
	char keynoteOrder[2][7] = { {'F', 'C', 'G', 'D', 'A', 'E', 'H'},{'H', 'E', 'A', 'D', 'G', 'C', 'F'} };
	char key[Kstuck][Kline];
	//chord:�a���̉��̈ʒu�A�x���\�L, key;���̖��O�ƒ����̎�ނƐ��A�O������ǂނ�, keynoteOrder:�����̂���, 
	//notes:7��, scaleTKeynote:�X�P�[���̗Վ��L���̐��Əꏊ(�x���\�L)�A�O������ǂ�

	float GproductSum = 0.5;//�쐬�����Individual�ɔԍ������邽�߂Ɏg���Ă鐔�B
	int chromLen = -999;
	//char musicChord = NULL;
	int typeofChord = -999;
	int hanonNum = -999;
	int chordNum = -999;
	char chordProg[barNum];

	//�֐�
	data_controller();
	~data_controller();
	bool checkInt(std::string input);
private:
	//�萔�n

	//�ϐ�
	std::ifstream fin;
	std::string passer;
	char* tmpp;
	char textHolder[80];
	
	//�֐�
	void readData(std::string fileName, char* databox, int chunkNum, int lineNum);//linenum:key[30][3]��3�̂ق�

	//�m�F�p��3�b�ō�����֐��A�{�؂ɂ͊֌W�Ȃ��B
	//�G�ɍ�����̂Ŋm�F�̓x�Ɋm�F�������z��̖��O���v���O��������w�肷��K�v������Ƃ��������ׂ�����܂�
	void confirmCorrect(int tate, int yoko);
};