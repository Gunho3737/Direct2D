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



struct TransformData
{
	float4x4 World;
	float4x4 View;
	float4x4 Proj;
};

TransformData TransData;

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	return;
}

void UserGame::Release()
{

}



void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//float4x4 mScale;
	//float4x4 mRot;
	//float4x4 mPos;
	//float4x4 mWorld;

	//// 업데이트
	//{
	//	mScale.Scaling(vScale);
	//	mRot.RotationDeg(vRot);
	//	mPos.Translation(vPos);

	//	mWorld = mScale * mRot * mPos;

	//	// Pipe.Setting("World", mWorld);
	//}

	//  랜더링
	{


		GameEngineDevice::RenderStart();
		Pipe->Rendering();
		GameEngineDevice::RenderEnd();
	}
}

