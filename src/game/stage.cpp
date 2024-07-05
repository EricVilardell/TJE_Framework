#include "Stage.h"
#include <iostream>
#include "world.h"
#include "framework/entities/entityPlayer.h"
#include "framework/entities/EntityUI.h"

EntityUI* background_intro;
EntityUI* background_lost;
EntityUI* background_won;
EntityUI* play_button;
EntityUI* play_button_win;
EntityUI* exit_button;
EntityUI* exit_button_win;

IntroStage::IntroStage()
{
    int width = Game::instance->window_width;
    int height = Game::instance->window_height;

    Material background_mat;
    background_mat.diffuse = Texture::Get("data/textures/background_intro.png");
    background_intro = new EntityUI(Vector2(width, height), Vector2(width, height), background_mat, "background");
    Material play_mat;
    play_mat.diffuse = Texture::Get("data/textures/playbutton.png");
    play_button = new EntityUI(Vector2(width - 250, 750), Vector2(240, 240), play_mat, "play");
    Material exit_mat;
    exit_mat.diffuse = Texture::Get("data/textures/exitbutton.png");
    exit_button = new EntityUI(Vector2(width + 250, 750), Vector2(200, 200), exit_mat, "exit");

    std::cout << (play_button->position.x - play_button->size.x) * 0.5f << std::endl;
    std::cout << (play_button->position.x + play_button->size.x) * 0.5f << std::endl;

    std::cout << (play_button->position.y - play_button->size.y) * 0.5f << std::endl;
    std::cout << (play_button->position.y + play_button->size.y) * 0.5f << std::endl;
}

void IntroStage::render()
{
    background_intro->render(World::get_instance()->camera2d);
    play_button->render(World::get_instance()->camera2d);
    exit_button->render(World::get_instance()->camera2d);

}

void IntroStage::update(double seconds_elapsed)
{
    Vector2 mouse_pos = Input::mouse_position;

    if (mouse_pos.x > ((play_button->position.x - play_button->size.x) * 0.5f) &&
        mouse_pos.x< ((play_button->position.x + play_button->size.x) * 0.5f) &&
        mouse_pos.y >((play_button->position.y - play_button->size.y) * 0.5f) &&
        mouse_pos.y < ((play_button->position.y + play_button->size.y) * 0.5f)) {
        play_button->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->moveToStage(Game::instance->play_stage);
        }
    }
    else {
        play_button->material.color = Vector4::WHITE;
    }
    if (mouse_pos.x > ((exit_button->position.x - exit_button->size.x) * 0.5f) &&
        mouse_pos.x< ((exit_button->position.x + exit_button->size.x) * 0.5f) &&
        mouse_pos.y >((exit_button->position.y - exit_button->size.y) * 0.5f) &&
        mouse_pos.y < ((exit_button->position.y + exit_button->size.y) * 0.5f)) {
        exit_button->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->must_exit = true;
        }
    }
    else {
        exit_button->material.color = Vector4::WHITE;
    }
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
    World::get_instance()->player->points = 0.0f;
    World::get_instance()->player->model.setTranslation(383.f, 330.f, 0.f);
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
    int width = Game::instance->window_width;
    int height = Game::instance->window_height;

    Material background_mat_lost;
    background_mat_lost.diffuse = Texture::Get("data/textures/background_lost.png");
    background_lost = new EntityUI(Vector2(width, height), Vector2(width, height), background_mat_lost, "background");
    Material play_mat;
    play_mat.diffuse = Texture::Get("data/textures/playbutton.png");
    play_button = new EntityUI(Vector2(width - 250, 750), Vector2(240, 240), play_mat, "play");
    Material exit_mat;
    exit_mat.diffuse = Texture::Get("data/textures/exitbutton.png");
    exit_button = new EntityUI(Vector2(width + 250, 750), Vector2(200, 200), exit_mat, "exit");

    std::cout << (play_button->position.x - play_button->size.x) * 0.5f << std::endl;
    std::cout << (play_button->position.x + play_button->size.x) * 0.5f << std::endl;

    std::cout << (play_button->position.y - play_button->size.y) * 0.5f << std::endl;
    std::cout << (play_button->position.y + play_button->size.y) * 0.5f << std::endl;
}

