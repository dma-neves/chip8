#include "Display.h"

uint8_t screenBuf[SCREEN_HEIGHT][SCREEN_WIDTH];

void resetDisplay()
{
    memset(screenBuf, 0, sizeof(screenBuf));
}

void updateBuffer(Chip8* chip8)
{
    memcpy(screenBuf, chip8->screen, sizeof(chip8->screen));
}

void renderDisplay(Chip8* chip8, sfRenderWindow* window)
{
    //if(chip8->drawFlag)
    {
        chip8->drawFlag = 0;

        sfRenderWindow_clear(window, sfBlack);

        sfRectangleShape* rect = sfRectangleShape_create();
        sfVector2f size = 
        {
            .x = sfRenderWindow_getSize(window).x / SCREEN_WIDTH,
            .y = sfRenderWindow_getSize(window).y / SCREEN_HEIGHT
        };
        sfRectangleShape_setSize(rect, size);
        sfRectangleShape_setFillColor(rect, sfColor_fromRGB(255,255,255));

        int y,x;
        for(y = 0; y < SCREEN_HEIGHT; y++)
        {
            for(x = 0; x < SCREEN_WIDTH; x++)
            {
                if(chip8->screen[y][x] | screenBuf[y][x])
                {
                    sfVector2f pos = { .x = x*size.x, .y = y*size.y };
                    sfRectangleShape_setPosition(rect, pos);
                    sfRenderWindow_drawRectangleShape(window, rect, NULL);
                }
            }
        }

        sfRenderWindow_display(window);
        updateBuffer(chip8);
    }
}