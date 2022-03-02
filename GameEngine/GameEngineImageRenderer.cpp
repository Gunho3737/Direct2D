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

	//1. �̹����� ����� float4�� �޾ƿ�
	//2. �������� transform�� �޾Ƽ� ���ο��� SetLocalScaling�� ����
	float4 size = ShaderHelper.GetTextureSize(_ImageName);
	_transform->SetLocalScaling(size);
}