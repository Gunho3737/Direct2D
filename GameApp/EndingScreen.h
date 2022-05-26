#pragma once
#include <GameEngine/GameEngineActor.h>


// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineSoundPlayer;
class EndingScreen : public GameEngineActor
{
private:	// member Var

public:
	EndingScreen(); // default constructer 디폴트 생성자
	~EndingScreen(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* ImageRenderer;

	static GameEngineSoundPlayer* EndingBackGroundPlayer;

protected:		// delete constructer
	EndingScreen(const EndingScreen& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EndingScreen(EndingScreen&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EndingScreen& operator=(const EndingScreen& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EndingScreen& operator=(const EndingScreen&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

