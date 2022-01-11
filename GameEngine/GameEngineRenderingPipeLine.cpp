#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer 디폴트 생성자
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(GameEngineVertexBuffer* _Ptr)
{
	VertexBuffer_ = _Ptr;
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Ptr)
{
	VertexShader_ = _Ptr;
}


void GameEngineRenderingPipeLine::Rendering()
{
	// input어셈블러 단계
	std::vector<float4> CopyVertex;
	{
		CopyVertex = VertexBuffer_->GetVertexs();
	}

	{
		for (size_t i = 0; i < CopyVertex.size(); i++)
		{
			CopyVertex[i] = VertexShader_->VertexShaderFunction(CopyVertex[i]);
		}

	}
}