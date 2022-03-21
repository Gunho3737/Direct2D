#include "Precompile.h"
#include "UserGame_Resources_Shader.h"

void AppShaderLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParent("Direct2D");
	Dir.MoveChild("Resources");
}