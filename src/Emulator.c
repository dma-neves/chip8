#include "Emulator.h"
#include "Display.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

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

void loadFonts(Chip8* chip8)
{
    int i = 0;
    for(; i < FONTSET_SIZE; i++)
    {
        chip8->mem[FONTSET_START_ADDRESS + i] = fontset[i]; 
    }
}

void resetSystem(Chip8* chip8)
{
    memset(chip8, 0, sizeof(Chip8));
    chip8->drawFlag = 1;
    chip8->PC = PROG_START;
    loadFonts(chip8);
    srand(time(NULL));
}

void executeNextInstruction(Chip8* chip8)
{
    chip8->pcIncFlag = 1;

    uint8_t highbyte = chip8->mem[chip8->PC];
    uint8_t lowbyte = chip8->mem[chip8->PC+1];

    // printf("highbyte: %X\n", highbyte);
    // printf("lowbyte: %X\n", lowbyte);
    // printRegs(chip8);
    // getchar();

    uint8_t word[4] =
    {
        lowbyte & 0x0F,
        lowbyte >> 4,
        highbyte & 0x0F,
        highbyte >> 4
    };

    uint16_t nibble = ( (uint16_t)lowbyte ) | ( (uint16_t)word[2] << 8 );

    // if(highbyte == 0 && lowbyte == 0)
    //     exit(0);

    switch(word[3])
    {
        case 0x0:
            if(lowbyte == 0xE0)
            {
                cls(chip8);
                //printf("REACHED\n");
            }
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
            sne_vx_vy(chip8, word[2], word[1]);
            break;

        case 0xA:
            ld_i_addr(chip8, nibble);
            break;
        
        case 0xB:
            jp_v0_addr(chip8, nibble);
            break;
        
        case 0xC:
            rnd_vx_kk(chip8, word[2], lowbyte, rand()%256);
            break;

        case 0xD:
            drw_vx_vy(chip8, word[2], word[1], word[0]);
            break;

        case 0xE:
            switch(lowbyte)
            {
                case 0x9E:
                    skp_vx(chip8, word[2]);
                    break;

                case 0xA1:
                    sknp_vx(chip8, word[2]);
                    break;
            }
            break;

        case 0xF:
            switch(lowbyte)
            {
                case 0x07:
                    ld_vx_dt(chip8, word[2]);
                    break;

                case 0x0A:
                    ld_vx_k(chip8, word[2]);
                    break;

                case 0x15:
                    ld_dt_vx(chip8, word[2]);
                    break;

                case 0x18:
                    ld_st_vx(chip8, word[2]);
                    break;
                
                case 0x1E:
                    add_i_vx(chip8, word[2]);
                    break;

                case 0x29:
                    ld_f_vx(chip8, word[2]);
                    break;

                case 0x33:
                    ld_b_vx(chip8, word[2]);
                    break;

                case 0x55:
                    ld_i_vx(chip8, word[2]);
                    break;

                case 0x65:
                    ld_vx_i(chip8, word[2]);
                    break;
            }
            break;
    }

    if(chip8->pcIncFlag)
        chip8->PC += 2;
}

void updateTimers(Chip8* chip8)
{
    if(chip8->delayTimer != 0)
        chip8->delayTimer--;

    if(chip8->soundTimer != 0)
        chip8->soundTimer--;
}

void handleInput(Chip8* chip8)
{
    chip8->keyboard[0x1] = sfKeyboard_isKeyPressed(sfKeyNum1);
    chip8->keyboard[0x2] = sfKeyboard_isKeyPressed(sfKeyNum2);
    chip8->keyboard[0x3] = sfKeyboard_isKeyPressed(sfKeyNum3);
    chip8->keyboard[0xC] = sfKeyboard_isKeyPressed(sfKeyNum4);

    chip8->keyboard[0x4] = sfKeyboard_isKeyPressed(sfKeyQ);
    chip8->keyboard[0x5] = sfKeyboard_isKeyPressed(sfKeyW);
    chip8->keyboard[0x6] = sfKeyboard_isKeyPressed(sfKeyE);
    chip8->keyboard[0xD] = sfKeyboard_isKeyPressed(sfKeyR);

    chip8->keyboard[0x7] = sfKeyboard_isKeyPressed(sfKeyA);
    chip8->keyboard[0x8] = sfKeyboard_isKeyPressed(sfKeyS);
    chip8->keyboard[0x9] = sfKeyboard_isKeyPressed(sfKeyD);
    chip8->keyboard[0xE] = sfKeyboard_isKeyPressed(sfKeyF);

    chip8->keyboard[0xA] = sfKeyboard_isKeyPressed(sfKeyZ);
    chip8->keyboard[0x0] = sfKeyboard_isKeyPressed(sfKeyX);
    chip8->keyboard[0xB] = sfKeyboard_isKeyPressed(sfKeyC);
    chip8->keyboard[0xF] = sfKeyboard_isKeyPressed(sfKeyV);

}

void printMem(Chip8* chip8)
{
    int i;
    for(i = PROG_START; i < PROG_START+250; i++)
    {
        printf("%X ", chip8->mem[i]);

        if((i+1)%16 == 0) printf("\n");
    }
    printf("\n");
}

void printRegs(Chip8* chip8)
{
    for(int i = 0; i < 16; i++)
        printf("V[%X] = %X\n", i, chip8->V[i]);


    printf("I = %X\n", chip8->I);
    printf("PC = %X\n", chip8->PC);
    printf("SP = %X\n", chip8->SP);
    printf("DT = %X\n", chip8->delayTimer);
    printf("ST = %X\n", chip8->soundTimer);
}