#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"

GameEngineImageRenderer::GameEngineImageRenderer() 
{
}

GameEngineImageRenderer::~GameEngineImageRenderer() 
{
}

void GameEngineImageRenderer::Start() 
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName)
{
	ShaderHelper.SettingTexture("Tex", _ImageName);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, GameEngineTransform* _transform)
{
	SetImage(_ImageName);

	//1. 이미지의 사이즈를 float4로 받아옴
	//2. 렌더러의 transform을 받아서 내부에서 SetLocalScaling을 해줌
	float4 size = ShaderHelper.GetTextureSize(_ImageName);
	_transform->SetLocalScaling(size);
}