#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "Emulator.h"

sfClock* clock;
float timer;

int main(int argc, char** argv)
{

    if(argc != 2)
        printf("usage: ./chip8 rom.ch8\n");
    
    else
    {
        clock = sfClock_create();
        timer = 0;

        Chip8* chip8 = malloc(sizeof(Chip8));
        resetSystem(chip8);
        loadRom(argv[1], chip8);

        while(1)
        {
            float dt = sfTime_asSeconds( sfClock_restart(clock) );
            timer += dt;
            if(timer >= 1.f/60.f)
            {
                // Update timers at a 60Hz frequency
                timer = 0;
                updateTimers(chip8);
            }

            // handleInput(chip8);
            // updateTimers(chip8);
            // executeNextInstruction(chip8);

            // renderDisplay(chip8);
        }

        sfClock_destroy(clock);
    }
}