#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineFolderTexture : public GameEngineObjectNameBase
{
public:
	void Load(const std::string& _Path);

	GameEngineFolderTexture();
	~GameEngineFolderTexture();

	GameEngineTexture* GetTextureIndex(int _Index);

	inline int GetTextureCount()
	{
		return static_cast<int>(AllTexture_.size());
	}

	//폴더안의 0번째 이미지의 사이즈를 가져오는 것
	//즉 폴더안의 이미지들끼리는 같은 크기여야 자연스럽다
	float4 GetTextureSize();


protected:		// delete constructer

private:		//delete operator
	GameEngineFolderTexture(const GameEngineFolderTexture& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineFolderTexture(GameEngineFolderTexture&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

	std::vector<GameEngineTexture*> AllTexture_;
};

