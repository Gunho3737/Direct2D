#pragma once
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

enum class SettingMode
{
	Link,
	Set,
	MAX,
};



class GameEngineShader;
class GameEngineConstantBuffer;
class GameEngineConstantBufferSetting
{
public:
	GameEngineShader* Shader;
	GameEngineConstantBuffer* Res_;
	SettingMode Mode_;
	char* SettingData_;
	size_t SettingDataSize_;
	int SettingIndex_;

public:
	void Clear() 
	{
		if (SettingMode::Set == Mode_)
		{
			if (nullptr != SettingData_)
			{
				delete SettingData_;
				SettingData_ = nullptr;
			}
		}
	}

	void ChangeData() 
	{
		Res_->ChangeData(SettingData_, SettingDataSize_);
	}

	void ShaderSetting()
	{
		Shader->SetConstantBuffers(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetConstantBuffers(this);
	}

public:
	GameEngineConstantBufferSetting()
		: SettingData_(nullptr)
		, Mode_(SettingMode::MAX)
	{

	}

	~GameEngineConstantBufferSetting() 
	{
		Clear();
	}
};


class GameEngineShader;
class GameEngineSampler;
class GameEngineSamplerSetting
{
public:
	GameEngineShader* Shader;
	GameEngineSampler* Res_;
	int SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader->SetSampler(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetSampler(this);
	}

public:
	GameEngineSamplerSetting()
		: Res_(nullptr)
	{

	}

	~GameEngineSamplerSetting()
	{
	}
};

class GameEngineShader;
class GameEngineTexture;
class GameEngineTextureSetting
{
public:
	GameEngineShader* Shader;
	GameEngineTexture* Res_;
	int SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader->SetTexture(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetTexture(this);
	}

public:
	GameEngineTextureSetting()
		: Res_(nullptr)
	{

	}

	~GameEngineTextureSetting()
	{
	}
};