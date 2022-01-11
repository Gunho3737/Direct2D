#pragma once
#include <GameEngineBase/GameEngineMath.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRenderingPipeLine
{
private:	// member Var
	std::vector<float4> CopyVertex;

public:
	void SetInputAssembler1(GameEngineVertexBuffer* _Ptr);
	// void SetVertexShader(GameEngineVertexShader* _Vertex);

	void OutPutMerger();

public:
	GameEngineRenderingPipeLine(); // default constructer ����Ʈ ������
	~GameEngineRenderingPipeLine(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
};

