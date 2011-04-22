//****************************************************************
//cAudio 2.1.0 Tutorial 3
//Basic Memory Playback *Virtual file systems*
//bling.h created with bin2h http://deadnode.org/sw/bin2h/
//****************************************************************

#include <iostream>
#include <string>

//Include cAudio.h so we can work wtih cAudio
#include "../../include/cAudio.h"

//Our Bling sound
#include "bling.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Some fancy text
    cout << "cAudio 2.1.0 Tutorial 3: Memory Playback. \n \n";
    
	//Create an uninitialized Audio Manager
    cAudio::IAudioManager* manager = cAudio::createAudioManager(false);

	if(manager)
	{
		//Allow the user to choose a playback device
		cout << "\nAvailable Playback Devices: \n";
		unsigned int deviceCount = manager->getAvailableDeviceCount();
		std::string defaultDeviceName = manager->getDefaultDeviceName();
		for(unsigned int i=0; i<deviceCount; ++i)
		{
			std::string deviceName = manager->getAvailableDeviceName(i);
			if(deviceName.compare(defaultDeviceName) == 0)
				cout << i << "): " << deviceName << " [DEFAULT] \n";
			else
				cout << i << "): " << deviceName << " \n";
		}
		cout << std::endl;
		cout << "Choose a device by number: ";
		unsigned int deviceSelection = 0;
		cin >> deviceSelection;
		cout << std::endl;

		//Initialize the manager with the user settings
		manager->initialize(manager->getAvailableDeviceName(deviceSelection));

		//Create a IAudio object and load a sound from memory. using the bling array and bling size generated by bin2h.
		cAudio::IAudioSource* mysound = manager->createFromMemory("bling",(const char*)bling,bling_size,"wav");

		if(mysound)
		{
			//Set the IAudio Sound to play2d and loop
			mysound->play2d(true);

			//Sleep for 10,000 ms to free some CPU, also makes the example only last 10 seconds
			cAudio::cAudioSleep(10000);
		}

		//Delete all IAudio sounds
		manager->releaseAllSources();
		//Shutdown cAudio
		manager->shutDown();

		cAudio::destroyAudioManager(manager);
	}
	else
	{
		std::cout << "Failed to create audio playback manager. \n";
	}

	std::cout << "Press any key to quit \n";
	std::cin.get();
	std::cin.get();

    return 0;
}