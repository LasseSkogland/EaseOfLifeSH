using namespace std;
#include <cstdlib>
#include "cavegenerator.h"

const int CAVE_BORN_MIN = 6;
const int CAVE_BORN_MAX = 8;
const int CAVE_SURVIVE_MIN = 3;
const int CAVE_SURVIVE_MAX = 8;
const int SMOOTH_MIN = 4;
const int SMOOTH_MAX = 9;

Tile *noiseMap;
const int MAX_SCAN_SIZE = 2048;
const int MAX_SIZE = (MAX_SCAN_SIZE * MAX_SCAN_SIZE) * sizeof(Tile);
int noiseSize;

const int R = RAND_MAX / 2;
#define randBool (rand() < R)

CaveGenerator::CaveGenerator(int noiseSize) {
	delete noiseMap;
	this->noiseSize = noiseSize;
	noiseMap = new Tile[MAX_SIZE];
}

void CaveGenerator::setSeed(Uint32 seed) {
	srand(seed);
}

Tile CaveGenerator::getTile(int x, int y) {
	return noiseMap[(y * noiseSize) + x];
}

void CaveGenerator::scaleUp() {
	int s = (noiseSize * noiseSize);
	const int SIZE = noiseSize * 2;
	Tile *old = new Tile[s];
	for (int i = 0; i < s; i++) {
		old[i] = noiseMap[i];
	}
	for (int z = 0; z < noiseSize; z++) {
		for (int x = 0; x < noiseSize; x++) {
			const int X = x * 2, Z = z * 2;
			noiseMap[(Z * SIZE) + X].type = old[(z * noiseSize) + x].type;
			noiseMap[(Z * SIZE) + X + 1].type = old[(z * noiseSize) + x].type;
			noiseMap[((Z + 1) * SIZE) + X].type = old[(z * noiseSize) + x].type;
			noiseMap[((Z + 1) * SIZE) + X + 1].type = old[(z * noiseSize) + x].type;
		}
	}
	delete[] old;
	noiseSize *= 2;
}

void CaveGenerator::generateNoise() {
	for (int y = 0; y < noiseSize; y++) {
		for (int x = 0; x < noiseSize; x++) {
			Tile &t = noiseMap[(y * noiseSize) + x];
			t.type = 0 == (rand() % 2) ? TILE_FLOOR : TILE_OUTERWALL;
		}
	}
}

void CaveGenerator::addOre() {
	for (int y = 0; y < noiseSize; y++) {
		for (int x = 0; x < noiseSize; x++) {
			Tile &t = noiseMap[(y * noiseSize) + x];
			t.updateNeighboors(this, x, y);
			if (t.neighbors.NUM4 == 4)
				t.type = TILE_INNERWALL;
		}
	}
}

void CaveGenerator::fixPathways() {

}

void CaveGenerator::applySmoothing() {
	for (int y = 1; y < noiseSize - 1; y++) {
		for (int x = 1; x < noiseSize - 1; x++) {
			Tile &t = noiseMap[(y * noiseSize) + x];
			t.updateNeighboors(this, x, y);
			if (t.neighbors.NUM8 < SMOOTH_MIN || t.neighbors.NUM8 > SMOOTH_MAX)
				noiseMap[(y * noiseSize) + x].type = TILE_FLOOR;
		}
	}
}

void CaveGenerator::applyCaves() {
	for (int y = 0; y < noiseSize; y++) {
		for (int x = 0; x < noiseSize; x++) {
			Tile &t = noiseMap[(y * noiseSize) + x];
			t.updateNeighboors(this, x, y);
			if (t.neighbors.NUM8 < CAVE_SURVIVE_MIN || t.neighbors.NUM8 > CAVE_SURVIVE_MAX)
				t.type = TILE_FLOOR;
			if (t.neighbors.NUM8 >= CAVE_BORN_MIN && t.neighbors.NUM8 <= CAVE_BORN_MAX)
				t.type = TILE_OUTERWALL;
		}
	}
}

void CaveGenerator::generate() {
	generateNoise();
	for (int i = 0; i < 20; i++)
		applyCaves();
	while (noiseSize < MAX_SCAN_SIZE) {
		scaleUp();
		for (int i = 0; i < 20; i++)
			applySmoothing();
	}
	int x = (noiseSize - 1) * noiseSize;
	addOre();
	for (int i = 0; i < noiseSize; i++) {
		noiseMap[i].type = TILE_END;
		noiseMap[x + i].type = TILE_END;
		noiseMap[(i * noiseSize)].type = TILE_END;
		noiseMap[(i * noiseSize) + x].type = TILE_END;
	}
}

