#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"
#include "GameEngineDebugRenderData.h"
#include "Enums.h"

enum class ProjectionMode
{
	Perspective,
	Orthographic
};

class PostProcess
{
public:
	GameEngineRenderTarget* OriginalTarget; // 효과를 주고 싶은 타겟이고
	GameEngineRenderingPipeLine* Effect;
	GameEngineRenderTarget* ResultTarget; // 효과를 받을 
};

// 설명 :
class GameEngineRenderer;
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	CameraComponent();
	~CameraComponent();
	CameraComponent(const CameraComponent& _Other) = delete;
	CameraComponent(CameraComponent&& _Other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _Other) = delete;
	CameraComponent& operator=(CameraComponent&& _Other) noexcept = delete;

	void SetProjectionMode(ProjectionMode _ProjectionMode)
	{
		ProjectionMode_ = _ProjectionMode;
	}

	void PushRenderer(int _Order, GameEngineRenderer* _Renderer);

	void PushDebugRender(GameEngineTransform* _Trans, CollisionType _Type);

	GameEngineRenderTarget* CameraBufferTarget_;

	void ChangeRendererGroup(int _Group, GameEngineRenderer* _Renderer);

	inline GameEngineRenderTarget* GetCameraRenderTarget()
	{
		return CameraBufferTarget_;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


	ProjectionMode ProjectionMode_;
	float FovAngleY_;
	float4 CamSize_;
	float NearZ_;
	float FarZ_;

	void ClearCameraTarget();

	void Render();
	void DebugRender();

	void ReleaseRenderer();

	void CameraTransformUpdate();

	std::map<int, std::list<GameEngineRenderer*>> RendererList_;
	// std::set<int> ZSort_;

	int DebugRenderCount_;
	std::vector<GameEngineDebugRenderData> DebugVector_;

	template<typename PostEffect>
	void AddPostProcessing(GameEngineRenderTarget* _ResultTarget, std::string _EffectName)
	{
		PostProcess NewEffect = PostProcess();
		NewEffect.OriginalTarget = CameraBufferTarget_;

		//if (_ResultTarget == BackBuffer)
		//{
		//}
	}

};

