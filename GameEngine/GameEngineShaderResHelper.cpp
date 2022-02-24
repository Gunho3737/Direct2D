#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineSampler.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"

GameEngineShaderResHelper::GameEngineShaderResHelper() 
{
}

GameEngineShaderResHelper::~GameEngineShaderResHelper() 
{

	for (auto& Setting : AllTextureData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllSamplerData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}

	for (auto& Setting : AllConstantBufferData_)
	{
		if (nullptr != Setting.second)
		{
			delete Setting.second;
			Setting.second = nullptr;
		}
	}
}

bool GameEngineShaderResHelper::IsConstantBuffer(const std::string& _SettingName)
{
	std::map<std::string, GameEngineConstantBufferSetting*>::iterator FindIter = AllConstantBufferData_.find(_SettingName);

	if (FindIter == AllConstantBufferData_.end())
	{
		return false;
	}

	return true;
}


void GameEngineShaderResHelper::ShaderResourcesCheck(GameEngineShader* _Shader) 
{
	// _Shader는 상수버퍼를 들고 있지
	// 이 상수버퍼를 각 플레이어나 몬스터가 세팅해줬는지 안했는지는 
	// GameEngineConstantBufferSetting이 가지게 됩니다.

	for (auto& ConstantBuffer : _Shader->GetConstantBuffers())
	{
		GameEngineConstantBufferSetting* SettingData = new GameEngineConstantBufferSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ConstantBuffer.second;
		SettingData->SettingIndex_ = ConstantBuffer.first;
		auto Result = AllConstantBufferData_.insert(std::make_pair(ConstantBuffer.second->GetName(), SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("같은 이름의 상수버퍼가 이미 존재합니다." + ConstantBuffer.second->GetName());
		}
	}

	for (auto& Sampler : _Shader->GetSamplers())
	{
		GameEngineSamplerSetting* SettingData = new GameEngineSamplerSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = Sampler.second;
		SettingData->SettingIndex_ = Sampler.first;
		auto Result = AllSamplerData_.insert(std::make_pair(Sampler.second->GetName(), SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("같은 이름의 샘플러가 이미 존재합니다." + Sampler.second->GetName());
		}
	}

	GameEngineTexture* ErrorTexture = GameEngineTextureManager::GetInst().Find("NotSettingError.png");

	for (auto& Texture : _Shader->GetTextures())
	{
		GameEngineTextureSetting* SettingData = new GameEngineTextureSetting();
		SettingData->Shader = _Shader;
		SettingData->Res_ = ErrorTexture;
		SettingData->SettingIndex_ = Texture.first;
		auto Result = AllTextureData_.insert(std::make_pair(Texture.second, SettingData));

		if (false == Result.second)
		{
			GameEngineDebug::MsgBoxError("같은 이름의 텍스처가 이미 존재합니다." + Texture.second);
		}
	}

}

void GameEngineShaderResHelper::Setting() 
{
	// 정보가 다 있으니까.
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("다음의 상수버퍼가 세팅되지 않았습니다. >>> " + Setting.first);
		}
		

		Setting.second->ChangeData();
		Setting.second->ShaderSetting();
	}

	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderSetting();
	}

	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderSetting();
	}

}

void GameEngineShaderResHelper::ReSet()
{
	for (auto& Setting : AllConstantBufferData_)
	{
		if (Setting.second->Mode_ == SettingMode::MAX)
		{
			GameEngineDebug::MsgBoxError("다음의 상수버퍼가 세팅되지 않았습니다. >>> " + Setting.first);
		}


		Setting.second->ChangeData();
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllTextureData_)
	{
		Setting.second->ShaderReSet();
	}

	for (auto& Setting : AllSamplerData_)
	{
		Setting.second->ShaderReSet();
	}

}

void GameEngineShaderResHelper::SettingTexture(const std::string& _SettingName, const std::string& _ImageName)
{
	std::map<std::string, GameEngineTextureSetting*>::iterator FindIter = AllTextureData_.find(_SettingName);

	if (FindIter == AllTextureData_.end())
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처 슬롯에 세팅하려고 했습니다." + _SettingName);
		return;
	}


	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처를 세팅하려고 했습니다. >>> " + _ImageName);
		return;
	}

	FindIter->second->Res_ = FindTexture;
}