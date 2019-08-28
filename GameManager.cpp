#include "pch.h"
#include "GameManager.h"

#include "Pointer.h"
#include "Mine.h"
#include "Block.h"


GameManager::~GameManager()
{
	SAFE_DELETE(MyPointer);

	for (auto r : Blocks) { SAFE_DELETE(r); }
	for (auto r : Mines) { SAFE_DELETE(r); }

	Blocks.clear();
	Mines.clear();

	for(int y = 0; y< s; ++y)
	{
		SAFE_DELETE_ARR(Map[y]);
	}
	SAFE_DELETE_ARR(Map);

	for (int y = 0; y < s; ++y)
	{
		SAFE_DELETE_ARR(ObjState[y]);
	}
	SAFE_DELETE_ARR(ObjState);
}

void GameManager::Init()
{
	srand(time(NULL));
	Start = clock();

	Draw(CONSOLE_X / 2 - 6, dY - 5, "A : Sellect");
	Draw(CONSOLE_X / 2 - 6, dY - 4, "F : Flag");

	Map = new eType*[s];
	for (int i = 0; i < s; ++i)
	{
		Map[i] = new eType[s];
	}

	ObjState = new eState*[s];
	for (int i = 0; i < s; ++i)
	{
		ObjState[i] = new eState[s];
	}

	for (int y = 0; y < s; ++y)
	{
		for (int x = 0; x < s; ++x)
		{
			float r = (float)rand() / (float)RAND_MAX;
			if (r > 0.15f)
			{
				Block* pTemp = new Block(x, y, eType::Block);
				Blocks.push_back(pTemp);
				pTemp = nullptr;
				Map[y][x] = eType::Block;
				ObjState[y][x] = eState::None;
			}
			else
			{
				Mine* pTemp = new Mine(x, y, eType::Mine);
				Mines.push_back(pTemp);
				pTemp = nullptr;
				Map[y][x] = eType::Mine;
				ObjState[y][x] = eState::None;
			}
		}
	}

	MyPointer = new Pointer(s / 2 - 1, s / 2 - 1, eType::Pointer);

	Draw(dX+MyPointer->GetPos().X*2,dY+MyPointer->GetPos().Y, "▲");

	for (int y = 0; y = s; ++y)
	{
		for (int x = 0; x = s; ++x)
		{
			if (x != MyPointer->GetPos().X || y != MyPointer->GetPos().Y)
			{
				RenderByType(x, y);
			}
		}
	}
}

void GameManager::Update(float a_fDeltaTime)
{
	MyPointer->NowTerm += a_fDeltaTime;

	if (MyPointer->NowTerm > MyPointer->TargetTerm)
	{
		MyPointer->NowTerm -= MyPointer->TargetTerm;

		int x = MyPointer->GetPos().X;
		int y = MyPointer->GetPos().Y;

		char c = GetKeyInput();

		switch ((eKey)c)
		{
		case eKey::Up: --y; break;
		case eKey::Down: ++y; break;
		case eKey::Left: --x; break;
		case eKey::Right: ++x; break;
		case eKey::Select:
			for (auto r : Blocks)
			{
				if (r->IsCrossed(x, y) == true)
				{
					r->Interact(MyPointer);
					ObjState[r->GetPos().Y][r->GetPos().X] = r->State;
					break;
				}
			}

			for (auto r : Mines)
			{
				if (r->IsCrossed(x, y) == true)
				{
					r->Interact(MyPointer);
					ObjState[r->GetPos().Y][r->GetPos().X] = r->State;
					break;
				}
			}
			break;

		case eKey::Flag:
			for (auto r : Blocks)
			{
				if (r->IsCrossed(x, y) == true)
				{
					if (r->State == eState::None)
					{
						r->State = eState::Flagged;
						ObjState[r->GetPos().Y][r->GetPos().X] = eState::Flagged;
						break;
					}
					else if (r->State == eState::Flagged)
					{
						r->State = eState::None;
						ObjState[r->GetPos().Y][r->GetPos().X] = eState::None;
						break;
					}
				}
			}
			for (auto r : Mines)
			{
				if (r->IsCrossed(x, y) == true)
				{
					if (r->State == eState::None)
					{
						r->State = eState::Flagged;
						ObjState[r->GetPos().Y][r->GetPos().X] = eState::Flagged;
						break;
					}
					else if (r->State == eState::Flagged)
					{
						r->State = eState::None;
						ObjState[r->GetPos().Y][r->GetPos().X] = eState::None;
						break;
					}
				}
			}
			break;
		}

		if ((0 > x || s <= x) || (0 > y || s <= y)) { MyPointer->bMove = false; }

		if (MyPointer->bMove == true)
		{
			RenderByType(MyPointer->GetPos().X, MyPointer->GetPos().Y);

			MyPointer->MoveTo(x, y);

			Draw(dX + MyPointer->GetPos().X * 2, dY + MyPointer->GetPos().Y, "▲");
		}

		MyPointer->bMove = true;
	}

	int cnt = 0;
	for (auto r : Blocks)
	{
		if (r->State == eState::Pushed)
		{
			++cnt;
		}
	}

	if (cnt == Blocks.size())
	{
		bFinish = true;
	}

	if (MyPointer->bAlive == false || bFinish == true)
	{
		for (auto r : Mines)
		{
			r->State = eState::Pushed;
			ObjState[r->GetPos().Y][r->GetPos().X] = r->State;
			RenderByType(r->GetPos().X, r->GetPos().Y);
		}
		delay(2000);

		bOver = true;
	}
}


void GameManager::Render()
{
	gotoxy(1, 1);
	cout << MyPointer->GetPos().X << " " << MyPointer->GetPos().Y;

	int cnt = 0;
	for (auto r : Blocks)
	{
		if (r->State == eState::Pushed)
		{
			++cnt;
		}
	}
	gotoxy(CONSOLE_X / 2 - 6, dY - 3);
	cout << "남은 블럭 숫자 : " << Blocks.size() - cnt << "      ";
	gotoxy(CONSOLE_X / 2 - 6, dY - 2);
	cout << "경과 시간 : " << (clock() - Start) / 1000 << "초 ";
}

void GameManager::KeyInput()
{

}

void GameManager::Draw(int x, int y, const char* c)
{
	gotoxy(x, y);
	cout << c;
}

void GameManager::Clear(int x, int y)
{
	Draw(x, y, " ");
}

bool GameManager::GetOverState() { return bOver; }

void GameManager::RenderByType(int x, int y)
{
	gotoxy(dX + x * 2, dY + y);
	if (Map[y][x] == eType::Block)
	{
		switch (ObjState[y][x])
		{
		case eState::None:
			cout << "■";
			break;
		case eState::Pushed:
			for (auto r : Blocks)
			{
				if (r->IsCrossed(x, y) == true)
				{
					switch (r->MineCnt)
					{
					case 0: cout << "□"; break;
					case 1: cout << "①"; break;
					case 2: cout << "②"; break;
					case 3: cout << "③"; break;
					case 4: cout << "④"; break;
					case 5: cout << "⑤"; break;
					case 6: cout << "⑥"; break;
					case 7: cout << "⑦"; break;
					case 8: cout << "⑧"; break;
					default: cout << "  "; break;
					}
					break;
				}
			}
			break;
		case eState::Flagged:
			cout << "※";
			break;
		}
	}
	else if (Map[y][x] == eType::Mine) {
		switch (ObjState[y][x])
		{
			//cout << "★";
		case eState::None:
			cout << "■";
			break;
		case eState::Pushed:
			cout << "★";
			break;
		case eState::Flagged:
			cout << "※";
			break;
		}
	}
}