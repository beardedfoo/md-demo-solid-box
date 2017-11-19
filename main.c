// Author: Cyle Riggs (@beardedfoo)
// This program for the Sega Genesis/Megadrive demonstrates the
// most basic use the VDP tile subsystem by displaying a solid box
// on the screen.
#include <genesis.h>

// This program will load just a single tile. A tile is a primitive
// image which is displayed on part of the screen.
#define NUM_TILES 1

// Disable the use of DMA for tile loading
#define LOAD_TILE_WITH_DMA FALSE

// Assign an index for our tile, as the system can store many
// tiles and we need a numerical reference for this particular
// tile.
#define VRAM_POS_TILE_SOLID 1

// Place the tile at coordinates 10,13 on a grid of 40x28 tiles
#define COORD_X 10
#define COORD_Y 13

// Tiles represent 8x8 pixel areas on the screen using a matrix
// of 8x8 nibbles (hex digits). Each hex digit allows the
// selection of 16 colors (0-F) from a palette for that pixel
// on screen. This particular tile is defined as a full block
// of color "1" for all 64 pixels.
const u32 TILE_SOLID[8] =
{
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
	0x11111111,
};

int main()
{
  // Setup the video chip
  VDP_init();

  // Load the tile data into the video chip
  VDP_loadTileData(TILE_SOLID, VRAM_POS_TILE_SOLID, NUM_TILES,
  	LOAD_TILE_WITH_DMA);


  // The Megadrive VDP supports two tile "plans" (PLAN_A and PLAN_B).
  // These plans define a selection of tiles in a grid of 40x28
  // visible tiles. Here we update PLAN_A to place our tile at the
  // X,Y coordinates of choice. The coordinates are specefied in
  // tile units so the valid range for the X-axis is 0-39 and the
  // valid range for the Y-axis is 0-27.
  VDP_setTileMapXY(PLAN_A, VRAM_POS_TILE_SOLID, COORD_X, COORD_Y);

  // The rest of the program is essentially a busy-wait loop
  while(1)
  {
    VDP_waitVSync();
  }
}
