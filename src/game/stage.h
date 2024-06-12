#pragma once
#include "framework/audio.h"
class Stage {
public:

	virtual void render(); // Empty body
	virtual void update(double seconds_elapsed); // Empty body+
	virtual void onEnter();
	virtual void onExit();
	HCHANNEL channel;
};

class IntroStage : public Stage {
public:
	IntroStage();

	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body
	void onEnter();
	void onExit();
};

class PlayStage : public Stage {
public:
	PlayStage();
	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body
	void onEnter();
	void onExit();
};

class EndStage : public Stage {
public:
	HCHANNEL muerte;
	EndStage();
	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body
	void onEnter();
	void onExit();
};

class WinStage : public Stage {
public:
	WinStage();
	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body
	void onEnter();
	void onExit();
};