#ifndef EMULATOR
#define EMULATOR

#include "Chip8.h"

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

void loadRom(char* file, Chip8* chip8);
void resetSystem(Chip8* chip8);
void executeNextInstruction(Chip8* chip8);
void updateTimers(Chip8* chip8, sfSound* buzzer);
void handleInput(Chip8* chip8);
void render(Chip8* chip8, sfRenderWindow* window);

// Debug
void printMem(Chip8* chip8);
void printRegs(Chip8* chip8);

#endif