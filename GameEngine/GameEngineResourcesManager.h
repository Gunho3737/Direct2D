#pragma once
//GameEngine 안에서 절대 불러오지 말것. 순환참조 생김
//오직 GameEngineApp을 위한 매니저


#include <GameEngineBase/GameEngineSoundManager.h>
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineReasterizerManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineReasterizer.h"
#include "GameEngineTexture.h"


class GameEngineManagerHeler
{
public:
	static void ManagerRelease()
	{
		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineReasterizerManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineSoundManager::Destroy();
	}
};
