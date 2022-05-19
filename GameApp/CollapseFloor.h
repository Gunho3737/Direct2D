#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class CollapseFloor : public GameEngineActor
{
private:	// member Var

public:
	CollapseFloor(); // default constructer ����Ʈ ������
	~CollapseFloor(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

protected:		// delete constructer
	CollapseFloor(const CollapseFloor& _other) = delete; // default Copy constructer ����Ʈ ���������
	CollapseFloor(CollapseFloor&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	CollapseFloor& operator=(const CollapseFloor& _other) = delete; // default Copy operator ��s��Ʈ ���� ������
	CollapseFloor& operator=(const CollapseFloor&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};
