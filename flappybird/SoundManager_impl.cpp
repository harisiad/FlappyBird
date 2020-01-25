#include "SoundManager.h"

SoundManager::SoundManager(){
	mixer = (ALLEGRO_MIXER*)0;
	theme_song = (ALLEGRO_SAMPLE_INSTANCE*)0;
	flap_sound = (ALLEGRO_SAMPLE_INSTANCE*)0;
	collision_sound = (ALLEGRO_SAMPLE_INSTANCE*)0;
	success_sound = (ALLEGRO_SAMPLE_INSTANCE*)0;
}
void SoundManager::initSManager(ALLEGRO_SAMPLE_INSTANCE* _theme,
	ALLEGRO_SAMPLE_INSTANCE* _flap,
	ALLEGRO_SAMPLE_INSTANCE* _collision,
	ALLEGRO_SAMPLE_INSTANCE* _success,
	ALLEGRO_MIXER* _mixer){

	theme_song = _theme;
	flap_sound = _flap;
	collision_sound = _collision;
	success_sound = _success;
	mixer = _mixer;
}

void SoundManager::initMixer(ALLEGRO_VOICE* _voicedata){
	_voicedata = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (!_voicedata){
		std::cout << "Failed to create voice!" << std::endl;
	}

	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if (!mixer){
		std::cout << "Failed to create mixer!" << std::endl;
	}

	if (!al_attach_mixer_to_voice(mixer, _voicedata)){
		std::cout << "Failed to attach mixer to voice!" << std::endl;
	}
}

void SoundManager::attach_Samples_to_Instances(ALLEGRO_SAMPLE* _themedata,
	ALLEGRO_SAMPLE* _flapdata,
	ALLEGRO_SAMPLE* _hitdata,
	ALLEGRO_SAMPLE* _pointdata){

	if (_themedata == NULL){
		std::cout << "Failed to initialize theme sample!" << std::endl;
	}
	if (_flapdata == NULL){
		std::cout << "Failed to initialize flaping sample!" << std::endl;
	}
	if (_hitdata == NULL){
		std::cout << "Failed to initialize collision sample!" << std::endl;
	}
	if (_pointdata == NULL){
		std::cout << "Failed to initialize success sample!" << std::endl;
	}

	if (!al_set_sample(theme_song, _themedata)){
		std::cout << "Failed to load theme song sample data to instance" << std::endl;
	}
	if (!al_set_sample(flap_sound, _flapdata)){
		std::cout << "Failed to load flap sound sample data to instance" << std::endl;
	}
	if (!al_set_sample(collision_sound, _hitdata)){
		std::cout << "Failed to load collision sound sample data to instance" << std::endl;
	}
	if (!al_set_sample(success_sound, _pointdata)){
		std::cout << "Failed to load point sound sample data to instance" << std::endl;
	}

}

void SoundManager::attach_Instances_to_Mixer(){
	
	if (!al_attach_sample_instance_to_mixer(theme_song, mixer)){
		std::cout << "Failed to attach theme song Instance to Mixer" << std::endl;
	}
	al_set_sample_instance_playmode(flap_sound, ALLEGRO_PLAYMODE_ONCE);
	if (!al_attach_sample_instance_to_mixer(flap_sound, mixer)){
		std::cout << "Failed to attach flap sound Instance to Mixer" << std::endl;
	}
	al_set_sample_instance_playmode(flap_sound, ALLEGRO_PLAYMODE_ONCE);
	if (!al_attach_sample_instance_to_mixer(collision_sound, mixer)){
		std::cout << "Failed to attach collision sound Instance to Mixer" << std::endl;
	}
	al_set_sample_instance_playmode(flap_sound, ALLEGRO_PLAYMODE_ONCE);
	if (!al_attach_sample_instance_to_mixer(success_sound, mixer)){
		std::cout << "Failed to attach point sound Instance to Mixer" << std::endl;
	}

}

void SoundManager::playThemeSong(){
	al_set_sample_instance_playmode(theme_song, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(theme_song, 0.7);
	al_play_sample_instance(theme_song);
}

void SoundManager::pauseThemeSong(){
	al_stop_sample_instance(theme_song);
}

void SoundManager::playFlapSound(){
	al_play_sample_instance(flap_sound);
}
void SoundManager::playCollisionSound(){
	al_play_sample_instance(collision_sound);
}
void SoundManager::playSuccessSound(){
	al_play_sample_instance(success_sound);
}