void EndStage::render()
{
    background_lost->render(World::get_instance()->camera2d);
    play_button->render(World::get_instance()->camera2d);
    exit_button->render(World::get_instance()->camera2d);
}

void EndStage::update(double seconds_elapsed)
{
    Vector2 mouse_pos = Input::mouse_position;

    if (mouse_pos.x > ((play_button->position.x - play_button->size.x) * 0.5f) &&
        mouse_pos.x< ((play_button->position.x + play_button->size.x) * 0.5f) &&
        mouse_pos.y >((play_button->position.y - play_button->size.y) * 0.5f) &&
        mouse_pos.y < ((play_button->position.y + play_button->size.y) * 0.5f)) {
        play_button->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->moveToStage(Game::instance->play_stage);
        }
    }
    else {
        play_button->material.color = Vector4::WHITE;
    }
    if (mouse_pos.x > ((exit_button->position.x - exit_button->size.x) * 0.5f) &&
        mouse_pos.x< ((exit_button->position.x + exit_button->size.x) * 0.5f) &&
        mouse_pos.y >((exit_button->position.y - exit_button->size.y) * 0.5f) &&
        mouse_pos.y < ((exit_button->position.y + exit_button->size.y) * 0.5f)) {
        exit_button->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->must_exit = true;
        }
    }
    else {
        exit_button->material.color = Vector4::WHITE;
    }
    World::get_instance()->update(seconds_elapsed);

}

void EndStage::onEnter()
{
    //Init();
    float volume_death = 0.5f;
    HCHANNEL muerte = Audio::Play("data/audio/muerte.wav", volume_death, false);
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
    int width = Game::instance->window_width;
    int height = Game::instance->window_height;

    Material background_mat;
    background_mat.diffuse = Texture::Get("data/textures/background_won.png");
    background_won = new EntityUI(Vector2(width, height), Vector2(width, height), background_mat, "background");
    Material play_mat;
    play_mat.diffuse = Texture::Get("data/textures/playbutton.png");
    play_button_win = new EntityUI(Vector2(width - 250, 950), Vector2(240, 240), play_mat, "play");
    Material exit_mat;
    exit_mat.diffuse = Texture::Get("data/textures/exitbutton.png");
    exit_button_win = new EntityUI(Vector2(width + 250, 950), Vector2(175, 175), exit_mat, "exit");

    std::cout << (play_button->position.x - play_button->size.x) * 0.5f << std::endl;
    std::cout << (play_button->position.x + play_button->size.x) * 0.5f << std::endl;

    std::cout << (play_button->position.y - play_button->size.y) * 0.5f << std::endl;
    std::cout << (play_button->position.y + play_button->size.y) * 0.5f << std::endl;
}

void WinStage::render()
{
    std::string message = std::to_string(World::get_instance()->player->points);
    background_won->render(World::get_instance()->camera2d);
    play_button_win->render(World::get_instance()->camera2d);
    exit_button_win->render(World::get_instance()->camera2d);
    drawText(400, 215, message, Vector3(100, 100, 50), 7);
}

