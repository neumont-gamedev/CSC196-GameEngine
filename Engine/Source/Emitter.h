#pragma once
#include "Actor.h"
#include "Color.h"

class Emitter : public Actor
{
public:
	struct Data
	{
		// emission
		float spawnRate = 0;
		float spawnRateTimer = 0;
		bool burst = false;
		size_t burstCount = 0;

		// particle parameters
		float lifetimeMin = 0;
		float lifetimeMax = 0;
		float speedMin = 0;
		float speedMax = 0;
		float damping = 0;
		float angle = 0;
		float angleRange = 0;
		float size = 1;
		Color color;
	};

public:
	Emitter() = default;
	Emitter(const Transform& transform, const Data& data) :
		Actor{ transform },
		m_data{ data }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override {}

private:
	void Emit();

private:
	Data m_data;
};
