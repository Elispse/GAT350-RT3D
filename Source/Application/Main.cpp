#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "World06.h"
#include "World07.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...")

	Jackster::seedRandom((unsigned int)time(nullptr));
	Jackster::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<Jackster::World05>();
	world->Initialize();

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<Jackster::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
