#pragma once

// 설명 : 
class GameEngineReasterizer;
class GameEngineReasterizerManager
{
private:
	static GameEngineReasterizerManager* Inst;

public:
	static GameEngineReasterizerManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineReasterizer*> ResourcesMap;

public:
	// 직접 만들수 있다.
	GameEngineReasterizer* Create(const std::string& _Name);
	// 파일에서 로드
	GameEngineReasterizer* Load(const std::string& _Path);
	// 이름 직접 지정
	GameEngineReasterizer* Load(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
	GameEngineReasterizer* Find(const std::string& _Name);

private:
	GameEngineReasterizerManager(); // default constructer 디폴트 생성자
	~GameEngineReasterizerManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineReasterizerManager(const GameEngineReasterizerManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineReasterizerManager(GameEngineReasterizerManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineReasterizerManager& operator=(const GameEngineReasterizerManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineReasterizerManager& operator=(const GameEngineReasterizerManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자
};




