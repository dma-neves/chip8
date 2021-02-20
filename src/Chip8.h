#ifndef CHIP8
#define CHIP8

#include <stdint.h>
#include <string.h>

#define MEM_SIZE   0xFFF
#define PROG_START 0x200
#define DISP_START 0x000
#define DISP_END   0x1FF
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define NUM_KEYS 16
#define FONTSET_START_ADDRESS 0x50
#define FONTSET_BYTES_PER_DIGIT 5
#define FONTSET_NDIGITS 16
#define FONTSET_SIZE FONTSET_NDIGITS*FONTSET_BYTES_PER_DIGIT

typedef struct _Chip8
{
    uint8_t mem[MEM_SIZE];          // 4096 byte memory

    uint8_t V[16];                  // 16 8-bit registers
    uint16_t I;                     // 16-bit register for addresses
    uint8_t SP;                     // 8-bit stack pointer
    uint16_t PC;                    // 16-bit program counter
    uint8_t delayTimer, soundTimer; // 8-bit registers for sound and delay timers

    uint16_t stack[16];             // stack 16 16-bit values

    uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    uint8_t keyboard[NUM_KEYS];
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
void ld_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void or_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void and_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void xor_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void add_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void sub_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void shr_vx(Chip8* chip8, uint8_t x);
void subn_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void shl_vx(Chip8* chip8, uint8_t x);
void sne_vx_vy(Chip8* chip8, uint8_t x, uint8_t y);
void ld_i_addr(Chip8* chip8, uint16_t addr);
void jp_v0_addr(Chip8* chip8, uint16_t addr);
void rnd_vx_kk(Chip8* chip8, uint8_t x, uint8_t kk, uint8_t rnd);
void drw_vx_vy(Chip8* chip8, uint8_t x, uint8_t y, uint8_t n);
void skp_vx(Chip8* chip8, uint8_t x);
void sknp_vx(Chip8* chip8, uint8_t x);
void ld_vx_dt(Chip8* chip8, uint8_t x);
void ld_vx_k(Chip8* chip8, uint8_t x);
void ld_dt_vx(Chip8* chip8, uint8_t x);
void ld_st_vx(Chip8* chip8, uint8_t x);
void add_i_vx(Chip8* chip8, uint8_t x);
void ld_f_vx(Chip8* chip8, uint8_t x);
void ld_b_vx(Chip8* chip8, uint8_t x);
void ld_i_vx(Chip8* chip8, uint8_t x);
void ld_vx_i(Chip8* chip8, uint8_t x);

#endif

