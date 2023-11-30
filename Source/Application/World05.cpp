#include "World05.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Framework/Components/RotateComponent.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace Jackster
{

	bool World05::Initialize()
	{
		m_scene = std::make_unique<Scene>();
		m_scene->Load("scenes/scene.json");
		m_scene->Initialize();

		return true;
	}

	void World05::Shutdown()
	{

	}

	void World05::Update(float dt)
	{
		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_time += dt;

		m_scene->Update(dt);
		m_scene->ProcessGui();
		
		/*
		auto actor = m_scene->GetActorByName<Actor>("ogre-refraction");
		actor->GetComponent<RotateComponent>()->Update(dt);

		auto material = actor->GetComponent<ModelComponent>()->material;

		material->ProcessGui();
		material->Bind();
		
		material = GET_RESOURCE(Material, "materials/refraction.mtrl");

		if (material)
		{
			ImGui::Begin("Refraction");
			ImGui::DragFloat("ior", &m_refraction, 0.1f, 1, 3);
			auto program = material->GetProgram();
			program->Use();
			program->SetUniform("ior", m_refraction);
			ImGui::End();
		}
		*/

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World05::Draw(Renderer& renderer)
	{
		// pre-render
		renderer.BeginFrame();
		// render
		m_scene->Draw(renderer);
		ENGINE.GetSystem<Gui>()->Draw();
		// post-render
		renderer.EndFrame();
	}
}