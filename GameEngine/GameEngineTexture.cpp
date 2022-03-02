#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineBase/GameEngineString.h"

#pragma comment(lib, "DirectXTex.lib")

GameEngineTexture::GameEngineTexture() // default constructer 디폴트 생성자
	: Texture2D_(nullptr)
	, RenderTargetView_(nullptr)
	, ShaderResourceViewPtr_(nullptr)
{

}

GameEngineTexture::~GameEngineTexture() // default destructer 디폴트 소멸자
{
	if (nullptr != ShaderResourceViewPtr_)
	{
		ShaderResourceViewPtr_->Release();
		ShaderResourceViewPtr_ = nullptr;
	}


	if (nullptr != RenderTargetView_)
	{
		RenderTargetView_->Release();
		RenderTargetView_ = nullptr;
	}

	if (nullptr != Texture2D_)
	{
		Texture2D_->Release();
		Texture2D_ = nullptr;
	}
}

void GameEngineTexture::Create(ID3D11Texture2D* _Texture2D)
{
	if (nullptr == _Texture2D)
	{
		GameEngineDebug::MsgBoxError("Texture Is null GameEngine Texture Create Error");
	}


	Texture2D_ = _Texture2D;
}


ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView_)
	{
		GameEngineDebug::MsgBoxError("RenderTargetView OverLap Create Error");
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D_, nullptr, &RenderTargetView_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return RenderTargetView_;
}


void GameEngineTexture::Load(const std::string& _Path)
{
	GameEngineFile NewFile = GameEngineFile(_Path);

	std::string Extension = NewFile.GetExtension();
	GameEngineString::toupper(Extension);

	// PNG 풍화설

	std::wstring wPath;
	GameEngineString::StringToWString(_Path, wPath);

	// PNG
	if (Extension == "TGA")
	{
		GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + Extension);
	}
	else if (Extension == "DDS")
	{
		GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + Extension);
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, Image_))
		{
			GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + _Path);
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(GameEngineDevice::GetDevice(),
		Image_.GetImages(),
		Image_.GetImageCount(),
		Image_.GetMetadata(), &ShaderResourceViewPtr_))
	{
		GameEngineDebug::MsgBoxError("쉐이더 리소스 뷰를 생성하는데 실패했습니다." + _Path);
	}

	TextureDesc_.Width = static_cast<unsigned int>(Image_.GetMetadata().width);
	TextureDesc_.Height = static_cast<unsigned int>(Image_.GetMetadata().height);
}

ID3D11RenderTargetView* GameEngineTexture::GetRenderTargetView()
{
	return RenderTargetView_;
}
ID3D11ShaderResourceView** GameEngineTexture::GetShaderResourcesView()
{
	return &ShaderResourceViewPtr_;
}

void GameEngineTexture::PushCutIndex(const float4& _Size, const float4& _Pos)
{
	float4 CutUv;

	CutUv.x = _Pos.x;
	CutUv.y = _Pos.y;

	CutUv.z = _Size.x;
	CutUv.w = _Size.y;

	CutList_.push_back(CutUv);
}

void GameEngineTexture::Cut(int _x, int _y)
{
	// UV값은 무조건
	// 1.0f 라고 봐야죠?
	// 

	// uv값으로서의 자름이 됩니다.
	for (int y = 0; y < _y; y++)
	{
		float4 CurStart;

		CurStart.z = 1.0f / _x;
		CurStart.w = 1.0f / _y;

		CurStart.y = CurStart.w * y;

		for (int x = 0; x < _x; x++)
		{
			CurStart.x = CurStart.z * x;
			CutList_.push_back(CurStart);
		}
	}

}


float4 GameEngineTexture::GetCutData(int _Index)
{
	if (0 == CutList_.size())
	{
		GameEngineDebug::MsgBoxError("자르지 않은 텍스처에서 인덱스를 얻어오려고 했습니다.");
	}

	if (_Index > CutList_.size())
	{
		GameEngineDebug::MsgBoxError("자른 개수에 비해서 인덱스가 너무 큽니다.");
	}

	return CutList_[_Index];
}

bool GameEngineTexture::IsCut()
{
	return CutList_.size() != 0;
}

float4 GameEngineTexture::GetImageSize()
{
	return { static_cast<float>(TextureDesc_.Width) , static_cast<float>(TextureDesc_.Height), 1.0f };
}