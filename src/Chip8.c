#include "Chip8.h"

// Clear screen
void cls(Chip8* chip8)
{
    //memset(chip8->mem+DISP_START, 0, (DISP_END-DISP_START)*sizeof(uint8_t));

    int i = DISP_START;
    for(; i <= DISP_END; i++)
        chip8->mem[i] = 0;
}

// Return from subroutine
void ret(Chip8* chip8)
{
    chip8->PC = chip8->stack[--chip8->SP];
}

void sys(Chip8* chip8)
{
    //Ignore
}

// Jump to addr
void jp(Chip8* chip8, uint16_t addr)
{
    chip8->PC = addr;
}

// Call subroutine at addr
void call(Chip8* chip8, uint16_t addr)
{
    chip8->stack[chip8->SP++] = chip8->PC;
    chip8->PC = addr;
}

// Skip next instruction if Vx = kk
void se_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk)
{
    if(chip8->V[x] == kk)
        chip8->PC += 2;
}

// Skip next instruction if Vx != kk
void sne_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk)
{
    if(chip8->V[x] != kk)
        chip8->PC += 2;
}

// Skip next instruction if Vx = Vy
void se_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    if(chip8->V[x] == chip8->V[y])
        chip8->PC += 2;
}

// Load kk into Vx
void ld_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk)
{
    chip8->V[x] = kk;
}

// Add kk to Vx
void add_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk)
{
    chip8->V[x] += kk;
}

// Load Vy into Vx
void Load_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[x] = chip8->V[y];
}

// Load Vx or Vy into Vx
void or_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[x] = chip8->V[x] | chip8->V[y];
}

// Load Vx and Vy into Vx
void and_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[x] = chip8->V[x] & chip8->V[y];
}

// Load Vx xor Vy into Vx
void xor_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[x] = chip8->V[x] ^ chip8->V[y];
}

// Load Vx + Vy into Vx
void add_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[0xF] = ( (uint16_t)chip8->V[x] + (uint16_t)chip8->V[x] > 255 );
    chip8->V[x] += chip8->V[y];
}

// Load Vx - Vy into Vx
void sub_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[0xF] = ( chip8->V[x] > chip8->V[y] );
    chip8->V[x] -= chip8->V[y];
}

// Load Vx shifted right once into Vx
void shr_vx(Chip8* chip8, uint8_t x)
{
    chip8->V[0xF] = (chip8->V[x] & 1);
    chip8->V[x] = chip8->V[x] >> 1;
}

// Load Vy - Vx into Vx
void subn_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[0xF] = ( chip8->V[y] > chip8->V[x] );
    chip8->V[x] = chip8->V[y] - chip8->V[x];
}

// Load Vx shifted left once into Vx
void shl_vx(Chip8* chip8, uint8_t x)
{
    chip8->V[0xF] = ( (chip8->V[x] & 0x80) != 0 );
    chip8->V[x] = chip8->V[x] >> 1;
}