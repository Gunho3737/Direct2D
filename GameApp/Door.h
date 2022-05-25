#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class Door : public GameEngineActor
{
private:	// member Var

public:
	Door(); // default constructer ����Ʈ ������
	~Door(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	bool DoorOn;

protected:		// delete constructer
	Door(const Door& _other) = delete; // default Copy constructer ����Ʈ ���������
	Door(Door&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	Door& operator=(const Door& _other) = delete; // default Copy operator ����Ʈ ���� ������
	Door& operator=(const Door&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

