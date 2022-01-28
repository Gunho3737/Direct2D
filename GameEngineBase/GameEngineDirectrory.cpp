#include "PreCompile.h"
#include "GameEngineDirectrory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

// Static Var
// Static Func

// constructer destructer
GameEngineDirectrory::GameEngineDirectrory()
{
	path_ = std::filesystem::current_path();
}

GameEngineDirectrory::GameEngineDirectrory(const GameEngineDirectrory& _other)
	: GameEnginePath(_other)
{

}

GameEngineDirectrory::~GameEngineDirectrory()
{
}

GameEngineDirectrory::GameEngineDirectrory(GameEngineDirectrory&& _other) noexcept
{
}

//member Func

std::string GameEngineDirectrory::DirectroyName() 
{
	return path_.filename().string();
}

void GameEngineDirectrory::MoveParent() 
{
	path_ = path_.parent_path();
}

bool GameEngineDirectrory::IsRoot() 
{
	return path_.root_directory() == path_;
}

bool GameEngineDirectrory::MoveParent(const std::string& _DirName)
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


bool GameEngineDirectrory::MoveChild(const std::string& _DirName)
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

std::string GameEngineDirectrory::PathToPlusFileName(const std::string& _FileName)
{
	std::filesystem::path NewPath = path_;
	NewPath.append(_FileName);
	return NewPath.string();
}

//std::filesystem::directory_iterator를 사용하여 디렉토리의 파일 목록 가져 오기
//opendir / readdir 함수를 사용하여 디렉토리의 파일 목록 가져 오기
//std::filesystem::recursive_directory_iterator를 사용하여 모든 하위 디렉토리의 파일 목록을 가져옵니다

std::vector<GameEngineFile> GameEngineDirectrory::GetAllFile(const std::string& _filter /*= "*"*/)
{
	//벡터를 사용하는 GetAllFile

	//만약 들어온 확장자(_filter)에 . 이 안붙어 있다면, .을 붙혀준다
	//npos = string::find()을 했을때 검색하는 문자가 문자열에 없다면 string::nops를 리턴함
	std::string Filter = "";
	if (std::string::npos == _filter.find('.'))
	{
		Filter = ".";
	}

	//들어온 확장자명을 받음
	Filter += _filter;

	//들어온 확장자명을 전부 대문자로 바꿔준다
	GameEngineString::toupper(Filter);

	//찾은 특정 확장자의 파일명을 저장할 vector를 생성
	std::vector<GameEngineFile> Return;

	//path_주소에 있는 모든 파일 정보를 가져오는 directory_iterator
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(path_);

	//순환시켜서 확장자가 일치하면 vector에 pushback
	for (const std::filesystem::directory_entry& File : DirIter)
	{
		//파일의 확장자를 string으로 받아옴
		std::string Ext = File.path().extension().string();

		//그 확장자를 전부 대문자로 전환
		GameEngineString::toupper(Ext);

	
		if (_filter != "*" && Filter != Ext)
		{
			continue;
		}

		//내가 확장자를 지정하지 않았거나, 지정한 확장자와 파일의 확장자가 같으면 vector에 push_back
		Return.push_back(GameEngineFile(File.path()));

	}

	//파일들의 이름이 담긴 vector를 리턴
	return Return;
}