#include "timer.h"

Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}


void Timer::Start()
{
	mStarted = true;
	mPaused = false;

    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}


void Timer::Stop()
{
	mPaused = false;
	mStarted = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}


void Timer::Pause()
{
	if ( mStarted && !mPaused )
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks();
	}
}


void Timer::Unpause()
{
	if ( mStarted && mPaused )
	{
		mPaused = false;

		mPausedTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}


Uint32 Timer::GetTicks()
{
	Uint32 ticks;

	if ( mStarted )
	{
		if ( mPaused )
		{
			ticks = mPausedTicks - mStartTicks;
		}
		else
		{
			ticks = SDL_GetTicks() - mStartTicks;
		}
	}

	return ticks;
}