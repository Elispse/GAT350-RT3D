#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace Jackster
{
	CLASS_DEFINITION(EnginePhysicsComponent)

	void EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += velocity * dt;
		velocity *= std::pow(1.0f - damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		velocity += force;
	}

	void EnginePhysicsComponent::ApplyTorque(float torque)
	{
	}

	void EnginePhysicsComponent::Read(const json_t& value)
	{
		READ_DATA(value, damping);
	}

}
