#pragma once
#include "GameEnginePath.h"
// 분류 :
// 용도 :
// 설명 :

class GameEngineFile;
class GameEngineDirectroy : public GameEnginePath
{
public:
	GameEngineDirectroy(); // default constructer 디폴트 생성자
	~GameEngineDirectroy(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineDirectroy(const GameEngineDirectroy& _other); // default Copy constructer 디폴트 복사생성자
	GameEngineDirectroy(GameEngineDirectroy&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineDirectroy& operator=(const GameEngineDirectroy& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDirectroy& operator=(const GameEngineDirectroy&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	std::string DirectroyName();

public:		//member Func
	//C:\ 나 D:\ 와 같이 가장 기본 디렉터리인지 확인
	bool IsRoot();

	//상위 폴더로 이동
	void MoveParent();

	//상위 폴더중 _DirName라는 이름이 붙은 폴더로 이동
	bool MoveParent(const std::string& _DirName);

	//하위 폴더중 _DirName라는 이름이 붙은 폴더로 이동
	bool MoveChild(const std::string& _DirName);

public:
	std::string PathToPlusFileName(const std::string& _DirName);


	std::vector<GameEngineFile> GetAllFile(const std::string& _filter = "*");
};

