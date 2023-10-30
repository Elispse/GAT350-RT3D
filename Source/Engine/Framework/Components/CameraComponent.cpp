#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace Jackster
{
	CLASS_DEFINITION(CameraComponent)

	bool CameraComponent::Initialize()
	{
		// get aspect from window if not set
		if (aspect == 0)
		{
			// set aspect with renderer width / renderer height (make sure it is a floating point division)
			// aspect = width / height;
			aspect = static_cast<float>(Renderer().GetWidth() / Renderer().GetHeight());
		}

		return true;
	}

	void CameraComponent::Update(float dt)
	{
		// set view matrix with glm::lookAt function, use owner position
		// view = glm::lookAt(<owner transform position>, <owner transform position + owner transform forward>, <up vector>);
		// set projection matrix with glm::perspective function (fov is in degrees, convert to radians)
		// projection = glm::perspective(<parameters>);
		//view = glm::lookAt();
	}

	void CameraComponent::SetPerspective(float fov, float aspect, float near, float far)
	{
		// set this class fov, aspect, near and far values with parameters (this->fov = fov, ...)
		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		// set projection matrix with glm::perspective function (fov is in degrees, convert to radians)
		// projection = glm::perspective(<parameters>);
		projection = glm::perspective(DegreesToRadians(this->fov), this->aspect, this->near, this->far);
	}

	void CameraComponent::SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		// set view matrix with glm::lookAt function
		// view = glm::lookAt(<parameters>)
		view = glm::lookAt(eye, center, up);
	}

	void CameraComponent::SetProgram(res_t<Program> program)
	{
		// set program uniform for "view" with view matrix
		// set program uniform for "projection" with projection matrix
		program->SetUniform("view", view);
		program->SetUniform("projection", projection);
	}

	void CameraComponent::ProcessGui()
	{
		// use ImGui::DragFloat to set fov, aspect, near and far values (use speed of 0.1f)
	}

	void CameraComponent::Read(const json_t& value)
	{
		// READ_DATA of fov, aspect, near and far values
	}
}