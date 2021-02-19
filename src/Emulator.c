#include "Emulator.h"
#include "Display.h"

#include <stdio.h>
#include <string.h>

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

    uint8_t word[4] =
    {
        lowbyte & 0x0F,
        lowbyte >> 4,
        highbyte & 0x0F,
        highbyte >> 4
    };

    uint16_t nibble = ( (uint16_t)lowbyte ) & ( (uint16_t)word[2] << 12 );

    switch(word[3])
    {
        case 0x0:
            if(lowbyte == 0xE0)
                cls(chip8);
            else if(lowbyte == 0xEE)
                ret(chip8);
            else
                sys(chip8);
            break;

        case 0x1:
            jp(chip8, nibble);
            break;

        case 0x2:
            call(chip8, nibble);
            break;

        case 0x3:
            se_vx_kk(chip8, word[2], lowbyte);
            break;

        case 0x4:
            sne_vx_kk(chip8, word[2], lowbyte);
            break;

        case 0x5:
            if(word[0] == 0)
                se_vx_vy(chip8, word[2], word[1]);
            break;

        case 0x6:
            ld_vx_kk(chip8, word[2], lowbyte);
            break;

        case 0x7:
            add_vx_kk(chip8, word[2], lowbyte);
            break;

        case 0x8:
            switch(word[0])
            {
                case 0x0:
                    ld_vx_vy(chip8, word[2], word[1]);
                    break;
                
                case 0x1:
                    or_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0x2:
                    and_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0x3:
                    xor_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0x4:
                    add_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0x5:
                    sub_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0x6:
                    shr_vx(chip8, word[2]);
                    break;

                case 0x7:
                    subn_vx_vy(chip8, word[2], word[1]);
                    break;

                case 0xE:
                    shl_vx(chip8, word[2]);
                    break;
            }
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