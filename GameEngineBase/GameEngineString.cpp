#include "PreCompile.h"
#include "GameEngineString.h"

GameEngineString::GameEngineString() // default constructer 디폴트 생성자
{

}

GameEngineString::~GameEngineString() // default destructer 디폴트 소멸자
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



void GameEngineString::toupper(std::string& Text)
{
	//string 안에 들은 영문자를 전부 대문자로 변경시켜주는 함수
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);
}