#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "Emulator.h"

#define W_HEIGHT 320
#define W_WIDTH  640

sfClock* clock;
sfRenderWindow* window;
sfVideoMode mode;
sfEvent event;
float timer_60;  // 60Hz  timer
float timer_500; // 500Hz timer
int running;

void handleCloseEvent()
{
    while(sfRenderWindow_pollEvent(window, &event))
    {
        if(event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        {
            running = 0;
            sfRenderWindow_close(window);
        }
    }
}

int main(int argc, char** argv)
{
    if(argc != 2)
        printf("usage: ./chip8 rom.ch8\n");
    
    else
    {
        mode.height = W_HEIGHT;
        mode.width = W_WIDTH;
        mode.bitsPerPixel = 32;
        window = sfRenderWindow_create(mode, "chip-8", sfResize | sfClose, NULL);
        clock = sfClock_create();
        timer_60 = 0;
        running = 1;

        Chip8* chip8 = malloc(sizeof(Chip8));
        resetSystem(chip8);
        loadRom(argv[1], chip8);

        while(running)
        {
            handleCloseEvent();

            float dt = sfTime_asSeconds( sfClock_restart(clock) );
            timer_60 += dt;
            timer_500 += dt;

            if(timer_60 >= 1.f/60.f)
            {
                // Update timer_60s at a 60Hz frequency
                timer_60 = 0;
                updateTimers(chip8);
            }

            if(timer_500 >= 1.f/500.f)
            {
                timer_500 = 0;
                executeNextInstruction(chip8);
            }

            handleInput(chip8);
            renderDisplay(chip8, window);
        }

        sfClock_destroy(clock);
        sfRenderWindow_destroy(window);
    }
}