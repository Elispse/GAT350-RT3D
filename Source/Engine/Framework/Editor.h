#pragma once

namespace Jackster
{
	class Editor
	{
	public:
		void Update();
		void ProcessecGui(class Scene* scene);

	private:
		bool m_active = true;
		class Object* m_selected = nullptr;
	};
}