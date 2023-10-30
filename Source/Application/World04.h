#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace Jackster
{
	struct light_t
	{
		enum eType
		{
			Point,
			Directional,
			Spot
		};

		int type;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		float intensity;
		float range;
		float innerAngle;
		float outerAngle;
	};

	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		//light_t m_light;
		//light_t m_lights[3];
		std::vector<light_t> m_lights;
		int m_selected = 0;
		glm::vec3 m_ambientColor{ 0.4, 0.4, 0.4 };

		Transform m_transform;
		res_t<Model> m_model;
	};
}