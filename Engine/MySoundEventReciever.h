
#include <irrKlang.h>

class MySoundEndReceiver : public irrklang::ISoundStopEventReceiver
{
public:
	virtual void OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
	{
		// called when the sound has ended playing
		sound->stop();
	}
};