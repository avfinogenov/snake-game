#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Snek.h"
#include "Goal.h"
class Board
{
	enum class CellContents 
	{
		Empty,
		Goal,
		Obstacle,
		Poison
	};
	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColor = Colors::Gray;
	static constexpr Color emptyColor = Colors::Black;
	static constexpr Color GoalColor = Colors::Green;
	static constexpr Color ObstacleColor = Colors::LightGray;
	static constexpr Color PoisonColor = Colors::Magenta;
	//static constexpr Color GoalColor = Colors::Green;

	int cellNumX;
	int cellNumY;
	//Color* cell;//создает €чейки пол€
	//CellContents* content[cellNumX * cellNumY] = { CellContents::Empty };
	Color* cell;
	CellContents* content;
	int freeCell;
public:
	Board(Graphics& gfx, int cellsize, int x,int  y,int  srate,int  pamount,int  gamount);
	void WCell(Location in_loc, Color c);
	void Draw(Graphics& gfx);//выводит доску на экран
	void CheckVln();
	void CreateObstacle(int i, int j);
	void SetPoison(int i, int j);


	 //!!!!=======================
	void MakeStep(float dt);
	//!!!============

	void PaintGoal(Goal& g);
	void Update(MainWindow& wnd);
	void SetGoal(int num);
	void ConsumeCheck();
	bool vln = false;
	bool isEaten = false;
	void SetSnek();
	bool* guest;
	~Board();
private:
	Graphics& gfx;
	int size;//размеры €чеек
	//static constexpr int height=10;
	Snek* snek;
	Goal* g;
	int srate;
	int  pamount;
	int  gamount;
	
	

};

