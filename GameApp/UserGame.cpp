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

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };


void UserGame::Release() 
{
	
}

void UserGame::GameLoop()
{
	//실제 게임이 돌아가는 루프

	GameEngineDevice::RenderStart();

	//GameEngineRenderingPipeLine Pipe;
	//
	//Pipe.SetInputAssembler1("Rect"); //버텍스버퍼-> 기본도형이 될 정점들 생성
	//Pipe.SetVertexShader("TestShader"); //버텍스쉐이더 -> 버텍스 버퍼로 받은 정점들을 변형시킨다
	//Pipe.SetInputAssembler2("Rect"); // 인덱스버퍼->변형이 된점들을 이용해 삼각형을 기반으로한 면을 만듬
	//Pipe.SetRasterizer("TestReasterizer"); //레스터라이저 -> 뷰포트를 곱해서 실제 화면에 나오는 것처럼 변형
	//
	//RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();
	//BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//
	//Pipe.Rendering();
	
	GameEngineDevice::RenderEnd();

}