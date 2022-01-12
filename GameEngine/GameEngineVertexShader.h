#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>


// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineVertexShader : public GameEngineObjectNameBase
{
public:	// member Var
	std::function<float4(const float4& _Vertex)> VertexShaderFunction;

	// virtual float4 VertexShaderFunction(const float4& _Vertex);

public:
	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

