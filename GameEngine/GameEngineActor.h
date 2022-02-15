#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// 설명 :
class GameEngineComponent;
class GameEngineLevel;
class GameEngineTransform;
class GameEngineActor : public GameEngineObjectNameBase
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	GameEngineLevel* GetLevel() 
	{
		return Level_;
	}

	template<typename ComponentType>
	ComponentType* CreateComponent()
	{
		ComponentType* NewComponent = new ComponentType(); 
		NewComponent->InitComponent(this);


		ComponentList_.push_back(NewComponent);
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// 트랜스폼을 변화시킨다는걸 기본적으로 생각할겁니다.

private:
	GameEngineLevel* Level_;
	GameEngineTransform* Transform_;

	std::list<GameEngineComponent*> ComponentList_;

	void SetLevel(GameEngineLevel* Level);

};

