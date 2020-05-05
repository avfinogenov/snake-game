#include "Board.h"
#include"Snek.h"
#include <random>



Board::Board(Graphics & gfx)
	: gfx(gfx),
	snek()
{
	for (int x = 0;x < cellNumX;x++)//sdsdsd
	{
		for (int y = 0;y < cellNumY;y++)
		{
			cell[x][y] = Colors::Black;
			guest[x][y] = false;
		}
	}
	SetSnek();
	for (int x = 0;x < cellNumX;x++)
	{
		int y = 0;
		guest[x][y] = true;
		y = cellNumY-1;
		guest[x][y] = true;
	}
	for (int y = 0;y < cellNumY;y++)
	{
		int x = 0;
		guest[x][y] = true;
		x = cellNumX-1;
		guest[x][y] = true;
	}


	
	SetGoal();
}

void Board::WCell(Location in_loc, Color c)
{
	cell[(int)in_loc.x][(int)in_loc.y] = c;
}

void Board::Draw(Graphics& gfx)
{
	
	for (int x=0;x<cellNumX;x++)
	{
		for (int y=0;y<cellNumY;y++)
		{			
			gfx.DrawRect(x*width, y*height, width, height, cell[x][y]);

		}
	}
	

}

void Board::MakeStep(float dt)
{

	if (isEaten)				
	{
		snek.Segment(snek.GetSeg(snek.tail - 1), snek.tail);//создаем новый хвост
	}
	
		snek.MakeStep(dt);
		if(snek.stepIsDone){
			CheckVln();
			int tmp = snek.tail;
			Location tmpLc = snek.GetSeg(tmp - 1);
			WCell(tmpLc, emptyColor);


		for (int n = snek.tail - 1;n >= 1;n--)//с хвоста к голове
		{
			snek.Segment(snek.GetSeg(n - 1), n);//записать н-1 в н
			
		}
		WCell(snek.GetSeg(1), bodyColor);
				//snek.IncStep(dt);

		
		snek.ApplyStep();
		guest[(int)tmpLc.x][(int)tmpLc.y] = false;
		if (!vln) {
			Location head = snek.GetSeg(0);
			WCell(head, headColor);//записать нарисовать голову
		
			guest[(int)head.x][(int)head.y] = true;
		}
		if (isEaten)				//если голодная
		{
			snek.tail++;//удлиняем хвост
			isEaten = false;//перевариваем фрукт
		}
		snek.stepIsDone = false;
		}

}

void Board::CheckVln()
{
	Location l1 = snek.GetSeg(0);
	Location l2= snek.RStep();
	Location in_loc;
	if (l2.x != l2.y) {
		in_loc.x = l1.x + l2.x;
		in_loc.y = l1.y + l2.y;
	if(guest[in_loc.x][in_loc.y])/// (guest[l1.x][l1.y])
	{

		vln = true;
	}
}

}

void Board::PaintGoal(Goal& g)
{
	cell[(int)g.loc.x][(int)g.loc.y] = GoalColor;
}

void Board::Update(MainWindow & wnd)
{
	snek.Update(wnd);
}

void Board::SetGoal()
{
	int q = (cellNumX * cellNumY);
	int p = cellNumX * 2 + cellNumY * 2; 
	snek.tail;
	freeCell = q - p - snek.tail;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> sDist(0, freeCell);
	int x = 0;
	int y = 0;
	int randomnumber = sDist(rng);
	for (int i = 0;i< cellNumX*cellNumY;i++)
	{
		x = i - (i / cellNumX)*cellNumX;
		y = i / cellNumX;
		if (!guest[x][y])
		{
			randomnumber--;
		}
		if (randomnumber==0)
		{
			break;
		}
	}
	g.loc.x = x;
	g.loc.y = y;
	WCell(g.loc, GoalColor);
	
}

void Board::ConsumeCheck()
{
	Location ls = snek.GetSeg(0);
	Location lg = g.loc;
	if (((int)lg.x == (int)ls.x) && ((int)lg.y ==(int) ls.y))//сравниваем положения головы и фрукта
	{
		SetGoal();
		// отправляем фрукт в новые кординаты

		isEaten = true;//змея проглатывает фрукт
		PaintGoal(g);
							/*if (dif>1)
							{
							dif--;
							}*/
	}

}



void Board::SetSnek()
{
	for (int i = snek.tail - 1; i > 0;i--) {
		WCell(snek.GetSeg(i), bodyColor);
		int x= snek.GetSeg(i).x;
		int y= snek.GetSeg(i).y;
		guest[x][y] = true;
		}
	WCell(snek.GetSeg(0), headColor);
	int x = snek.GetSeg(0).x;
	int y = snek.GetSeg(0).y;
	guest[x][y] = true;

}

Board::~Board()
{
}
