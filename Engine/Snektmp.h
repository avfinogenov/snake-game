#pragma once
#include "Board.h"
#include "Location.h"
#include "MainWindow.h"
#include "Goal.h"
class Snek
{
public:
	static constexpr int nSegmentsMax = 100;
	static constexpr Color headColor = Colors::Red;//-----------
	static constexpr Color bodyColor = Colors::Gray;//------------ ������ �������
	static constexpr Color emptyColor = Colors::Black;//-----------

/*!!*/	Snek(Board& brd);//�� �������� ��� �=0


	void Update(MainWindow& wnd);//��������� ���������� �����������
	void MakeStep();// ������ 1 �� 2� �����
	void CheckVln();//������ �� ���



	bool vln = false;// ��������� ��������� ������
	bool isEaten = false;   // ��������� ����
	Location loc[nSegmentsMax];//��������� ������ ������ ����
	
	~Snek();
private:		
		Board& brd;		//������ �� ����� 
		int tail = 3;	// ����� ����
		int defX = 40;	// ��������� ����������, ��� �� ����� ���� loc[0] 
		int defY = 30;//�� ������ ��������
		int stepX;// �������� �����������
		int stepY;
};

