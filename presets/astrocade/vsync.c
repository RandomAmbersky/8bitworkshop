 
#include <string.h>

//#resource "astrocade.inc"
#include "aclib.h"
//#link "aclib.s"
#include "acbios.h"
//#link "acbios.s"
//#link "hdr_autostart.s"

const byte player_bitmap[] =
{0,0,	// X, Y offset
 3,14,	// width (bytes) and height (lines)
 /*{w:12,h:16,bpp:2,brev:1}*/
 0x00,0x3C,0x00,0x00,0x18,0x00,0x00,0x3C,0x00,0x00,0x18,0x00,0x04,0x18,0x20,0x0C,0x3C,0x30,0x3C,0x3C,0x3C,0x1F,0xE7,0xF4,0x1F,0x66,0xF4,0x17,0xE7,0xE4,0x17,0xE7,0xE4,0x1C,0x7E,0x34,0x1C,0xFF,0x34,0x3C,0x18,0x3C,0x0C,0x18,0x30,0x04,0x18,0x20};

/*{pal:"astrocade",layout:"astrocade"}*/
const byte palette[8] = {
  0x07, 0xD4, 0x33, 0x01,
  0x07, 0xD4, 0x33, 0x01,
};

void main() {
  byte x,y;
  x=20;
  y=20;
  memset((void*)0x4FCE, 0, 0x5000-0x4FCE);
  set_palette(palette);
  SYS_SETOUT(98*2, 0, 0x0);
  SYS_FILL(0x4000, 98*40, 0); // clear screen
  activate_interrupts();
  while (1) {
    write_relative(x, y, M_MOVE, player_bitmap);
    write_relative(x, y+20, M_MOVE, player_bitmap);
    write_relative(x, y+40, M_MOVE|M_FLOP, player_bitmap);
//    write_relative(x, y+60, M_MOVE, player_bitmap);
    fast_vsync();
    x++;
  }
}
