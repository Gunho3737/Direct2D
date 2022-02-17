#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}


void GameEngineRenderer::Render()
{
	PipeLine_->Rendering();
}

void GameEngineRenderer::Start()
{
	GetLevel()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find("Color");

	if (true == PipeLine_->ShaderHelper.IsConstantBuffer("TransformData"))
	{
		PipeLine_->ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
	}

	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 파이프라인 입니다!");
	}
}