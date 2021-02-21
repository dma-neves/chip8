#ifndef DISPLAY
#define DISPLAY

#include <SFML/Graphics.h>
#include "Chip8.h"

void renderDisplay(Chip8* chip8, sfRenderWindow* window);
void resetDisplay();

#endif