
#include "neslib.h"
#include <string.h>

// link the pattern table into PRG ROM
// we'll write it into CHR RAM on startup

//#link "jroatch.c"
extern unsigned char jroatch_chr[0x1000];
#define PATTERN_TABLE jroatch_chr

// function to write a string into the name table
//   adr = start address in name table
//   str = pointer to string
void put_str(unsigned int adr, const char *str) {
  vram_adr(adr);        // set PPU read/write address
  vram_write(str, strlen(str)); // write bytes to PPU
}

// function to scroll window up and down until end
void scroll_demo() {
  int x = 0;   // x scroll position
  int y = 0;   // y scroll position
  int dy = 1;  // y scroll direction
  // infinite loop
  while (1) {
    // wait for next frame
    ppu_wait_frame();
    // set scroll register
    scroll(x, y);
    // update y variable
    y += dy;
    // change direction when hitting either edge of scroll area
    if (y >= 479) dy = -1;
    if (y == 0) dy = 1;
  }
}

// main function, run after console reset
void main(void) {
  // copy pattern table to PRG RAM
  vram_adr(0x0);
  vram_write((unsigned char*)PATTERN_TABLE, sizeof(PATTERN_TABLE));

  // set palette colors
  pal_col(1,0x04);
  pal_col(2,0x20);
  pal_col(3,0x30);

  // write text to name table
  put_str(NTADR_A(2,0), "Nametable A, Line 0");
  put_str(NTADR_A(2,15), "Nametable A, Line 15");
  put_str(NTADR_A(2,29),"Nametable A, Line 29");
  put_str(NTADR_C(2,0), "Nametable C, Line 0");
  put_str(NTADR_C(2,15), "Nametable C, Line 15");
  put_str(NTADR_C(2,29),"Nametable C, Line 29");

  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // scroll window back and forth
  scroll_demo();
}
