#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class CrawlBug : public GameEngineActor
{
private:	// member Var

public:
	CrawlBug(); // default constructer ����Ʈ ������
	~CrawlBug(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;
	LeftRight Direction;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;


	float StartX;
protected:		// delete constructer
	CrawlBug(const CrawlBug& _other) = delete; // default Copy constructer ����Ʈ ���������
	CrawlBug(CrawlBug&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	CrawlBug& operator=(const CrawlBug& _other) = delete; // default Copy operator ����Ʈ ���� ������
	CrawlBug& operator=(const CrawlBug&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Walk();
	void Spin();
	void Death();

public:
	bool GetDamage;
	int HP;

	float MoveDistance;
	float ImmuneTime;
	float SpinTime;
	float Speed;
};

