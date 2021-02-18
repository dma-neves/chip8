#include "Emulator.h"
#include "Display.h"

#include <stdio.h>

void loadRom(char* file, Chip8* chip8)
{
    FILE *fp;
    int c, i, max = MEM_SIZE;

    fp = fopen(file, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "cannot open input file\n");
        return;
    }

    for (i = 0; i < max && (c = getc(fp)) != EOF; i++)
        chip8->mem[PROG_START + i] = (uint8_t)c;

    fclose(fp);
}

void resetSystem(Chip8* chip8)
{
    memset(chip8, 0, sizeof(Chip8));
}

void executeNextInstruction(Chip8* chip8)
{
    uint8_t highbyte = chip8->mem[chip8->PC++];
    uint8_t lowbyte = chip8->mem[chip8->PC++];

    uint8_t highword = highbyte & 0xF0;
    switch(highword)
    {
        case 0x0:
            if(lowbyte == 0xE0)
                cls(chip8);
            else if(lowbyte == 0xEE)
                ret(chip8);
            else
                sysAddr(chip8);
            break;

        case 0x1:
            break;

        case 0x2:
            break;

        case 0x3:
            break;

        case 0x4:
            break;

        case 0x5:
            break;

        case 0x6:
            break;

        case 0x7:
            break;

        case 0x8:
            break;

        case 0x9:
            break;

        case 0xA:
            break;
        
        case 0xB:
            break;
        
        case 0xC:
            break;

        case 0xD:
            break;

        case 0xE:
            break;

        case 0xF:
            break;
    }
}

void updateTimers(Chip8* chip8)
{
    if(chip8->delayTimer != 0)
        chip8->delayTimer--;
}

void handleInput(Chip8* chip8)
{

}

void renderDisplay(Chip8* chip8)
{

}

void printMem(Chip8* chip8)
{
    int i;
    for(i = PROG_START; i < MEM_SIZE; i++)
    {
        printf("%X ", chip8->mem[i]);

        if((i+1)%16 == 0) printf("\n");
    }
}