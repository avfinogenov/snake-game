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
	static constexpr Color bodyColor = Colors::Gray;//------------ больше доступа
	static constexpr Color emptyColor = Colors::Black;//-----------

/*!!*/	Snek(Board& brd);//не работает при н=0


	void Update(MainWindow& wnd);//управляет оператором направления
	void MakeStep();// делает 1 из 2х шагов
	void CheckVln();//следит за влн



	bool vln = false;// контролер нарушений границ
	bool isEaten = false;   // контролер шага
	Location loc[nSegmentsMax];//положение каждой ячейки змеи
	
	~Snek();
private:		
		Board& brd;		//ссылка на доску 
		int tail = 3;	// конец змеи
		int defX = 40;	// стартовые координаты, так же могут быть loc[0] 
		int defY = 30;//на момент создания
		int stepX;// оператор направления
		int stepY;
};

