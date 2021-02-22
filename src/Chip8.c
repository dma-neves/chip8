#include "Chip8.h"

// Clear screen
void cls(Chip8* chip8)
{
    memset(chip8->screen, 0, sizeof(chip8->screen));
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
    chip8->pcIncFlag = 0;
}

// Call subroutine at addr
void call(Chip8* chip8, uint16_t addr)
{
    chip8->stack[chip8->SP++] = chip8->PC;
    chip8->PC = addr;
    chip8->pcIncFlag = 0;
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
void ld_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
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
    chip8->V[0xF] = ( (uint16_t)chip8->V[x] + (uint16_t)chip8->V[y] > 255 );
    chip8->V[x] += chip8->V[y];
}

// Load Vx - Vy into Vx
void sub_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    chip8->V[0xF] = ( chip8->V[x] >= chip8->V[y] );
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
    chip8->V[0xF] = ( chip8->V[y] >= chip8->V[x] );
    chip8->V[x] = chip8->V[y] - chip8->V[x];
}

// Load Vx shifted left once into Vx
void shl_vx(Chip8* chip8, uint8_t x)
{
    chip8->V[0xF] = ( (chip8->V[x] & 0x80) != 0 );
    chip8->V[x] = chip8->V[x] << 1;
}

// Skip next instruction if Vx != Vy
void sne_vx_vy(Chip8* chip8, uint8_t x, uint8_t y)
{
    if(chip8->V[x] != chip8->V[y])
        chip8->PC += 2;
}

// Load addr into I
void ld_i_addr(Chip8* chip8, uint16_t addr)
{
    chip8->I = addr;
}

// Jump to V0 + addr
void jp_v0_addr(Chip8* chip8, uint16_t addr)
{
    chip8->PC = chip8->V[0] + addr;
}

// Load rnd and kk into Vx
void rnd_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk, uint8_t rnd)
{
    chip8->V[x] = rnd & kk;
}

// Draw sprite at display coordinates (Vx, Vy), stored at address I with n bytes.
void drw_vx_vy(Chip8* chip8, uint8_t x, uint8_t y, uint8_t n)
{
    // Reset collision register to false
    chip8->V[0xF] = 0;
    int i,j;
    for(i = 0; i < n; i++)
    {
        uint8_t sprite_ps = chip8->mem[chip8->I + i]; // Sprite pixel set (8 pixels)

        for(j = 0; j < 8; j++)
        {
            int py = (chip8->V[y]+i) % SCREEN_HEIGHT;
            int px = (chip8->V[x]+j) % SCREEN_WIDTH;
            uint8_t* pixel = &chip8->screen[py][px];
            uint8_t sprite_p = ( sprite_ps & (0x80 >> j) ) != 0; 
            uint8_t screen_p = *pixel;
            *pixel = screen_p ^ sprite_p;

            // If pixel is ereased set collision register to true
            if(screen_p == 1 && *pixel == 0)
                chip8->V[0xF] = 1;
        }
    }
}

// Skip next instruction if key with the value of Vx is pressed
void skp_vx(Chip8* chip8, uint8_t x)
{
    if(chip8->keyboard[chip8->V[x]])
        chip8->PC += 2;
}

// Skip next instruction if key with the value of Vx is not pressed
void sknp_vx(Chip8* chip8, uint8_t x)
{
    if(!chip8->keyboard[chip8->V[x]])
        chip8->PC += 2;
}

// Set Vx = delay timer value
void ld_vx_dt(Chip8* chip8, uint8_t x)
{
    chip8->V[x] = chip8->delayTimer;
}

// Wait for a key press, store the value of the key in Vx
void ld_vx_k(Chip8* chip8, uint8_t x)
{
    int i = 0;
    for(; i < NUM_KEYS; i++)
    {
        if(chip8->keyboard[i])
            chip8->V[x] = i;
    }

    if(i == NUM_KEYS)
        chip8->pcIncFlag = 0;
}

// Set delay timer = Vx
void ld_dt_vx(Chip8* chip8, uint8_t x)
{
    chip8->delayTimer = chip8->V[x];
}

// Set sound timer = Vx
void ld_st_vx(Chip8* chip8, uint8_t x)
{
    chip8->soundTimer = chip8->V[x];
}

// Set I = I + Vx
void add_i_vx(Chip8* chip8, uint8_t x)
{
    chip8->I += chip8->V[x];
}

// Set I = location of sprite for digit Vx
void ld_f_vx(Chip8* chip8, uint8_t x)
{
    chip8->I = FONTSET_START_ADDRESS + chip8->V[x] * FONTSET_BYTES_PER_DIGIT;
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2
void ld_b_vx(Chip8* chip8, uint8_t x)
{
    chip8->mem[chip8->I] = chip8->V[x]/100;
    chip8->mem[chip8->I+1] = (chip8->V[x]/10) % 10;
    chip8->mem[chip8->I+2] = (chip8->V[x] % 100) % 10;
}

// Store registers V0 through Vx in memory starting at location I
void ld_i_vx(Chip8* chip8, uint8_t x)
{
    int i = 0;
    for(; i <= x; i++)
        chip8->mem[chip8->I + i] = chip8->V[x];
}

// Read registers V0 through Vx from memory starting at location I
void ld_vx_i(Chip8* chip8, uint8_t x)
{
    int i = 0;
    for(; i <= x; i++)
        chip8->V[i] = chip8->mem[chip8->I + i];
}