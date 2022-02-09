#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader()
	: VersionHigh_(5)
	, VersionLow_(0)
{
}

GameEngineShader::~GameEngineShader()
{
}


void GameEngineShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType)
{
	Version_ = "";
	Version_ += _ShaderType + "_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

void GameEngineShader::ResCheck()
{

	if (nullptr == CodeBlob_)
	{
		return;
	}

	// 내가 쉐이더에서 사용한 변수 함수들 인자들 그 이외의 상수버퍼등등등등의 모든
	// 정보를 알고 있는 녀석
	// 이 사람 쉐이더에서 행렬1개사용함
	ID3D11ShaderReflection* CompilInfo;

	if (S_OK != D3DReflect
	(
		CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(&CompilInfo)
	)
		)
	{
		// 뭔가 코드가 이상함.
		GameEngineDebug::MsgBoxError("쉐이더 컴파일 정보를 얻어오지 못했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info;
	CompilInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResInfo;

	for (unsigned int i = 0; i < Info.BoundResources; i++)
	{
		CompilInfo->GetResourceBindingDesc(i, &ResInfo);

		//LPCSTR                      Name;           // Name of the resource
		//D3D_SHADER_INPUT_TYPE       Type;           // Type of resource (e.g. texture, cbuffer, etc.)
		//UINT                        BindPoint;      // Starting bind point
		//UINT                        BindCount;      // Number of contiguous bind points (for arrays)
		//UINT                        uFlags;         // Input binding flags
		//D3D_RESOURCE_RETURN_TYPE    ReturnType;     // Return type (if texture) 
		//D3D_SRV_DIMENSION           Dimension;      // Dimension (if texture) // 3차원 텍스처
		//UINT                        NumSamples;     // Number of samples (0 if not MS texture)

		std::string Name = ResInfo.Name;
		unsigned int BindPoint = ResInfo.BindPoint;
		D3D_SHADER_INPUT_TYPE ResPoint = ResInfo.Type;

		switch (ResPoint)
		{
		case D3D_SIT_CBUFFER:
		{

		}
		break;
		default:
			break;
		}
	}
}