#pragma once
#include "MapObject.h"

class Block : public MapObject
{
public:
	eState State = eState::None;

	int MineCnt = 0;

public:
	Block() = delete;
	Block(int x, int y, eType Type);
	~Block();

	virtual void Interact(class Pointer* MyPointer);
	void Interact(int x, int y);
	void Chain(int x, int y);

	void Push(int x, int y);
};

