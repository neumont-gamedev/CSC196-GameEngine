#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	Time time;

	// add audio sounds
	//g_engine.GetAudio()->AddSound("bass.wav");
	//g_engine.GetAudio()->AddSound("snare.wav");
	//g_engine.GetAudio()->AddSound("close-hat.wav");
	//g_engine.GetAudio()->AddSound("open-hat.wav");
	//g_engine.GetAudio()->AddSound("clap.wav");
	//g_engine.GetAudio()->AddSound("cowbell.wav");

	std::vector<Particle> particles;
	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });

	Model model{ points, Color{ 1, 0, 0 } };
	Transform transform{ { g_engine.GetRenderer()->GetWidth() >> 1, g_engine.GetRenderer()->GetHeight() >> 1}, 0, 5};

	// main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();

		// INPUT
		g_engine.GetInput()->Update();
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		float thrust = 0;
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_UP))		thrust = 400;
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_DOWN))		thrust = -400;

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_LEFT))		transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_RIGHT))	transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)g_engine.GetRenderer()->GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)g_engine.GetRenderer()->GetHeight());

		// UPDATE
		Vector2 mousePosition = g_engine.GetInput()->GetMousePosition();
		if (g_engine.GetInput()->GetMouseButtonDown(0) && !g_engine.GetInput()->GetPreviousMouseButtonDown(0))
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

		// DRUM MACHINE
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_E)) g_engine.GetAudio()->PlaySound("bass.wav");
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_R) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_R)) g_engine.GetAudio()->PlaySound("snare.wav");
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_T) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_T)) g_engine.GetAudio()->PlaySound("close-hat.wav");
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_Y) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_Y)) g_engine.GetAudio()->PlaySound("open-hat.wav");
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_Q)) g_engine.GetAudio()->PlaySound("clap.wav");
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_W)) g_engine.GetAudio()->PlaySound("cowbell.wav");

		// DRAW
		// clear screen
		g_engine.GetRenderer()->SetColor(0, 0, 0, 0);
		g_engine.GetRenderer()->BeginFrame();

		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		float radius = 5;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 60)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.1f) * (radius + angle * 0.2f);
			//float x = Math::Cos(Math::DegToRad(angle + offset)) * (radius + angle);
			//float y = Math::Sin(Math::DegToRad(angle + offset)) * (radius + angle);

			g_engine.GetRenderer()->SetColor(random(256), random(256), random(256), 0);
			//renderer.DrawRect(400 + x, 300 + y, 10.0f, 10.0f);
		}

		// draw particles
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(*g_engine.GetRenderer());
		}
		
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		model.Draw(*g_engine.GetRenderer(), transform);


		// show screen
		g_engine.GetRenderer()->EndFrame();
	}

	return 0;
}
