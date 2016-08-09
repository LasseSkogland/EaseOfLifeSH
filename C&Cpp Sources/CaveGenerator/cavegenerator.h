#ifndef SRC_CAVEGENERATOR_H_
#define SRC_CAVEGENERATOR_H_
#include <SDL2/SDL.h>
#include "global.h"

class Tile;

class CaveGenerator {
private:
	void scaleUp();
public:
	int noiseSize;
	CaveGenerator(int = 64);
	void setSeed(Uint32);
	Tile getTile(int, int);
	void generateNoise();
	void applyCaves();
	void applySmoothing();
	void addOre();
	void fixPathways();
	void generate();
};

const int TILE_COLOR_FLOOR = BYTES_TO_INT(119, 119, 119, 255);
const int TILE_COLOR_OUTERWALL = BYTES_TO_INT(255, 255, 255, 255);
const int TILE_COLOR_INNERWALL = BYTES_TO_INT(221, 221, 221, 255);

const unsigned char TILE_FLOOR = 0;
const unsigned char TILE_OUTERWALL = 1;
const unsigned char TILE_INNERWALL = 2;
const unsigned char TILE_END = 255;

typedef struct Neighbors {
	bool NW;
	bool N;
	bool NE;
	bool W;
	bool E;
	bool SW;
	bool S;
	bool SE;
	int NUM8, NUM4;
} Neighbors;
class Tile {
public:
	int type;
	Neighbors neighbors;

	void updateNeighboors(CaveGenerator *cg, int x, int y) {
		neighbors.NUM8 = neighbors.NUM4 = 0;
		neighbors.NUM8 += neighbors.NW = cg->getTile(x - 1, y - 1).type != TILE_FLOOR;
		neighbors.NUM4 += neighbors.N = cg->getTile(x, y - 1).type != TILE_FLOOR;
		neighbors.NUM8 += neighbors.NE = cg->getTile(x + 1, y - 1).type != TILE_FLOOR;
		neighbors.NUM4 += neighbors.W = cg->getTile(x - 1, y).type != TILE_FLOOR;
		neighbors.NUM4 += neighbors.E = cg->getTile(x + 1, y).type != TILE_FLOOR;
		neighbors.NUM8 += neighbors.SW = cg->getTile(x - 1, y + 1).type != TILE_FLOOR;
		neighbors.NUM4 += neighbors.S = cg->getTile(x, y + 1).type != TILE_FLOOR;
		neighbors.NUM8 += neighbors.SE = cg->getTile(x + 1, y + 1).type != TILE_FLOOR;
		neighbors.NUM8 += neighbors.NUM4;
	}

};

#endif /* SRC_CAVEGENERATOR_H_ */
