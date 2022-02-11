#pragma once
#include "GameEngineConstantBuffer.h"

enum SettingMode
{
	Link,
	New,
};



class GameEngineConstantBufferSetting
{
public:
	GameEngineConstantBuffer* Res_;
	SettingMode Mode_;
	char* SettingData_;
	int SettingIndex_;
	bool IsSet_;
};
