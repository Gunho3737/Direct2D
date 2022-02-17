#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>

// ���� :
class GameEngineComponent;
class GameEngineTransformComponent;
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
	ComponentType* CreateComponent(int _Order = 0)
	{
		GameEngineComponent* NewComponent = new ComponentType(); 
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		ComponentList_.push_back(NewComponent);
		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);;
	}

	template<typename ComponentType>
	ComponentType* CreateTransformComponent(GameEngineTransform* _ParentTrans, int _Order = 0)
	{
		// ��ĳ������ �̿��ؼ� ������ ������ �����̴�.
		GameEngineTransformComponent* NewComponent = new ComponentType();
		NewComponent->SetOrder(_Order);
		NewComponent->InitComponent(this);
		if (nullptr == _ParentTrans)
		{
			GameEngineDebug::MsgBoxError("Ʈ�������� ���þ� ������ϴ�.");
		}
		NewComponent->AttachTransform(_ParentTrans);
		ComponentList_.push_back(NewComponent);

		NewComponent->Start();
		return dynamic_cast<ComponentType*>(NewComponent);;
	}

protected:
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;

	// Ʈ�������� ��ȭ��Ų�ٴ°� �⺻������ �����Ұ̴ϴ�.

////////////////////////

public:
	GameEngineTransform* GetTransform() 
	{
		return 	Transform_;
	}

private:
	GameEngineTransform* Transform_;
	GameEngineLevel* Level_;

	// Status
	std::list<GameEngineComponent*> ComponentList_;

	std::list<GameEngineTransformComponent*> TransformComponentList_;

	void SetLevel(GameEngineLevel* Level);
};

