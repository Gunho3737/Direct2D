#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

// �̳༮�鸸�� �׷��� ����ڽ��ϴ�.

enum class CollisionType
{
	Sphere,
	AABBBox,
	OBBBox,
	MAX,
};

// ���� :
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;


	template<typename UserType>
	void SetCollisionGroup(UserType _Type)
	{
		SetCollisionGroup(static_cast<int>(_Type));
	}

	void SetCollisionGroup(int _Type);

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::vector<GameEngineCollision*>& _Other);


	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);


protected:


private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

