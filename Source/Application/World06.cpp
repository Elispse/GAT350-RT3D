#include "World06.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace Jackster
{

	bool World06::Initialize()
	{
		m_scene = std::make_unique<Scene>();
		m_scene->Load("Scenes/scene_FrameBuffer.json");
		m_scene->Initialize();

		auto texture = std::make_shared<Texture>();
		texture->CreateTexture(2048, 2048);
		ADD_RESOURCE("fb_texture", texture);

		auto framebuffer = std::make_shared<Framebuffer>();
		framebuffer->CreateFrameBuffer(texture);
		ADD_RESOURCE("fb", framebuffer);

		auto material = GET_RESOURCE(Material, "materials/postprocess.mtrl");
		if (material)
		{
			material->albedoTexture = texture;
		}

		return true;
	}

	void World06::Shutdown()
	{
	}

	void World06::Update(float dt)
	{
		m_time += dt;

		ENGINE.GetSystem<Gui>()->BeginFrame();

		m_scene->Update(dt);
		m_scene->ProcessGui();

		// set post process gui
		ImGui::Begin("PostProcess");
		ImGui::SliderFloat("blend", &m_blend, 0, 1);

		// checkbox and controls for invert
		bool effect = m_params & INVERT_MASK;
		if (ImGui::Checkbox("Invert", &effect))
		{
			(effect) ? m_params |= INVERT_MASK : m_params &= ~INVERT_MASK;
		}

		// checkbox and controls for grayscale
		effect = m_params & GRAYSCALE_MASK;
		if (ImGui::Checkbox("GrayScale", &effect))
		{
			(effect) ? m_params |= GRAYSCALE_MASK : m_params &= ~GRAYSCALE_MASK;
		}
		
		// checkbox and controls for colortint
		effect = m_params & COLORTINT_MASK;
		if (ImGui::Checkbox("Color Tint", &effect))
		{
			(effect) ? m_params |= COLORTINT_MASK : m_params &= ~COLORTINT_MASK;
		}
		if (effect)
		{
			ImGui::ColorEdit3("Color Tint", glm::value_ptr(m_tint));
		}

		// checkbox and controls for grain
		effect = m_params & GRAIN_MASK;
		if (ImGui::Checkbox("Grain", &effect))
		{
			(effect) ? m_params |= GRAIN_MASK : m_params &= ~GRAIN_MASK;
		}

		// checkbox and controls for scanline
		effect = m_params & SCANLINE_MASK;
		if (ImGui::Checkbox("SCANLINE", &effect))
		{
			(effect) ? m_params |= SCANLINE_MASK : m_params &= ~SCANLINE_MASK;
		}

		effect = m_params & BLUR_MASK;
		if (ImGui::Checkbox("Kernel", &effect))
		{
			(effect) ? m_params |= BLUR_MASK : m_params &= ~BLUR_MASK;
		}
		ImGui::End();

		// set postprocess shader
		auto program = GET_RESOURCE(Program, "shaders/postprocess.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("blend", m_blend);
			program->SetUniform("params", m_params);
			program->SetUniform("tint", m_tint);
		}

		ENGINE.GetSystem<Gui>()->EndFrame();
	}

	void World06::Draw(Renderer& renderer)
	{
		// *** PASS 1 ***
		m_scene->GetActorByName("postprocess")->active = false;

		auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
		renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		// pre-render
		renderer.BeginFrame({ 0, 0, 1 });
		// render
		m_scene->Draw(renderer);

		framebuffer->Unbind();
		
		// *** PASS 2 ***
		m_scene->GetActorByName("postprocess")->active = true;

		renderer.ResetViewport();
		renderer.BeginFrame();
		m_scene->GetActorByName("postprocess")->Draw(renderer);
		// post-render
		ENGINE.GetSystem<Gui>()->Draw();
		renderer.EndFrame();
	}
}