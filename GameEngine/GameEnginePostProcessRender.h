#pragma once
#include "GameEngineRenderTarget.h"
#include "GameEngineRenderingPipeLineManager.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>

// ���� :
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
			GameEngineDebug::MsgBoxError("�������� �ʴ� ȿ���� �ַ��� �߽��ϴ�.");
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
	// � ����Ÿ�ٿ� ȿ���� �ְ� �ʹ�.
	GameEngineRenderTarget* Target_;
	// �ַ��� ȿ���� �̰��̴�.
	GameEngineRenderingPipeLine* Effect_;
	GameEngineShaderResHelper Res_;

	// �� ȿ���� ����� ����� �Ʒ��� ����.
	GameEngineRenderTarget* Result_;


};

