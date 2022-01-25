#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineCore : public GameEngineObjectBase
{
private:
	void EngineInitialize();
	void EngineDestroy();

protected:
	GameEngineCore(); // default constructer 디폴트 생성자
	~GameEngineCore(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	static GameEngineCore* MainCore_;

private:
	static void WindowCreate();
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		// 신뢰의 릭.
#ifdef _DEBUG
		// 디버그때만 릭을 남길것이다.
		new int();
#endif
		WindowCreate();

		UserGameType NewUserGame;
		NewUserGame.EngineInitialize();
		NewUserGame.Initialize();
		NewUserGame.ResourcesLoad();

		MainCore_ = &NewUserGame;

		Loop();

		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;

public:
};

