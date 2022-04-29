#include "PreCompile.h"
#include "GameEngineResourcesManager.h"


#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer ����Ʈ ������
	: VertexBuffer_(nullptr)
	, InputLayOutVertexShader_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	SetOutputMergerBlend("AlphaBlend");
	SetRasterizer("EngineBaseRasterizer");
	SetOutputMergerDepthStencil("BaseDepthOn");
	SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{
	if (true == Rasterizer_->IsClone())
	{
		delete Rasterizer_;
		Rasterizer_ = nullptr;
	}


}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
	: VertexBuffer_(_other.VertexBuffer_)
	, VertexShader_(_other.VertexShader_)
	, IndexBuffer_(_other.IndexBuffer_)
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
{
	InputLayOutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayOutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	Topology_ = _Topology;
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);

	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �����Ͷ����� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader_ = GameEnginePixelShaderManager::GetInst().Find(_Name);

	if (nullptr == PixelShader_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� �ȼ� ���̴��� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend_ = GameEngineBlendManager::GetInst().Find(_Name);

	if (nullptr == Blend_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���带 ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

}

void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil_ = GameEngineDepthStencilManager::GetInst().Find(_Name);
	if (nullptr == DepthStencil_)
	{
		GameEngineDebug::MsgBoxError("�������� �ʴ� ���� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	VertexBuffer_->Setting();
	InputLayOutVertexShader_->InputLayOutSetting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	IndexBuffer_->Setting();
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology_);
}

void GameEngineRenderingPipeLine::VertexShader()
{
	VertexShader_->Setting();
}

void GameEngineRenderingPipeLine::Rasterizer()
{
	Rasterizer_->Setting();
	Rasterizer_->SettingViewPort();
}


void GameEngineRenderingPipeLine::PixelShader()
{
	PixelShader_->Setting();
}

void GameEngineRenderingPipeLine::OutPutMerger()
{
	Blend_->Setting();
	DepthStencil_->Setting();
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	// input����� �ܰ�
	InputAssembler1();

	InputAssembler2();

	VertexShader();

	Rasterizer();

	PixelShader();

	OutPutMerger();
}

void GameEngineRenderingPipeLine::Rendering()
{
	RenderingPipeLineSetting();

	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer_->GetIndexCount(), 0, 0);
}

void GameEngineRenderingPipeLine::InstanceRendering()
{
	// ���� �Ž��� ����
	// ���� ������ ������������ ����Ұǵ�.
	// ������� 
	RenderingPipeLineSetting();

	// GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer_->GetIndexCount(), 0, 0);
}

void GameEngineRenderingPipeLine::Reset()
{
	Blend_->Reset();
	DepthStencil_->Reset();
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Clone()
{
	GameEngineRenderingPipeLine* NewClone = new GameEngineRenderingPipeLine();

	NewClone->VertexBuffer_ = VertexBuffer_;
	NewClone->InputLayOutVertexShader_ = InputLayOutVertexShader_;
	NewClone->VertexShader_ = VertexShader_;
	NewClone->IndexBuffer_ = IndexBuffer_;
	NewClone->Topology_ = Topology_;
	NewClone->Rasterizer_ = Rasterizer_;
	NewClone->PixelShader_ = PixelShader_;
	NewClone->Blend_ = Blend_;
	NewClone->RenderTarget_ = RenderTarget_;
	NewClone->DepthStencil_ = DepthStencil_;
	NewClone->CloneOn();

	return NewClone;
}

void GameEngineRenderingPipeLine::RasterizerClone()
{
	Rasterizer_ = Rasterizer_->Clone();
}