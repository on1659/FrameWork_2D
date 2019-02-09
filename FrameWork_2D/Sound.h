#pragma once


#include <fmod.h>
#include "../inc/fmod.hpp"
#include "../inc/fmod_errors.h"

#pragma comment (lib, "fmodex_vc.lib")

enum SoundType{
	SOUND_BGM,
	SOUND_EFFECT,
	SOUND_SelectEnd,
};


class SoundManager : public CSingleTonBase<SoundManager>
{


private:
	FMOD::System*				g_pSystem;
	FMOD::Channel*				g_pChannel[SOUND_SelectEnd];

	std::map<std::string, FMOD::Sound*>			m_pSound;
	float										m_fVolum;

public:
	void LoadSound();
	
	void VoulamInit();

	//배경음을 추가할 떄 사용한다
	void AddStrem(char* filePath, std::string name);

	//효과음을 추가할 떄 사용한다.
	void AddSound(char* filePath, std::string name);

	//사운드의 원활한 재생을 위해 사용한다.
	void OnUpdate();

	//효과음을 플레이 할 때사용한다
	void PlayEFFECT(std::string name);

	//따로안해도되네?
	void Play(std::string name);

	//bgm플레이는 따로 만들어줘야한다.
	void PlayBGM(std::string name);

	//스탑을 멈출 때
	void Stop();

	//소리조절
	void VolumSet(float vol);
	void VolumUp(float vol = 0.05f);
	void VolumDown(float vol = 0.05f);

	//노래를 찾을때
	FMOD::Sound*		FindSound(std::string name);

public:
	SoundManager(); 
		~SoundManager();

};


