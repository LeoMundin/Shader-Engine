#include "Game/ElderHex.h"

#include "soloud.h"
#include "soloud_wav.h"
#include <iostream>


const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;

ElderHex game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(){

    // TO-DO : Move to seperate system with sound objects for audio handling.
    // Start Music
    SoLoud::Soloud audio;
    audio.init();        

    SoLoud::Wav music; 
    if (music.load("Assets/Audio/Skyrim_16-bit_Theme.mp3") != 0)
    {
        std::cout << "Failed to load audio!\n";
        return 1;
    } 

    music.setVolume(0.5);
    audio.play(music);

    // Start Game
    game.init();
    return 0;

}






   



