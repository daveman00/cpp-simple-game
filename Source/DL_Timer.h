#ifndef DL_TIMER_H_INCLUDED
#define DL_TIMER_H_INCLUDED

//The application time based timer
class DL_Timer
{
    public:
		//Initializes variables
		DL_Timer();
		//~DL_Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif // DL_TIMER_H_INCLUDED
