#pragma once
#include "MapObject.h"

class Mine : public MapObject
{
public:
	eState State = eState::None;

public:
	Mine() = delete;
	Mine(int x, int y ,eType Type); 
	~Mine();

	virtual void Interact(class Pointer* MyPointer);
};

