#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Snek.h"
#include "Goal.h"
class Board
{
	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColor = Colors::Gray;
	static constexpr Color emptyColor = Colors::Black;
	static constexpr Color GoalColor = Colors::Green;
	static constexpr Color PoisonColor = Colors::Magenta;
	static constexpr Color ObstacleColor = Colors::LightGray;
	
	static constexpr int cellNumX = (Graphics::ScreenWidth) / 10;
	static constexpr int cellNumY = (Graphics::ScreenHeight) / 10;
	Color cell[cellNumX][cellNumY];//создает €чейки пол€
	int freeCell;
public:
	Board(Graphics& gfx);
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
	void SetGoal();
	void ConsumeCheck();
	bool vln = false;
	bool isEaten = false;
	void SetSnek();
	bool guest[cellNumX][cellNumY];
	~Board();
private:
	Graphics& gfx;
	static constexpr int width=10;//размеры €чеек
	static constexpr int height=10;
	Snek snek;
	Goal g;
	
	
	

};

