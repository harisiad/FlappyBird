#ifndef _FLAPPYBIRD_TRANSCRIPTS_GAMEACTS_H_
#define _FLAPPYBIRD_TRANSCRIPTS_GAMEACTS_H_

#include "fb_globals.h"

class Acts {
	protected:
		ALLEGRO_EVENT event;

	public:
		Acts() {};

		virtual void ActsPlayLoop() = 0;
		virtual void ActsProgramme() = 0;
		virtual void PauseAct() = 0;
		virtual void CheatTheGame() = 0;
		virtual void DebugAct() = 0;
		virtual void OpenCurtains() = 0;
		virtual void CloseCurtains() = 0;

		~Acts() {};
};

#endif