#include "pch.h"
#include "FinishScene.h"


FinishScene::FinishScene(SceneManager* a_pParent) : Scene(a_pParent) {
}

FinishScene::~FinishScene() {
	m_refParent = nullptr;
}

eScene FinishScene::GetScene() {
	return eScene::OverScene;
}

void FinishScene::Init() {

}
void FinishScene::Update(float a_fDeltaTime) {

}
void FinishScene::Render() {
	gotoxy(1, 1);
	cout << "�¸��ϼ̽��ϴ�!!!";
	// ������
	getchar();
	// Application���� ��������
	Exit();
}

void FinishScene::KeyInput() {

}