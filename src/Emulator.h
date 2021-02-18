#ifndef EMULATOR
#define EMULATOR

#include "Chip8.h"

void loadRom(char* file, Chip8* chip8);
void resetSystem(Chip8* chip8);
void executeNextInstruction(Chip8* chip8);
void updateTimers(Chip8* chip8);

void handleInput(Chip8* chip8);
void renderDisplay(Chip8* chip8);

#endif