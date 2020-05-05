#include "Snek.h"



Snek::Snek()
{
	for (int n = 0; n < tail; n++)
	{
		loc[n].x = defX + n;
		loc[n].y = defY;
	}
	step.x = -1;
	step.y = 0;
	stepX = -stepsize;
	stepY = 0;
}

void Snek::SetDef(Location loc)
{
	defX = (int)loc.x;
	defY = (int)loc.y;
}

void Snek::Update(MainWindow& wnd)
{
	HeadToBody();
	if (!update)//изменить прирощение можно только если оно было учтено
	{
	
		if (!HeadToBodyDown&&!HeadToBodyUp)

		{
			if (wnd.kbd.KeyIsPressed('W'))
			{

				bStepUp = true;
				bStepDown = false;
				bStepLeft = false;
				bStepRight = false;
				/*stepY = -stepsize*dt;
				stepX = 0;*/
				update = true;
			}
		
			if (wnd.kbd.KeyIsPressed('S'))
			{
				bStepUp = false;
				bStepDown = true;
				bStepLeft = false;
				bStepRight = false;
				/*stepY = stepsize*dt;
				stepX = 0;*/
				update = true;
			}
		}
		if (!HeadToBodyRight&&!HeadToBodyLeft)
		{
			if (wnd.kbd.KeyIsPressed('A'))
			{
				bStepUp = false;
				bStepDown = false;
				bStepLeft = true;
				bStepRight = false;
				/*stepY = 0;
				stepX = -stepsize*dt;*/
				update = true;
			}
		
			if (wnd.kbd.KeyIsPressed('D'))
			{
				bStepUp = false;
				bStepDown = false;
				bStepLeft = false;
				bStepRight = true;
			/*	stepY = 0;
				stepX = stepsize*dt;*/
				update = true;
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_SHIFT))
		{
			update = true;
			vs++;
		}
		if (wnd.kbd.KeyIsPressed(VK_CONTROL))
		{
			update = true;
			vs--;
		}
	}
	else {
		bStepUp = false;
		bStepDown = false;
		bStepLeft = false;
		bStepRight = false;
	}
	
}

//void Snek::IncStep(double dt)
//{
//	//bool prevStep;
//	//присваиваем шаг
//	if (bStepUp)							 //
//	{										 //
//		stepY -= stepsize*dt;				 //
//	}										 //
//	if (bStepDown)							 //		присваиваем шаг
//	{										 //
//		stepY += stepsize*dt;				 //
//	}										 //
//	if (bStepLeft)							 //
//	{										 //
//		stepX -= stepsize*dt;				 //
//	}										 //
//	if (bStepRight)							 //
//	{										 //
//		stepX += stepsize*dt;				 //
//	}										 //
//	
// // разрешаем изменение приращения
//	update = false;			
//	
//}

void Snek::CheckStep(float dt)
{	//подготовка
//	IncStep(dt);
//	idt += dt;
//	float t = 1 / vs;
//	vecX += stepX;
//	vecY += stepY;
//	if (idt >= t)
//	{
//		MakeStep();
//	}
//	
//	// надо описать универсальный флоут вектор который будет увеличиваться до тех пор
//	//пока не пройдет нужное количество времени, после чего он будет переделан в 
//	//команду змейке изменить позицию
//	float defStepX;
//	float defStepY;
//	if (HeadToBodyUp)
//	{
//		defStepX = 0;
//		defStepY = -stepsize*dt;
//	}
//	if (HeadToBodyDown)
//	{
//		defStepX = 0;
//		defStepY = stepsize*dt;
//	}
//	if(HeadToBodyLeft)
//	{
//		defStepX = -stepsize*dt;
//		defStepY = 0;
//	}
//	if(HeadToBodyRight)
//	{
//		defStepX = stepsize*dt;
//		defStepY = 0;
//	}
//
//
//
////	if (((int)defStepX) || ((int)defStepY) != 0){}
//	//нужно: работающий bodyLoc{}
//	//bool bodyLoc{up,down,left,right} sets defStep
//	//необходимо знать количество подсчетов
//	//для получаения целого значения перемещения = CreatorVar or CV 
//	//выбрать больший из двух шагов (см исключения) или назначить шаг по умолчанию
//	
//	stepY;//данный шаг по вертикали
//	stepX;//данный шаг по горизонтали
//	loc[0];//голова, ей нужен целый шаг
//


	//
	//idt += dt;
	//float t = 1 / vs;
	//if (idt > t)
	//{
	//	if ((stepX != 0) && (stepY != 0))
	//	{
	//		if (fabs(stepX) > fabs(stepY))
	//		{
	//			step.x = stepX;
	//			step.y = 0;
	//		}
	//		else
	//		{
	//			step.x = 0;
	//			step.y = stepY;
	//		}
	//	}

	//	idt = 0.0f;
	////	MakeStep();



	//}
		/*fabs(stepX);
		fabs(stepY);
		stepX;
		stepY;
		defStepX;
		defStepY;
		MakeStep();

*/




















}

