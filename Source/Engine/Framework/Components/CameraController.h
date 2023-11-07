#pragma once
#include "Component.h"

namespace Jackster
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		bool Initialize() override;
		void Update(float dt) override;

	public:
		float sensitivity = 0.1f;
		float speed = 0;
		float yaw = 0;
		float pitch = 0;
	};
}