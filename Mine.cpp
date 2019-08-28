#include "pch.h"
#include "Mine.h"
#include "Pointer.h"


Mine::Mine(int x ,int y, eType Type) : MapObject(x,y,Type)
{
}


Mine::~Mine()
{
}

void Mine::Interact(Pointer* MyPointer)
{
	if (State == eState::None)
	{
		MyPointer->bAlive = false;
	}
}