void Snek::HeadToBody()
{
	int x;
	int y;
	x=loc[0].x - loc[1].x;
	y=loc[0].y - loc[1].y;
	if (x==0)
	{
		if (y>0)
		{ 
			HeadToBodyDown = true;
			HeadToBodyUp = false;
			HeadToBodyLeft = false;
			HeadToBodyRight = false;
		}
		if(y<0)
		{
			HeadToBodyDown = false;
			HeadToBodyUp = true;
			HeadToBodyLeft = false;
			HeadToBodyRight = false;
		}
	}
	if(y==0)
	{
		if (x > 0)
		{
			HeadToBodyDown = false;
			HeadToBodyUp = false;
			HeadToBodyRight = true;
			HeadToBodyLeft = false;
		}
		if (x < 0)
		{
			HeadToBodyDown = false;
			HeadToBodyUp = false;
			HeadToBodyRight = false;
			HeadToBodyLeft = true;
		}
	}

}

Location Snek::RStep()
{
	return step;
}

void Snek::Segment(Location in_loc, int n)
{
	int tmpX = (int)in_loc.x;
	int tmpY= (int)in_loc.y;
	loc[n].x = tmpX;
	loc[n].y =tmpY;
}

Location Snek::GetSeg(int n)
{
	return loc[n];
}


void Snek::MakeStep(float dt)
{

	idt += dt;
	t = 1.0f / vs;
	
	if(idt >= t)
	{
		if (bStepUp)
		{	
		step.y = -1;
		step.x = 0;
		}
		if (bStepDown) {  
		step.y = 1;
		step.x = 0;
		}
		if (bStepRight) { 
		step.x = 1;
		step.y = 0;
		}
		if (bStepLeft) {  
		step.x = -1;
		step.y = 0;
		}

		if( !update	)
		{		
			if(HeadToBodyDown)
			{
				step.y = 1;
				step.x = 0;
			}
				if(HeadToBodyUp){
					
					
					step.y = -1;
					step.x = 0;
				}
				if(HeadToBodyLeft){
					
					step.x = -1;
					step.y = 0;
				}
				if(HeadToBodyRight){
					
					step.x = 1;
					step.y = 0;
				}
			
		}

		update = false;
		idt = 0;
		stepIsDone = true;
	}
	else
	{
		if (bStepUp)
		{
			step.y = -1;
			step.x = 0;
		}
		if (bStepDown) {
			step.y = 1;
			step.x = 0;
		}
		if (bStepRight) {
			step.x = 1;
			step.y = 0;
		}
		if (bStepLeft) {
			step.x = -1;
			step.y = 0;
		}
		

		

		update = false;
	}









/*



	hStepX+= stepX;
	hStepY += stepY;
	if ((int)hStepX != 0) {
		int tmpX = (int)hStepX;
		loc[0].x += tmpX;
		hStepX=hStepX-(float)tmpX;
	}
	if ((int)hStepY != 0) {
		int tmpY = (int)hStepY;
		loc[0].y += tmpY;
		hStepY = hStepY - (float)tmpY;
	}
	update = false;
	*/
}

void Snek::ApplyStep()
{
	loc[0].x += step.x;
	loc[0].y += step.y;
}

void Snek::CV()
{
	float t = 1 / vs;


}

Snek::~Snek()
{
}

