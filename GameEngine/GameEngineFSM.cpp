#include "PreCompile.h"
#include "GameEngineFSM.h"
#include <GameEngineBase\GameEngineDebug.h>

GameEngineFSM::GameEngineFSM()
	: Current_(nullptr)
	, Next_(nullptr)
{
}

GameEngineFSM::~GameEngineFSM()
{
	for (auto& State : AllState_)
	{
		delete State.second;
		State.second = nullptr;
	}
}

void GameEngineFSM::Update()
{
	if (nullptr != Next_)
	{
		if (nullptr != Current_ && nullptr != Current_->End_)
		{
			Current_->End_();
		}
		Current_ = Next_;

		if (nullptr != Current_->End_)
		{
			Current_->Start_();
		}
		Next_ = nullptr;
	}

	if (nullptr == Current_)
	{
		GameEngineDebug::MsgBoxError("���°� �������� �ʴµ� ���¸ӽ��� �۵���Ű���� �߽��ϴ�.");
		return;
	}

	Current_->Update_();
}

void GameEngineFSM::CreateState(
	const std::string& _Name,
	std::function<void()> _Update,
	std::function<void()> _Start /*= nullptr*/,
	std::function<void()> _EndStart /*= nullptr*/,
	std::function<void()> _Init /*= nullptr*/
)
{
	if (AllState_.end() != AllState_.find(_Name))
	{
		GameEngineDebug::MsgBoxError("�̹� �����ϴ� ������Ʈ�� �� ������� �߽��ϴ�.");
		return;
	}

	if (nullptr != _Init)
	{
		_Init();
	}

	AllState_.insert(std::map<std::string, State*>::value_type(_Name, new State{ _Start, _Update, _EndStart }));
}

void GameEngineFSM::ChangeState(const std::string& _Name)
{
	std::map<std::string, State*>::iterator FindIter = AllState_.find(_Name);

	if (AllState_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ������Ʈ�� ü�����Ϸ��� �߽��ϴ�..");
		return;
	}

	Next_ = FindIter->second;
}