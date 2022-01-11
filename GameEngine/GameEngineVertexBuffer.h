#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineVertexBuffer
{
private:	// member Var
	std::vector<float4> Vertexs_;

public:
	const std::vector<float4>& GetVertexs();

public:
	GameEngineVertexBuffer(); // default constructer 디폴트 생성자
	~GameEngineVertexBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

