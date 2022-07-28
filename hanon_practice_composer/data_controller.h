#pragma once
#include <iostream>
#include <string>


//�萔��`(�|�C���^�Ŏ����Ȃ��Ă��g�����ق����ǂ����)
const int Lega = 3;//�Œ��̒���(���������)
const int Stac = 1;//�ŒZ�̒P��(���������)
const int meloMakeNum = 7;//�����f�B�쐬�����v
const int meloMakeFrag = 2;//��x�ɍ쐬���郁���f�B
const int meloMakeRep = 2;//�����f�B�쐬�J��Ԃ���


class data_controller{
public:
	//�萔��`����
	int chord[3];//chord.csv�̃f�[�^��:3
	int key[24][3];//key.csv�̃f�[�^��:72
	int keynoteOrder[7][2];//keynote_order.csv�̃f�[�^��:14
	int notes[7];//notes.csv�̃f�[�^��(7)
	int scaleTKeynote[5][3];//scale_tmp_keynote.csv�̃f�[�^��(15)

	//�֐�
	data_controller();
	~data_controller();
private:
	const static int dataNum = 5;
	std::string toRead[dataNum] = { "chord.csv", "key.csv", "keynote_order.csv", "notes.csv", "scale_tmp_keynote.csv" };//����܂悭�Ȃ��������ǉ���������񂩂���������
	
	//�֐�
	void readData(std::string fileName);
};