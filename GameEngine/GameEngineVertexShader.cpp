#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader() // default constructer 디폴트 생성자
	: VersionHigh_(5)
	, VersionLow_(0)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer 디폴트 소멸자
{
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
		LayOut_ = nullptr;
	}

	if (nullptr != CodeBlob_)
	{
		CodeBlob_->Release();
		CodeBlob_ = nullptr;
	}

}

bool GameEngineVertexShader::Create(
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion();

	return Compile();
}

void GameEngineVertexShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineVertexShader::CreateVersion()
{
	Version_ = "";
	Version_ += "vs_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineVertexShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineVertexShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

bool GameEngineVertexShader::Compile()
{

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 00000000 00000000 00000000 00000101

	// 행렬이 전치가 되서 들어가는것을 막아준다.
	// 전치가 기본이고 전치된걸 다시 
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// 결과물의 바이트코드

	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),
		Version_.c_str(),
		0,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	return true;
}

void GameEngineVertexShader::AddInputLayOut(
	const char* _SemanticName,
	unsigned int _Index,
	unsigned int _AlignedByteOffset,
	DXGI_FORMAT _Format,
	unsigned int _InputSlot,
	unsigned int _InstanceDataStepRate,
	D3D11_INPUT_CLASSIFICATION _inputClass
)
{
	SemanticName_.push_back(_SemanticName);

	D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0, };

	// https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics
	//                         "POSTION"
	LayOutDesc.SemanticName = _SemanticName;
	//                          0
	LayOutDesc.SemanticIndex = _Index;
	//                 DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayOutDesc.Format = _Format;
	//                        0 신경쓰지마
	LayOutDesc.InputSlot = _InputSlot;
	//                                  신경쓰지마
	LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	//                               16
	LayOutDesc.AlignedByteOffset = LayOutOffset_;

	//struct GameEngineVertex
	//{
	//public:
	//	// 포지션
	//	// 텍스처 비율
	//	float4 Postion1; POSTION 1 0
	//	float4 Postion0; POSTION 0 16
	//  float4 Postion2; POSTION 2 32 
	//	float4 Color; COLOR 0 48
	//}


	// 
}

void GameEngineVertexShader::CreateLayOut()
{
}

void GameEngineVertexShader::LayOutClear()
{
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
	}

	LayOut_ = nullptr;
	InputLayoutDesc_.clear();
	SemanticName_.clear();
	LayOutOffset_ = 0;
}