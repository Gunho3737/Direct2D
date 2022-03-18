#pragma once
#include <list>
#include <map>
#include <GameEngine\Enums.h>
//#include <GameEngine\GameEngineRenderingPipeLine.h>
//
//// 설명 : 
//
//class DebugRenderData
//{
//	TransformData Data;
//	GameEngineRenderingPipeLine Data;
//	// 파이프라인
//	// 쉐이더 헬퍼가 한쌍이어야 한다.
//};

class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCollision;
class GameEngineDebugRenderData;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;
	friend class GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();

	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();

protected:

private:
	std::map<int, std::list<GameEngineActor*>> ActorList_;
	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

	void Init();

public:
	template<typename ActorType>
	ActorType* CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	void ActorUpdate(float _DeltaTime);
	void Render();
	void Release(float _DeltaTime);

	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;



	//////////////////////////////////////////////////////// collision:
private:
	std::map<int, std::list<GameEngineCollision*>> CollisionList_;


	inline std::list<GameEngineCollision*>& GetCollisionGroup(int _Group)
	{
		return CollisionList_[_Group];
	}

	void ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision);

	void LevelChangeEndActorEvent();
	void LevelChangeStartActorEvent();

	// 다른애가 이걸 가릴수 있나요?

public:
	void PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type);

	template<typename UserEnumType>
	void PushCollision(GameEngineCollision* _Collision, UserEnumType _Group)
	{
		PushCollision(_Collision, static_cast<int>(_Group));
	}

	void PushCollision(GameEngineCollision* _Collision, int _Group);
};