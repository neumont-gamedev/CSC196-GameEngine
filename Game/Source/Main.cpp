#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"

#include <fmod.hpp>
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);
	
	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	float offset = 0;

	// main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		// INPUT
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		
		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), randomf(1, 3), (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0} );
			}		
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);
		float radius = 5;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 60)
		{
			//float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.01f) * (radius + angle * 0.2f);
			//float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.01f) * (radius + angle * 0.2f);
			float x = Math::Cos(Math::DegToRad(angle + offset)) * (radius + angle);
			float y = Math::Sin(Math::DegToRad(angle + offset)) * (radius + angle);

			renderer.SetColor(random(256), random(256), random(256), 0);
			renderer.DrawRect(400 + x, 300 + y, 10.0f, 10.0f);
		}

		// draw particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}
		
		// show screen
		renderer.EndFrame();
	}

	return 0;
}