void WinStage::update(double seconds_elapsed)
{
    Vector2 mouse_pos = Input::mouse_position;

    if (mouse_pos.x > ((play_button_win->position.x - play_button_win->size.x) * 0.5f) &&
        mouse_pos.x< ((play_button_win->position.x + play_button_win->size.x) * 0.5f) &&
        mouse_pos.y >((play_button_win->position.y - play_button_win->size.y) * 0.5f) &&
        mouse_pos.y < ((play_button_win->position.y + play_button_win->size.y) * 0.5f)) {
        play_button_win->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->moveToStage(Game::instance->play_stage);
        }
    }
    else {
        play_button_win->material.color = Vector4::WHITE;
    }
    if (mouse_pos.x > ((exit_button_win->position.x - exit_button_win->size.x) * 0.5f) &&
        mouse_pos.x< ((exit_button_win->position.x + exit_button_win->size.x) * 0.5f) &&
        mouse_pos.y >((exit_button_win->position.y - exit_button_win->size.y) * 0.5f) &&
        mouse_pos.y < ((exit_button_win->position.y + exit_button_win->size.y) * 0.5f)) {
        exit_button_win->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->must_exit = true;
        }
    }
    else {
        exit_button_win->material.color = Vector4::WHITE;
    }
    World::get_instance()->update(seconds_elapsed);
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



WinStage_less250::WinStage_less250()
{
    int width = Game::instance->window_width;
    int height = Game::instance->window_height;

    Material background_mat;
    background_mat.diffuse = Texture::Get("data/textures/background_won.png");
    background_won = new EntityUI(Vector2(width, height), Vector2(width, height), background_mat, "background");
    Material play_mat;
    play_mat.diffuse = Texture::Get("data/textures/playbutton.png");
    play_button_win = new EntityUI(Vector2(width - 250, 950), Vector2(240, 240), play_mat, "play");
    Material exit_mat;
    exit_mat.diffuse = Texture::Get("data/textures/exitbutton.png");
    exit_button_win = new EntityUI(Vector2(width + 250, 950), Vector2(175, 175), exit_mat, "exit");

    std::cout << (play_button->position.x - play_button->size.x) * 0.5f << std::endl;
    std::cout << (play_button->position.x + play_button->size.x) * 0.5f << std::endl;

    std::cout << (play_button->position.y - play_button->size.y) * 0.5f << std::endl;
    std::cout << (play_button->position.y + play_button->size.y) * 0.5f << std::endl;
}

void WinStage_less250::render()
{
    std::string message = std::to_string(World::get_instance()->player->points);
    background_won->render(World::get_instance()->camera2d);
    play_button_win->render(World::get_instance()->camera2d);
    exit_button_win->render(World::get_instance()->camera2d);
    drawText(400, 215, message, Vector3(100, 100, 50), 7);
}

void WinStage_less250::update(double seconds_elapsed)
{
    Vector2 mouse_pos = Input::mouse_position;

    if (mouse_pos.x > ((play_button_win->position.x - play_button_win->size.x) * 0.5f) &&
        mouse_pos.x< ((play_button_win->position.x + play_button_win->size.x) * 0.5f) &&
        mouse_pos.y >((play_button_win->position.y - play_button_win->size.y) * 0.5f) &&
        mouse_pos.y < ((play_button_win->position.y + play_button_win->size.y) * 0.5f)) {
        play_button_win->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->moveToStage(Game::instance->play_stage);
        }
    }
    else {
        play_button_win->material.color = Vector4::WHITE;
    }
    if (mouse_pos.x > ((exit_button_win->position.x - exit_button_win->size.x) * 0.5f) &&
        mouse_pos.x< ((exit_button_win->position.x + exit_button_win->size.x) * 0.5f) &&
        mouse_pos.y >((exit_button_win->position.y - exit_button_win->size.y) * 0.5f) &&
        mouse_pos.y < ((exit_button_win->position.y + exit_button_win->size.y) * 0.5f)) {
        exit_button_win->material.color = Vector4::RED;
        if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
            Game::instance->must_exit = true;
        }
    }
    else {
        exit_button_win->material.color = Vector4::WHITE;
    }
    World::get_instance()->update(seconds_elapsed);
}

void WinStage_less250::onEnter()
{
    HCHANNEL win = Audio::Play("data/audio/Win.wav", 0.5, false);
    if (win == 0)
    {
        std::cerr << "Failed to play audio: data/audio/Win.wav" << std::endl;
    }
}

void WinStage_less250::onExit()
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
