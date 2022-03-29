#pragma once

enum class CollisionType
{
	// 2D�� 3D���� �浹�� �ȵǰ� ����̴ϴ�.
	Point2D,
	CirCle,
	Rect,
	OrientedRect,

	Point3D,
	Sphere3D,
	AABBBox3D,
	OBBBox3D,
	MAX,
};

enum class RenderingOrder
{
	BackBuffer, // ����ۿ� ���� �׸��°�
	World,
	UI,
	Debug,
};

enum class ActorCollisionType
{
	PLAYER,
	ATTACK,
	MONSTER,
	MAP,
};

enum class LeftRight
{
	LEFT,
	RIGHT,
};

enum class MapProgress
{
	BENCH,
	MIDDLEROOM,
	MIDDLEBOSS,
	FINALBOSS,
};