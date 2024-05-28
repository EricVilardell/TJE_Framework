#include "Stage.h"
#include <iostream>
#include "world.h"

IntroStage::IntroStage()
{
}

void IntroStage::render()
{
	drawText(32, 32, "pulse espacio apra jugar", Vector3(50, 50, 50), 2);

}

void IntroStage::update(double seconds_elapsed)
{

}

PlayStage::PlayStage()
{
}

void PlayStage::render()
{
	World::get_instance()->render();
}

void PlayStage::update(double seconds_elapsed)
{
	World::get_instance()->update(seconds_elapsed);
}

void Stage::render()
{
}

void Stage::update(double seconds_elapsed)
{
}
