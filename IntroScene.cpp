#include "pch.h"
#include "IntroScene.h"


IntroScene::IntroScene(SceneManager * a_pParent) : Scene(a_pParent) {}

IntroScene::~IntroScene() {
	m_refParent = nullptr;
}

eScene IntroScene::GetScene() {
	return eScene::IntroScene;
}

void IntroScene::Init() {
	ShowMenu();
}
void IntroScene::Update(float a_fDeltaTime) {
	SelectMenu();
}
void IntroScene::Render() {

}

void IntroScene::KeyInput() {
}

void IntroScene::ShowMenu() {
	Draw(x, y, ">> START");
	Draw(x, y + 1, "   EXIT");
}

// 메뉴 추가 가능
void IntroScene::SelectMenu() {
	eKey c = (eKey)GetKeyInput();

	switch (c) {
	case eKey::Up:
		Draw(x, y, "  ");

		if (y == Y) { y = LastY; } // 맨 위면 맨 아래로
		else { y = y - 1; }

		Draw(x, y, ">>");
		break;

	case eKey::Down:
		Draw(x, y, "  ");

		if (y == LastY) { y = Y; } // 맨 아래면 맨 위로
		else { y = y + 1; }

		Draw(x, y, ">>");
		break;

	case eKey::Enter:
		switch (y) {
		case Y:		Over();	break;
		case LastY: Exit();	break; // 종료면 끝내자
		}

		break;
	}
}

void IntroScene::Draw(int x, int y, const char* c) {
	gotoxy(x, y);
	cout << c;
}
