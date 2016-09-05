/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#ifndef _LAUDIO_H
#define _LAUDIO_H

#include "chip.h"
#include "vmsys.h"
#include "LTask.h"
#include "Arduino.h"

// Audio play status
typedef enum 
{
	AudioCommonFailed = -1,     // The playback has failed. For example, the audio file is corrupted.
	AudioStop = 1,              // The playback has stopped.
	AudioPause = 2,             // The Playback has paused and can be resumed.
	AudioResume = 3,            // The playback has resumed.
	AudioEndOfFile = 5          // The playback has finished.
}AudioStatus;

// Storage location
typedef enum 
{
	storageFlash,    // The flash.
	storageSD        // The SD card.
}StorageEnum;

// LAudio class interface
class LAudioClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LAudioClass() { };

public:	
	 // DESCRIPTION
	 //    Plays an audio file from an SD card or the flash storage.
	 // EXAMPLE
	 //<code>
	 //	#include <LAudio.h>  
	 //	void setup()
	 //	{
	 //   	    LAudio.begin();
	 //   	    LAudio.playFile(storageFlash, (char*)"sample.mp3");
	 //   	    LAudio.setVolume(2);
	 //   	    delay(2000);
	 //   	    LAudio.pause();
	 //   	    delay(2000);
	 //   	    LAudio.resume();
	 //   	    delay(2000);
	 //   	    LAudio.stop();
	 //	}	
	 //</code>
	void    playFile(
			StorageEnum drv,       // [IN] The storage type, it can be storageSD (SD card) or storageFlash (flash storage).
			char *songName         // [IN] The path of the audio file in ASCII (char*) encoding. 
			);
	
	 // DESCRIPTION
	 //    Plays an audio file from an SD card or flash storage.
	void    playFile(
			StorageEnum drv,        // [IN] The storage type, it can be storageSD (SD card) or storageFlash (flash storage).
			wchar_t* songName       // [IN] The path of the audio file in Unicode encoding (wchar_t*).
			);

	 // DESCRIPTION
	 //    Adjusts the playback volume; the range is from 0 (silent) to 6 (maximum).
	void    setVolume(
			unsigned char volume       // [IN] The volume level, it can be from 0 to 6; 0 as silent and 6 as maximum volume.
			);

	 // DESCRIPTION
	 //    Pauses the playback. It requires an ongoing active playback by playFile() in order to use the pause function.
	void    pause(void);

	 // DESCRIPTION
	 //    Resumes the playback. It requires the playback to be paused in order to use the resume function.
	void    resume(void);

	 // DESCRIPTION
	 //    Stops the playback.
	void    stop(void);

	 // DESCRIPTION
	 //    Queries the current playback status.
	 // RETURNS
	 //    AudioStatus: The playback status, they can be one of the following:
	 //    AudioStop: The playback has stopped.
	 //    AudioPause: The playback has paused and can be resumed.
	 //    AudioResume: The playback has resumed.
	 //    AudioEndOfFile: The playback has finished.
	 //    AudioCommonFailed: The playback has failed. For example, the audio file is corrupted.
	AudioStatus    getStatus(void);
	
public:
	VMSTR getFile();
	char getDriver();
	boolean getType();
	unsigned char getVolume();
	static void onCallback(int result);
private:
	char m_path[256];
	unsigned char  m_volume;
	char m_drv;
	boolean m_type;
};

extern LAudioClass LAudio;

#endif
