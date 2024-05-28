#pragma once
class Stage {
public:

	virtual void render(); // Empty body
	virtual void update(double seconds_elapsed); // Empty body+

};

class IntroStage : public Stage {
public:
	IntroStage();

	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body

};

class PlayStage : public Stage {
public:
	PlayStage();
	void render(); // Empty body
	void update(double seconds_elapsed); // Empty body

};