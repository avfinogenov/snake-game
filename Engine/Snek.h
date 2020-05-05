#pragma once
#include "Location.h"
#include "MainWindow.h"

class Snek
{
	Location step;//new?????
public:
	static constexpr int nSegmentsMax = 100;
	float stepsize = 1.0f;
	Snek();		

	void SetDef(Location loc);		//??????????

	//new=------------------
	void Update(MainWindow& wnd);	//kinda works лишние переменные
	// выбираем направление

	//void IncStep(double dt);
	//по направлению присваиваем шаг

	void CheckStep(float dt);

	//проверяем готова ли змейка сдвинуться
	void HeadToBody();

	float t;

	Location RStep();//?????
	void Segment(Location in_loc, int n);
	Location GetSeg(int n);
	bool ready = false;

	void MakeStep(float dt);//11!!!!!!
	void ApplyStep();
	
	int tail = 16;
	bool update = false;
	void CV();
	float vs=5;//количество пикселей в секунду
	double idt = 0.0f;
			
	bool stepIsDone=false;
	float vecX;
	float vecY;
	bool bStepUp;						 //new
	bool bStepDown;						 //new
	bool bStepLeft;						 //new
	bool bStepRight;					 //new
	bool HeadToBodyUp;					 //new
	bool HeadToBodyDown;				 //new
	bool HeadToBodyLeft;				 //new
	bool HeadToBodyRight;				 //new

	~Snek();
private:		
		int defX = 40;			
		int defY = 30;			
		bool isEaten = false;			
		Location loc[nSegmentsMax];		
		float hStepX;
		float hStepY;

		float stepX;					
		float stepY;
};

