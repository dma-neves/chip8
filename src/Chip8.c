#include "Chip8.h"

void cls(Chip8* chip8)
{
    //memset(chip8->mem+DISP_START, 0, (DISP_END-DISP_START)*sizeof(uint8_t));

    int i = DISP_START;
    for(; i <= DISP_END; i++)
        chip8->mem[i] = 0;
}

void ret(Chip8* chip8)
{
    chip8->PC = chip8->stack[--chip8->SP];
}

void sys(Chip8* chip8)
{
    //Ignore
}