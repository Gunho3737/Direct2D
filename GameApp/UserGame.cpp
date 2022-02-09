#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



void UserGame::Initialize()
{

	return;
}

void UserGame::Release()
{

}

float4 vPos = { 0.0f, 0.0f , 0.0f };
float4 vRot = { 0.0f, 0.0f , 0.0f };
float4 vScale = { 1.0f, 1.0f , 1.0f };

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");
	float4x4 mScale;
	float4x4 mRot;
	float4x4 mPos;
	float4x4 mWorld;

	// 업데이트
	{
		mScale.Scaling(vScale);
		mRot.RotationDeg(vRot);
		mPos.Translation(vPos);

		mWorld = mScale * mRot * mPos;

		// Pipe.Setting("World", mWorld);
	}

	//  랜더링
	{
		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
}

