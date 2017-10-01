#ifndef CLOCK_H
#define CLOCK_H

#include "timer.h"
#include "texture.h"

#include "constants.h"

#include <sstream>

class Clock: public Texture
{
public:
	Clock()
	{
		mSecondsPassed = 0;
		mMinutesPassed = 0;

		timer = new Timer();

		color = { 0, 0, 0 };
	}

	void Start() { timer->Start(); }
	void Pause() { timer->Pause(); }

	void Render()
	{
		SetTime();
		std::stringstream time;
		time << mMinutesPassed << ':' << mSecondsPassed;
		Texture::LoadFromRenderedText( time.str(), color );
		Texture::Render( SCREEN_WIDTH * 0.1, SCREEN_HEIGHT - Texture::GetHeight() * 1.1 );
	}

private:
	Timer* timer;

	int mSecondsPassed;
	int mMinutesPassed;

	SDL_Color color;

	void SetTime()
	{
		mSecondsPassed = timer->GetTicks() / 1000;

		mMinutesPassed = mSecondsPassed / 60;
		mSecondsPassed %= 60;
	}

};


#endif // CLOCK_H
