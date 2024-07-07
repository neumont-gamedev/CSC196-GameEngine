#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"

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

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);


	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
	audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);


	std::vector<Particle> particles;


	// main loop
	bool quit = false;
	while (!quit)
	{
		audio->update();

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
				particles.push_back(Particle{ mousePosition, { randomf(-100, 100), randomf(-100, 100) }, randomf(1, 3), (uint8_t)random(255), (uint8_t)random(255), (uint8_t)random(255), 0 });
			}		
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) audio->playSound(sounds[0], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio->playSound(sounds[1], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio->playSound(sounds[2], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_R)) audio->playSound(sounds[3], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_T)) audio->playSound(sounds[4], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPreviousKeyDown(SDL_SCANCODE_Y)) audio->playSound(sounds[5], 0, false, nullptr);


		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// draw shape
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
