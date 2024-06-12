#include "Stage.h"
#include <iostream>
#include "world.h"


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
    channel = Audio::Play("data/audio/cancion_principal.wav", 0.2f, BASS_SAMPLE_LOOP);
    if (channel == 0)
    {
        std::cerr << "Failed to play audio: data/audio/cancion_principal.wav" << std::endl;
    }
}

void PlayStage::onExit()
{
    if (channel != 0)
    {
        Audio::Stop(channel);
    }
}

EndStage::EndStage()
{
}

void EndStage::render()
{
    //World::get_instance()->render();
    drawText(32, 32, "tas muerto", Vector3(200, 200, 50), 2);
}

void EndStage::update(double seconds_elapsed)
{
    World::get_instance()->update(seconds_elapsed);
    //World::get_instance()->end_game = false;

}

void EndStage::onEnter()
{
    //Init();
    float volume_death = 0.5f;
    muerte = Audio::Play("data/audio/muerte.wav", volume_death, false);
    if (muerte == 0)
    {
        std::cerr << "Failed to play audio: data/audio/muerte.wav" << std::endl;
    }
    volume_death = 0.0f;
}

void EndStage::onExit()
{
}

WinStage::WinStage()
{
}

void WinStage::render()
{
    drawText(32, 32, "Congrats You Finished Mountain Rush with x points.", Vector3(100, 100, 50), 2);
}

void WinStage::update(double seconds_elapsed)
{

}

void WinStage::onEnter()
{
    HCHANNEL win = Audio::Play("data/audio/Win.wav", 0.5, false);
    if (win == 0)
    {
        std::cerr << "Failed to play audio: data/audio/Win.wav" << std::endl;
    }
}

void WinStage::onExit()
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
