#pragma once
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderingPipeLineManager.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>

// 설명 :
class GameEnginePostProcessRender : public GameEngineObjectNameBase
{

public:
	inline void SetTarget(GameEngineRenderTarget* _Target)
	{
		Target_ = _Target;
	}

	inline void SetResult(GameEngineRenderTarget* _Result)
	{
		Result_ = _Result;
	}

	inline void SetEffect(std::string& _Effect)
	{
		Effect_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Effect);

		if (nullptr == Effect_)
		{
			GameEngineDebug::MsgBoxError("존재하지 않는 효과를 주려고 했습니다.");
			return;
		}
	}


	// constrcuter destructer
	GameEnginePostProcessRender();
	~GameEnginePostProcessRender();

	// delete Function
	GameEnginePostProcessRender(const GameEnginePostProcessRender& _Other) = delete;
	GameEnginePostProcessRender(GameEnginePostProcessRender&& _Other) noexcept = delete;
	GameEnginePostProcessRender& operator=(const GameEnginePostProcessRender& _Other) = delete;
	GameEnginePostProcessRender& operator=(GameEnginePostProcessRender&& _Other) noexcept = delete;

protected:
	virtual void Effect() = 0;


private:
	// 어떤 랜더타겟에 효과를 주고 싶다.
	GameEngineRenderTarget* Target_;
	// 주려는 효과는 이것이다.
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// 그 효과가 적용된 결과는 아래와 같다.
	GameEngineRenderTarget* Result_;


};

