#ifndef CHIP8
#define CHIP8

#include <stdint.h>

#define MEM_SIZE   0xFFF
#define PROG_START 0x200
#define DISP_START 0x000
#define DISP_END   0x1FF

typedef struct _Chip8
{
    uint8_t mem[MEM_SIZE];          // 4096 byte memory

    uint8_t V[16];                  // 16 8-bit registers
    int I;                          // 8-bit register for addresses
    uint8_t SP;                     // 8-bit stack poinyrt
    int PC;                         // 16-bit program counter
    uint8_t delayTimer, soundTimer; // 8-bit registers for sound and delay timers

    int stack[16];                  // stack 16 16-bit values
} Chip8;

void cls(Chip8* chip8);
void ret(Chip8* chip8);
void sys(Chip8* chip8);
void jp(Chip8* chip8, uint16_t addr);
void call(Chip8* chip8, uint16_t addr);
void se_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk);
void sne_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk);
void se_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void ld_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk);
void add_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk);
void lod_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void or_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void and_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void xor_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void add_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void sub_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void shr_vx(Chip8* chip8, uint8_t x);
void subn_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void shl_vx(Chip8* chip8, uint8_t x);

#endif

