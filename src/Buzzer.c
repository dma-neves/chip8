#include "Buzzer.h"

#include <stdint.h>

#define NSAMPLES 44100

sfSound* buzzer;
sfSoundBuffer* soundBuf;
uint16_t samples[NSAMPLES];

short squareWave(double time, double freq, double amp)
{
    short result = 0;
    int tcp = NSAMPLES / freq; // Ticks per cycle
    int cyclepart = (int)(time) % tcp;
    int halfcycle = tcp/2;
    short amplitude = 32767 * amp;

    if(cyclepart <  halfcycle)
        result = amplitude;
    
    return result;
}

sfSound* buzzerCreate()
{
    int i = 0;
    for(; i < NSAMPLES; i++)
        samples[i] = squareWave(i, 440, 0.1);

    soundBuf = sfSoundBuffer_createFromSamples(samples, NSAMPLES, 1, NSAMPLES);
    buzzer = sfSound_create();
    sfSound_setBuffer(buzzer, soundBuf);
    sfSound_setLoop(buzzer, 1);

    return buzzer;
}

void buzzerDestroy()
{
    sfSound_destroy(buzzer);
    sfSoundBuffer_destroy(soundBuf);
}