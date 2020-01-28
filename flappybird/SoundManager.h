#pragma once

#include "Globals.h"

class SoundManager {
protected:
	ALLEGRO_SAMPLE_INSTANCE *theme_song;
	ALLEGRO_SAMPLE_INSTANCE *flap_sound;
	ALLEGRO_SAMPLE_INSTANCE *collision_sound;
	ALLEGRO_SAMPLE_INSTANCE *success_sound;
	ALLEGRO_MIXER *mixer;

public:

	SoundManager();
	void initSManager(ALLEGRO_SAMPLE_INSTANCE*, 
		ALLEGRO_SAMPLE_INSTANCE*, 
		ALLEGRO_SAMPLE_INSTANCE*,
		ALLEGRO_SAMPLE_INSTANCE*,
		ALLEGRO_MIXER *);
	void initMixer(ALLEGRO_VOICE*);
	void attach_Samples_to_Instances(ALLEGRO_SAMPLE*,
		ALLEGRO_SAMPLE*,
		ALLEGRO_SAMPLE*,
		ALLEGRO_SAMPLE*);
	void attach_Instances_to_Mixer();

	void setThemeSong(ALLEGRO_SAMPLE_INSTANCE* _theme) { theme_song = _theme; }
	ALLEGRO_SAMPLE_INSTANCE* getThemeSong(){ return theme_song; }

	void setFlapSound(ALLEGRO_SAMPLE_INSTANCE* _flap) { flap_sound = _flap; }
	ALLEGRO_SAMPLE_INSTANCE* getFlapSound(){ return flap_sound; }

	void setCollisionSound(ALLEGRO_SAMPLE_INSTANCE* _collision) { collision_sound = _collision; }
	ALLEGRO_SAMPLE_INSTANCE* getCollisionSound(){ return collision_sound; }

	void setSuccessSound(ALLEGRO_SAMPLE_INSTANCE* _success) { success_sound = _success; }
	ALLEGRO_SAMPLE_INSTANCE* getSuccessSound(){ return success_sound; }

	void setMixer(ALLEGRO_MIXER* _mixer) { mixer = _mixer; }
	ALLEGRO_MIXER* getMixer(){ return mixer; }

	void playThemeSong();
	void playFlapSound();
	void playCollisionSound();
	void playSuccessSound();

	void pauseThemeSong();
};