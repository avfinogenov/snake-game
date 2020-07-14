#include "Board.h"

#include <random>



Board::Board(Graphics& gfx, int cellsize, int in_x, int  in_y, int  in_srate, int  in_pamount, int  in_gamount)
	: gfx(gfx),
	
	size(cellsize),
	cellNumX(in_x),
	cellNumY(in_y),
	srate(in_srate),
	pamount(in_pamount),
	gamount(in_gamount)
	
{
	cell = new Color[cellNumX * cellNumY];
	
	content = new CellContents[cellNumX * cellNumY];
	
	for (int i = 0; i < cellNumX * cellNumY; i++)
	{
		cell[i] = Colors::Black;
		content[i] = CellContents::Empty;
	}
	snek = new Snek(srate, cellNumX, cellNumY);
	guest = new bool[cellNumX * cellNumY];
	SetSnek();
	//or (int x = 0; x < cellNumX; x++)
	//
	//	int y = 0;
	//	guest[x][y] = true;
	//	y = cellNumY - 1;
	//	guest[x][y] = true;
	//
	//or (int y = 0; y < cellNumY; y++)
	//
	//	int x = 0;
	//	guest[x][y] = true;
	//	x = cellNumX - 1;
	//	guest[x][y] = true;
	//
	//int count = 150;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> sDist(0, cellNumX * cellNumY);

	while (pamount > 0)
	{
		int randomnumber = sDist(rng);
		int Xrand, Yrand;
		Yrand = randomnumber / cellNumX;
		Xrand = randomnumber - Yrand * cellNumX;
		if (cell[Yrand*cellNumX + Xrand]== Colors::Black)
		{
			content[Yrand * cellNumX + Xrand] = CellContents::Poison;
			SetPoison(Xrand, Yrand);
			pamount--;
		}

	}

	
	g = new Goal[gamount];
	for (int i = 0; i < gamount; i++)
	{
		SetGoal(i);
	}
	
}

void Board::WCell(Location in_loc, Color c)
{
	cell[((int)in_loc.y)*cellNumX + (int)in_loc.x] = c;
}

void Board::Draw(Graphics& gfx)
{

	for (int x = 0; x < cellNumX; x++)
	{
		for (int y = 0; y < cellNumY; y++)
		{
			gfx.DrawRect(x * size, y * size, size, size, cell[y*cellNumX + x]);

		}
	}


}

void Board::MakeStep(float dt)
{

	if (isEaten)
	{
		(*snek).Segment((*snek).GetSeg((*snek).tail - 1), (*snek).tail);//создаем новый хвост
	}

	(*snek).MakeStep(dt);
	if ((*snek).stepIsDone) {
		CheckVln();
		int tmp = (*snek).tail;
		Location tmpLc = (*snek).GetSeg(tmp - 1);
		WCell(tmpLc, emptyColor);


		for (int n = (*snek).tail - 1; n >= 1; n--)//с хвоста к голове
		{
			(*snek).Segment((*snek).GetSeg(n - 1), n);//записать н-1 в н

		}
		WCell((*snek).GetSeg(1), bodyColor);
		//(*snek).IncStep(dt);


		(*snek).ApplyStep();
		int tmpx = (int)tmpLc.x;
		int tmpy = (int)tmpLc.y;
		guest[tmpy*cellNumX + tmpy] = false;
		if (!vln) {
			Location head = (*snek).GetSeg(0);
			WCell(head, headColor);//записать нарисовать голову

			//guest[(int)head.x][(int)head.y] = true;
		}
		if (isEaten)				//если голодная
		{
			(*snek).tail++;//удлиняем хвост
			isEaten = false;//перевариваем фрукт
			content[(*snek).GetSeg(0).y * cellNumX + (*snek).GetSeg(0).x] = CellContents::Empty;
		}
		(*snek).stepIsDone = false;
	}

}

