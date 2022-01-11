#include "PreCompile.h"
#include "GameEngineDirectroy.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

// Static Var
// Static Func

// constructer destructer
GameEngineDirectroy::GameEngineDirectroy()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectroy::GameEngineDirectroy(const GameEngineDirectroy& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectroy::~GameEngineDirectroy()
{
}

GameEngineDirectroy::GameEngineDirectroy(GameEngineDirectroy&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectroy::DirectroyName() 
{
	return path_.filename().string();
}

void GameEngineDirectroy::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectroy::IsRoot() 
{
	return path_.root_directory() == path_;
}

bool GameEngineDirectroy::MoveParent(const std::string& _DirName)
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


bool GameEngineDirectroy::MoveChild(const std::string& _DirName)
{
	path_.append(_DirName);
	//인자로 받은 폴더명과 같은 폴더로 이동

	if (false == IsExist())
	{
		//IsExixt로 존재여부를 확인
		GameEngineDebug::MsgBoxError("존재하지 않는 경로로 이동했습니다.");
		return false;
	}

	return true;
}

std::string GameEngineDirectroy::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);
	return NewPath.string();
}

//std::filesystem::directory_iterator를 사용하여 디렉토리의 파일 목록 가져 오기
//opendir / readdir 함수를 사용하여 디렉토리의 파일 목록 가져 오기
//std::filesystem::recursive_directory_iterator를 사용하여 모든 하위 디렉토리의 파일 목록을 가져옵니다

std::vector<GameEngineFile> GameEngineDirectroy::GetAllFile(const std::string& _filter /*= "*"*/)
{

	//벡터를 사용하는 GetAllFile
	std::string Filter = "";
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	Filter += _filter;

	GameEngineString::toupper(Filter);

	std::vector<GameEngineFile> Return;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	for (const std::filesystem::directory_entry& File : DirIter)
	{
		std::string Ext = File.path().extension().string();
		GameEngineString::toupper(Ext);

		if (_filter != "*" && Filter != Ext)
		{
			continue;
		}

		Return.push_back(GameEngineFile(File.path()));

	}


	return Return;
}