#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"
#include "CameraActor.h"
#include "CameraComponent.h"
#include "GameEngineCollision.h"
#include "GameEngineDebugRenderData.h"
#include "GameEngineRenderTarget.h"


CameraActor* GameEngineLevel::GetMainCameraActor()
{
	return MainCameraActor_;
}

CameraComponent* GameEngineLevel::GetMainCamera()
{
	return MainCameraActor_->GetCamera();
}

CameraActor* GameEngineLevel::GetUICameraActor()
{
	return UICameraActor_;
}

CameraComponent* GameEngineLevel::GetUICamera()
{
	return UICameraActor_->GetCamera();
}
GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}

		}
	}
}

void GameEngineLevel::Init()
{
	MainCameraActor_ = CreateActor<CameraActor>();
	UICameraActor_ = CreateActor<CameraActor>();

	UICameraActor_->GetCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	UICameraActor_->GetCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{


	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			// 위치바꾸고
			Actor->Update(_DeltaTime);
			Actor->UpdateComponent(_DeltaTime);
		}
	}
}

void GameEngineLevel::LevelChangeEndActorEvent()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->LevelChangeEndEvent();
		}
	}
}
void GameEngineLevel::LevelChangeStartActorEvent()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->LevelChangeStartEvent();
		}
	}
}

void GameEngineLevel::Render()
{
	GameEngineDevice::RenderStart();

	MainCameraActor_->GetCamera()->ClearCameraTarget();
	UICameraActor_->GetCamera()->ClearCameraTarget();
	// 월드를 그리는 것이죠
	MainCameraActor_->GetCamera()->Render();
	MainCameraActor_->GetCamera()->DebugRender();
	// ui를 여기에 그리죠?
	UICameraActor_->GetCamera()->Render();

	GameEngineDevice::GetBackBufferTarget()->Merge(MainCameraActor_->GetCamera()->GetCameraRenderTarget());
	GameEngineDevice::GetBackBufferTarget()->Merge(UICameraActor_->GetCamera()->GetCameraRenderTarget());

	// 충돌체 랜더링이 무조건 화면에 뚫고 나와야하는 애들은
	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::Release(float _DeltaTime)
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			Actor->ReleaseUpdate(_DeltaTime);
		}
	}

	MainCameraActor_->GetCamera()->ReleaseRenderer();
	UICameraActor_->GetCamera()->ReleaseRenderer();


	// 콜리전 삭제
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderMapBeginIter = CollisionList_.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator RenderMapEndIter = CollisionList_.end();


		for (; RenderMapBeginIter != RenderMapEndIter; ++RenderMapBeginIter)
		{
			std::list<GameEngineCollision*>& Collisions = RenderMapBeginIter->second;

			std::list<GameEngineCollision*>::iterator BeginIter = Collisions.begin();
			std::list<GameEngineCollision*>::iterator EndIter = Collisions.end();

			for (; BeginIter != EndIter; )
			{
				GameEngineCollision* ReleaseCollision = *BeginIter;

				if (nullptr == ReleaseCollision)
				{
					GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
				}

				if (true == ReleaseCollision->IsDeath())
				{
					BeginIter = Collisions.erase(BeginIter);

					continue;
				}

				++BeginIter;

			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator ActorMapBeginIter = ActorList_.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator ActorMapEndIter = ActorList_.end();

		for (; ActorMapBeginIter != ActorMapEndIter; ++ActorMapBeginIter)
		{
			std::list<GameEngineActor*>& Actors = ActorMapBeginIter->second;

			std::list<GameEngineActor*>::iterator BeginIter = Actors.begin();
			std::list<GameEngineActor*>::iterator EndIter = Actors.end();

			for (; BeginIter != EndIter; )
			{
				GameEngineActor* ReleaseActor = *BeginIter;

				if (nullptr == ReleaseActor)
				{
					GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
				}

				ReleaseActor->ComponentRelease();


				if (true == ReleaseActor->IsDeath())
				{
					delete* BeginIter;
					*BeginIter = nullptr;

					BeginIter = Actors.erase(BeginIter);

					continue;
				}

				++BeginIter;
			}

		}
	}

}

// 	RendererList_[_Order].push_back(_Renderer);


void GameEngineLevel::LevelChangeStartEvent()
{

}

void GameEngineLevel::LevelChangeEndEvent()
{

}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _Group)
{
	CollisionList_[_Group].push_back(_Collision);
}

void GameEngineLevel::ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision)
{
	CollisionList_[_Collision->GetOrder()].remove(_Collision);

	_Collision->SetOrder(_Group);

	CollisionList_[_Collision->GetOrder()].push_back(_Collision);
}

void GameEngineLevel::PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type)
{
	MainCameraActor_->GetCamera()->PushDebugRender(_Transform, _Type);
}