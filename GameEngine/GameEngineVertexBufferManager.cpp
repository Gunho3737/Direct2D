#include "PreCompile.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBufferManager* GameEngineVertexBufferManager::Inst = new GameEngineVertexBufferManager();

GameEngineVertexBufferManager::GameEngineVertexBufferManager() // default constructer 디폴트 생성자
{

}

GameEngineVertexBufferManager::~GameEngineVertexBufferManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineVertexBuffer*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineVertexBufferManager::GameEngineVertexBufferManager(GameEngineVertexBufferManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEngineVertexBuffer* GameEngineVertexBufferManager::Create(const std::string& _Name, const std::vector<float4>& _Vertex)
{
	GameEngineVertexBuffer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		//이미 만든 도형인지 Find로 체크후 겹칠시에는 터트린다
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	//VerTexBuffer 생성
	GameEngineVertexBuffer* NewRes = new GameEngineVertexBuffer();

	//내가 넣어준 이름으로 이름을 넣어줌
	NewRes->SetName(_Name);

	//들어온 점의 좌표를
	//VertexBuffer가 자체적으로 들고 있는 vector에 넣는다
	NewRes->Create(_Vertex);

	// 그리고 뭘할거냐?

	//VertexManager에 있는 만들어진 리소스를 모아 둘 Map에 이름과 같이 저장
	ResourcesMap.insert(std::map<std::string, GameEngineVertexBuffer*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineVertexBuffer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineVertexBuffer* NewRes = new GameEngineVertexBuffer();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEngineVertexBuffer*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineVertexBuffer*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}