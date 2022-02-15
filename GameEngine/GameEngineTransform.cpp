#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform() 
{
}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	//if (nullptr == _Child)
	//{
	//	GameEngineDebug::
	//}
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent) 
{
	if (nullptr == _Parent)
	{
	}

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
		// 기존 부모에게서 떨어져서 다른 부모에게로 옮겨가야 하므로
		// 현재 자신의 부모에서는 떨어져나가야 한다.
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}