# chip8

**Description**
  - A CHIP-8 emulator/interpreter written in c using the CSFML library for IO.
  - CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine. It was made to allow video games to be more easily programmed for these computers. (Source: https://en.wikipedia.org/wiki/CHIP-8)
  - Technical reference: [CHIP-8](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)

**Requirments**
  - Unix based OS.
  - gcc compiler.
  - [CSFML library](https://www.sfml-dev.org/download/csfml/).

**Compiling and Running**
  - To compile the program use the included makefile
  - To run the program use `./chip8.out roms/romfile.ch8`

**Controls**
<br/> ![alt text](https://github.com/dma-neves/chip8/blob/main/other/controls.png)

**Games**
  - Inside the folder /roms are some games and tests.
  - [Game Controls](https://github.com/dma-neves/chip8/blob/main/other/game_controls.txt).

**Images**
  - Pong: <br/> ![alt text](https://github.com/dma-neves/chip8/blob/main/other/pong.png)
  - Tetris <br/> ![alt text](https://github.com/dma-neves/chip8/blob/main/other/tetris.png)
