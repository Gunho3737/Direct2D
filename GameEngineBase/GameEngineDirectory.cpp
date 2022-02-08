#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

// Static Var
// Static Func

// constructer destructer
GameEngineDirectory::GameEngineDirectory()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectory::DirectroyName() 
{
	return path_.filename().string();
}

void GameEngineDirectory::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectory::IsRoot() 
{
	return path_.root_directory() == path_;
}

bool GameEngineDirectory::MoveParent(const std::string& _DirName)
{
	while (false == IsRoot())
	{
		if (path_.filename().string() == _DirName)
		{
			return true;
		}

		MoveParent();
	}
	return false;
}


bool GameEngineDirectory::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);
	//���ڷ� ���� ������� ���� ������ �̵�

	if (false == IsExist())
	{
		//IsExixt�� ���翩�θ� Ȯ��
		GameEngineDebug::MsgBoxError("�������� �ʴ� ��η� �̵��߽��ϴ�.");
		return false;
	}

	return true;
}

std::string GameEngineDirectory::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);
	return NewPath.string();
}

//std::filesystem::directory_iterator�� ����Ͽ� ���丮�� ���� ��� ���� ����
//opendir / readdir �Լ��� ����Ͽ� ���丮�� ���� ��� ���� ����
//std::filesystem::recursive_directory_iterator�� ����Ͽ� ��� ���� ���丮�� ���� ����� �����ɴϴ�

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string& _filter /*= "*"*/)
{
	//���͸� ����ϴ� GetAllFile

	//���� ���� Ȯ����(_filter)�� . �� �Ⱥپ� �ִٸ�, .�� �����ش�
	//npos = string::find()�� ������ �˻��ϴ� ���ڰ� ���ڿ��� ���ٸ� string::nops�� ������
	std::string Filter = "";
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	//���� Ȯ���ڸ��� ����
	Filter += _filter;

	//���� Ȯ���ڸ��� ���� �빮�ڷ� �ٲ��ش�
	GameEngineString::toupper(Filter);

	//ã�� Ư�� Ȯ������ ���ϸ��� ������ vector�� ����
	std::vector<GameEngineFile> Return;

	//path_�ּҿ� �ִ� ��� ���� ������ �������� directory_iterator
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	//��ȯ���Ѽ� Ȯ���ڰ� ��ġ�ϸ� vector�� pushback
	for (const std::filesystem::directory_entry& File : DirIter)
	{
		//������ Ȯ���ڸ� string���� �޾ƿ�
		std::string Ext = File.path().extension().string();

		//�� Ȯ���ڸ� ���� �빮�ڷ� ��ȯ
		GameEngineString::toupper(Ext);

	
		if (_filter != "*" && Filter != Ext)
		{
			continue;
		}

		//���� Ȯ���ڸ� �������� �ʾҰų�, ������ Ȯ���ڿ� ������ Ȯ���ڰ� ������ vector�� push_back
		Return.push_back(GameEngineFile(File.path()));

	}

	//���ϵ��� �̸��� ��� vector�� ����
	return Return;
}