#include "PreCompile.h"
#include "GameEngineTransform.h"
#include "CameraComponent.h"
#include "GameEngineWindow.h"
#include "GameEngineRenderer.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexShader.h"

CameraComponent::CameraComponent()
	: ProjectionMode_(ProjectionMode::Perspective)
	, FovAngleY_(90.0f)
	, CamSize_(GameEngineWindow::GetInst().GetSize())
	, NearZ_(0.1f)
	, FarZ_(1000.0f)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start()
{
	DebugVector_.resize(1000);
	DebugRenderCount_ = 0;

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("DebugColorRect");

	for (size_t i = 0; i < DebugVector_.size(); i++)
	{
		DebugVector_[i].ShaderHelper.ShaderResourcesCheck(Pipe->GetVertexShader());
		DebugVector_[i].ShaderHelper.ShaderResourcesCheck(Pipe->GetPixelShader());
		DebugVector_[i].ShaderHelper.SettingConstantBufferLink("TransformData", DebugVector_[i].Data);
	}
}

void CameraComponent::Update(float _DeltaTime)
{
}

void CameraComponent::CameraTransformUpdate()
{
	GetTransform()->GetTransformData().View_.ViewToLH(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldForwardVector(), GetTransform()->GetWorldUpVector());

	switch (ProjectionMode_)
	{
	case ProjectionMode::Perspective:
		GetTransform()->GetTransformData().Projection_.PerspectiveFovLH(FovAngleY_, CamSize_.x, CamSize_.y, NearZ_, FarZ_);
		break;
	case ProjectionMode::Orthographic:
		GetTransform()->GetTransformData().Projection_.OrthographicLH(CamSize_.x, CamSize_.y, NearZ_, FarZ_);
		break;
	default:
		break;
	}
}

void CameraComponent::Render()
{
	CameraTransformUpdate();

	float4x4 View = GetTransform()->GetTransformData().View_;
	float4x4 Projection = GetTransform()->GetTransformData().Projection_;

	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->GetTransform()->GetTransformData().Projection_ = Projection;
			Renderer->GetTransform()->GetTransformData().View_ = View;
			Renderer->GetTransform()->GetTransformData().CalWVP();
			Renderer->Render();
		}
	}

}

void CameraComponent::PushRenderer(int _Order, GameEngineRenderer* _Renderer)
{
	RendererList_[_Order].push_back(_Renderer);

}

void CameraComponent::ReleaseRenderer()
{
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapBeginIter = RendererList_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapEndIter = RendererList_.end();


		for (; RenderMapBeginIter != RenderMapEndIter; ++RenderMapBeginIter)
		{
			std::list<GameEngineRenderer*>& Renderers = RenderMapBeginIter->second;

			std::list<GameEngineRenderer*>::iterator BeginIter = Renderers.begin();
			std::list<GameEngineRenderer*>::iterator EndIter = Renderers.end();

			for (; BeginIter != EndIter; )
			{
				GameEngineRenderer* ReleaseRenderer = *BeginIter;

				if (nullptr == ReleaseRenderer)
				{
					GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
				}

				if (true == ReleaseRenderer->IsDeath())
				{
					BeginIter = Renderers.erase(BeginIter);

					continue;
				}

				++BeginIter;

			}
		}
	}
}

void CameraComponent::ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer)
{
	RendererList_[_Renderer->GetOrder()].remove(_Renderer);

	_Renderer->SetOrder(_Group);

	RendererList_[_Renderer->GetOrder()].push_back(_Renderer);
}

void CameraComponent::DebugRender()
{
	//for (size_t i = 0; i < DebugRenderCount_; i++)
	//{
	//	DebugVector_[i].R
	//}

	DebugRenderCount_ = 0;

	// DebugVector_.clear();
}

void CameraComponent::PushDebug(GameEngineTransform* _Trans, CollisionType _Type)
{
	// DebugVector_[i].Data

	// GameEngineDebugRenderData NewData;

	switch (_Type)
	{
	case CollisionType::Point2D:
	case CollisionType::CirCle:
	case CollisionType::Rect:
	case CollisionType::OrientedRect:
		// DebugVector_.resize(DebugVector_.size() + 1);

		DebugVector_[DebugRenderCount_].Data = _Trans->GetTransformData();

		break;
	case CollisionType::Point3D:
	case CollisionType::Sphere3D:
	case CollisionType::AABBBox3D:
	case CollisionType::OBBBox3D:
	case CollisionType::MAX:
		GameEngineDebug::MsgBoxError("처리할수 없는 디버그 타입입니다.");
		break;
	default:
		break;
	}

	++DebugRenderCount_;
}