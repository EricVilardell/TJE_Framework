/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#pragma once

#include "framework/includes.h"
#include "framework/camera.h"
#include "framework/utils.h"
#include "stage.h"
class Game
{
public:
	static Game* instance;

	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	//some globals
	long frame;
	float time;
	float elapsed_time;
	int fps;
	bool must_exit;
	IntroStage* intro_stage;
	PlayStage* play_stage = new PlayStage();
	EndStage* end_stage;
	WinStage* win_stage;
	WinStage_less250* win_stage_less250;

	Stage* currentStage = nullptr;

	//some vars
	Camera* camera; //our global camera
	Camera* camera2d;
	bool mouse_locked; //tells if the mouse is locked (not seen)


	Game(int window_width, int window_height, SDL_Window* window);

	//main functions
	void render(void);
	void update(double dt);

	//events
	void onKeyDown(SDL_KeyboardEvent event);
	void onKeyUp(SDL_KeyboardEvent event);
	void onMouseButtonDown(SDL_MouseButtonEvent event);
	void onMouseButtonUp(SDL_MouseButtonEvent event);
	void onMouseWheel(SDL_MouseWheelEvent event);
	void onGamepadButtonDown(SDL_JoyButtonEvent event);
	void onGamepadButtonUp(SDL_JoyButtonEvent event);
	void onResize(int width, int height);
	void moveToStage(Stage* stage);
};