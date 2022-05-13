#pragma once
#include <GameEngine/GameEngineActor.h>


// 분류 : 
// 용도 : 
// 설명 : 
class TitleScreen : public GameEngineActor
{
private:	// member Var

public:
	TitleScreen(); // default constructer 디폴트 생성자
	~TitleScreen(); // default destructer 디폴트 소멸자

	GameEngineImageRenderer* BackGroundImageRenderer;
	GameEngineImageRenderer* LogoImageRenderer;

protected:		// delete constructer
	TitleScreen(const TitleScreen& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleScreen(TitleScreen&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	TitleScreen& operator=(const TitleScreen& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleScreen& operator=(const TitleScreen&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