void Board::CheckVln()
{
	Location l1 = (*snek).GetSeg(0);
	Location l2 = (*snek).RStep();
	Location in_loc;
	if (l2.x != l2.y) {
		in_loc.x = l1.x + l2.x;
		in_loc.y = l1.y + l2.y;


		if (in_loc.x < 0 || in_loc.x>cellNumX || in_loc.y<0 || in_loc.y>cellNumY)
		{
			vln = true;
		}

		
		if (cell[in_loc.y* cellNumX+ in_loc.x] == Colors::Gray)
		{
			vln = true;
		}
		if (cell[in_loc.y * cellNumX + in_loc.x] == Colors::Magenta)
		{
			(*snek).vs+=snek->speduprate;
			content[in_loc.y * cellNumX + in_loc.x] = CellContents::Empty;
		}
		if (cell[in_loc.y * cellNumX  + in_loc.x] == Colors::LightGray)
		{
			vln = true;
		}
		///if(guest[in_loc.x][in_loc.y])/// (guest[l1.x][l1.y])
		///{
		///
		///	vln = true;
		///}
	}

}

void Board::CreateObstacle(int i, int j)
{
	// в свободную клетку засунуть преграду
	if (cell[j * cellNumX + i] == Color(Colors::Black))
	{
		content[j * cellNumX + i] = CellContents::Obstacle;
		cell[j * cellNumX + i] = ObstacleColor;
	}
}

void Board::SetPoison(int i, int j)
{
	if (cell[j*cellNumX+i] == Color(Colors::Black))
	{
		cell[j * cellNumX + i] = PoisonColor;
	}
}

void Board::PaintGoal(Goal& g)
{
	content[g.loc.y * cellNumX + g.loc.x] = CellContents::Goal;
	cell[g.loc.y * cellNumX + g.loc.x] = GoalColor;
}

void Board::Update(MainWindow& wnd)
{
	(*snek).Update(wnd);
}

void Board::SetGoal(int num)
{
	int count = 1;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> sDist(0, cellNumX * cellNumY);

	while (count > 0)
	{
		int randomnumber = sDist(rng);
		int Xrand, Yrand;
		Yrand = randomnumber / cellNumX;
		Xrand = randomnumber - Yrand * cellNumX;
		if (cell[Yrand*cellNumX+Xrand] == Colors::Black)
		{
			g[num].loc.x = Xrand;
			g[num].loc.y = Yrand;
			WCell(g[num].loc, GoalColor);
			count--;
		}

	}
	//g.loc.x = x;
	//g.loc.y = y;
	//WCell(g.loc, GoalColor);

}

void Board::ConsumeCheck()
{
	Location ls = (*snek).GetSeg(0);
	Location* lg = new Location[gamount];
	for (int i = 0; i < gamount; i++)
	{
		lg[i] = g[i].loc;
		if (((int)lg[i].x == (int)ls.x) && ((int)lg[i].y == (int)ls.y))//сравниваем положения головы и фрукта
		{
			SetGoal(i);
			// отправляем фрукт в новые кординаты

			isEaten = true;//змея проглатывает фрукт
			int count = 1;
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> sDist(0, cellNumX * cellNumY);

			while (count > 0)
			{
				int randomnumber = sDist(rng);
				int Xrand, Yrand;
				Yrand = randomnumber / cellNumX;
				Xrand = randomnumber - Yrand * cellNumX;
				if (cell[Yrand*cellNumX + Xrand] == Colors::Black)
				{
					CreateObstacle(Xrand, Yrand);
					count--;
				}

			}

		}
	
	

		//PaintGoal(g);
			 /*if (dif>1)
			 {
			 dif--;
			 }*/
	}
	delete[] lg;
}



void Board::SetSnek()
{
	for (int i = (*snek).tail - 1; i > 0; i--) {
		WCell((*snek).GetSeg(i), bodyColor);
		int x = (*snek).GetSeg(i).x;
		int y = (*snek).GetSeg(i).y;
		guest[y * cellNumX + x] = true;
	}
	WCell((*snek).GetSeg(0), headColor);
	int x = (*snek).GetSeg(0).x;
	int y = (*snek).GetSeg(0).y;
	guest[y*cellNumX+x] = true;

}

Board::~Board()
{
}
