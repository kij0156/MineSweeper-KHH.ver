#include "pch.h"
#include "OverScene.h"


OverScene::OverScene(SceneManager* a_pParent) : Scene(a_pParent) {
}

OverScene::~OverScene() {
	m_refParent = nullptr;
}

eScene OverScene::GetScene() {
	return eScene::OverScene;
}

void OverScene::Init() {

}
void OverScene::Update(float a_fDeltaTime) {

}
void OverScene::Render() {
	gotoxy(1, 1);
	cout << "�й��ϼ̽��ϴ�!!!";
	getchar();
	Exit();
}

void OverScene::KeyInput() {

}