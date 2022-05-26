#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 
// 용도 : 
// 설명 : 
class EndingLevel : public GameEngineLevel
{
private:	// member Var

public:
	EndingLevel(); // default constructer 디폴트 생성자
	~EndingLevel(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	EndingLevel(const EndingLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	EndingLevel(EndingLevel&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	EndingLevel& operator=(const EndingLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	EndingLevel& operator=(const EndingLevel&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

	void FadeOn() override;
	void FadeOff() override;

	class PostFade* FadeEffect;
};

