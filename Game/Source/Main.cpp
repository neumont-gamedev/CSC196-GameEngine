#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

