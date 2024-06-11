#include "Stage.h"
#include <iostream>
#include "world.h"
#include "framework/audio.h"

IntroStage::IntroStage()
{
    
}

void IntroStage::render()
{
	drawText(32, 32, "pulse R apra jugar", Vector3(100, 100, 50), 2);
}

void IntroStage::update(double seconds_elapsed)
{

}

void IntroStage::onEnter()
{
}

void IntroStage::onExit()
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
    World::get_instance()->end_game = false;

}

void PlayStage::onEnter()
{
    //Init();
    /*HCHANNEL channel = Audio::Play("data/audio/MarioAudio.wav", 0.5f, BASS_SAMPLE_LOOP);
    if (channel == 0)
    {
        std::cerr << "Failed to play audio: data/audio/MarioAudio.wav" << std::endl;
    }*/
}

void PlayStage::onExit()
{
}


void Stage::render()
{
}

void Stage::update(double seconds_elapsed)
{
}

void Stage::onEnter()
{
}

void Stage::onExit()
{
}
