#include "PreCompile.h"

#include <conio.h>
#include <GameEngine/GameEngineCore.h>
#include "UserGame.h"


int main()
{
	GameEngineCore::Start<UserGame>();
}