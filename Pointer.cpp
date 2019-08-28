#include "pch.h"
#include "Pointer.h"


Pointer::Pointer(int x, int y, eType Type) : MapObject(x, y, Type)
{

}

Pointer::~Pointer()
{

}

void Pointer::MoveTo(int x, int y)
{
	Pos.X = x;
	Pos.Y = y;
}