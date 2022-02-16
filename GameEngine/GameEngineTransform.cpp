#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::TransformUpdate()
{
	TransData_.LocalCalculation();

	// TransData_.LocalWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	// TransData_.WorldWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	if (nullptr != Parent_)
	{
		TransData_.ParentSetting(Parent_->TransData_.WorldWorld_);
	}
	else {
		TransData_.RootCalculation();
	}

}

void GameEngineTransform::AllChildCalculationScaling()
{
	for (auto& Child : Childs_)
	{
		// �θ��� ũ�Ⱑ �ٲ���̰� �θ��� ũ�Ⱑ �ٲ���ٴ°���
		// �ڽ��� ���� �������� �ٲ���ٴ°��� �ǹ��Ѵ�.
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();
		Child->AllChildCalculationPosition();
	}
}

void GameEngineTransform::CalculationWorldScaling()
{
	TransData_.vWorldScaling_ = Parent_->TransData_.vWorldScaling_ * TransData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalScaling()
{
	TransData_.vLocalScaling_ = TransData_.vWorldScaling_ / Parent_->TransData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	TransData_.vWorldRotation_ = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	TransData_.vLocalRotation_ = TransData_.vWorldRotation_ - Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// TransData_.v = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}


void GameEngineTransform::CalculationWorldPosition()
{
	// �������������� ���� ������ ��
	float4 CalLocalPos = TransData_.vLocalPosition_;

	// ũ�⸦ Ű���
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// ȸ����Ű��
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// �θ��� ��ġ�� �̵��Ѱ�
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	TransData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransData_.vLocalScaling_ = _Value;
	CalculationWorldScaling();
	AllChildCalculationScaling();
}



void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransData_.vWorldScaling_ = _Value;
	CalculationLocalScaling();
	AllChildCalculationScaling();
}

// ����� ��׸�
void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vLocalRotation_ = _Value;
	CalculationWorldRotation();
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();
}


void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalPosition_ = _Value;
		TransData_.vLocalPosition_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value) {

}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	Childs_.remove(_Child);
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	// ���� �������� _Parent�� ����ٳ�� �մϴ�.

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}