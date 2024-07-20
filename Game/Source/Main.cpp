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

		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}

/*
	std::vector<Particle> particles;
	float offset = 0;

	// actor
	Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };
	Scene* scene = new Scene();

	Transform transform{ Vector2{ 400, 300 }, 0, 3 };
	Player* player = new Player(800, transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene->AddActor(player);

	auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 0, 1 } };
	auto* enemy = new Enemy(400, Transform{ { g_engine.GetRenderer().GetWidth(),  g_engine.GetRenderer().GetHeight() }, 0, 2}, enemyModel);
	enemy->SetDamping(1.0f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);


	float spawnTimer = 2;


	// main loop
	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		// UPDATE
		scene->Update(g_engine.GetTime().GetDeltaTime());


		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPreviousMouseButtonDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3), (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0} );
			}		
		}

		for (Particle& particle : particles)
		{
			particle.Update(g_engine.GetTime().GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		// DRUM MACHINE
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)) g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_R) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_R)) g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_T) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_T)) g_engine.GetAudio().PlaySound("close-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Y) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Y)) g_engine.GetAudio().PlaySound("open-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) g_engine.GetAudio().PlaySound("clap.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W)) g_engine.GetAudio().PlaySound("cowbell.wav");

		
		// DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		float radius = 5;
		offset += (90 * g_engine.GetTime().GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 60)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			//float x = Math::Cos(Math::DegToRad(angle + offset)) * (radius + angle);
			//float y = Math::Sin(Math::DegToRad(angle + offset)) * (radius + angle);

			g_engine.GetRenderer().SetColor(random(256), random(256), random(256), 0);
			//renderer.DrawRect(400 + x, 300 + y, 10.0f, 10.0f);
		}

		// draw particles
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(g_engine.GetRenderer());
		}
		
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		
		scene->Draw(g_engine.GetRenderer());

		// show screen
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}
*/