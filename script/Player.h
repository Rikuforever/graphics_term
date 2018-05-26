#define PLAYER_H

#include "GameObject.h"
#include "GameMap.h"

#include "glm/gtc/constants.hpp"
#include <math.h>

enum CubeStatus { Moving, Climbing, Falling };

struct Cube
{
	GameObject* objPtr;
	
	float ad_angle = 10;
	float full_x_angle = 0;
	float full_z_angle = 0;
	float xangle = 0;
	float yangle = 0;
	float zangle = 0;
	glm::vec3 position;
	int dx = 0;
	int dy = 0;
	int dz = 0;
	glm::vec3 center;
	int mapScan = 0;
	CubeStatus cstatus = Moving;
	int UseMethod = 0;;
};

#pragma region Function List
void Move_Method1(Cube* pcube);
void Move_Method2(Cube* pcube);
void Move_Method3(Cube* pcube);
void Move_Method4(Cube* pcube);
void Move_Method5(Cube* pcube);
void Move_Method6(Cube* pcube);
void CubeFall(Cube*pcube);
void ScanMap(Cube* pcube);
void DefineCubeLine(Cube* pcube);
void SetDeltaPosition(Cube*);
void KeyMethod(Cube*);
void SetCubePosition(Cube *pcube, float x, float y, float z);
glm::vec3 GetCubeCenter(Cube* pcube);
#pragma endregion 

Cube cube;
Cube* pcube = &cube;
char keymode = '.';
int mode = 1;
GameMap* mapdata;

void DefineCubeLine(Cube* pcube) {
	int tempx = (int)(pcube->full_x_angle) % 90;
	int tempz = (int)(pcube->full_z_angle) % 90;
	if (tempx == 0 && tempz == 0) {
		GetCubeCenter(pcube);
		ScanMap(pcube);
		CubeFall(pcube);
		if (pcube->cstatus != Falling) {
			KeyMethod(pcube);
		}
	}
}

void CubeFall(Cube*pcube) {
	int mapScan = pcube->mapScan;
	if ((mapScan | 1) != mapScan) {
		if (pcube->cstatus == Climbing) {
			switch (keymode) {
			case 'a':
				if ((pcube->mapScan | 32) == mapScan) {
					pcube->cstatus = Falling;
				}
				else {
					pcube->cstatus = Moving;
				}
				break;
			case 'd':
				if ((pcube->mapScan | 64) == mapScan) {
					pcube->cstatus = Falling;
				}
				else {
					pcube->cstatus = Moving;
				}
				break;
			case 'w':
				if ((pcube->mapScan | 1024) == mapScan) {
					pcube->cstatus = Falling;
				}
				else {
					pcube->cstatus = Moving;
				}
				break;
			case 's':
				if ((pcube->mapScan | 1024) == mapScan) {
					pcube->cstatus = Falling;
				}
				else {
					pcube->cstatus = Moving;
				}
				break;


			default:
				break;
			}
		}
		else {
			float frame = 2.0;
			pcube->yangle -= 90.0 / frame;
			pcube->position.y -= 1.0 / frame;
			pcube->cstatus = Falling;
		}
	}
	else {
		pcube->cstatus = Moving;
	}
}

void Move_Method1(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'd') {
		pcube->full_x_angle += ad_angle;
		pcube->xangle += ad_angle;
	}
	else if (keymode == 'a') {
		pcube->full_x_angle -= ad_angle;
		pcube->xangle -= ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_x_angle = abs(((int)pcube->full_x_angle) % 90);
	pcube->position.x = cube.dx + 0.5 + (sqrt(2) / 2.0)*cos((135 - modular_x_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + (-0.5) + (sqrt(2) / 2.0)*sin((135 - modular_x_angle)*glm::pi<float>() / 180.0);
}

void Move_Method2(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'd') {
		pcube->full_x_angle += ad_angle;
		pcube->yangle += ad_angle;
	}
	else if (keymode == 'a') {
		pcube->full_x_angle -= ad_angle;
		pcube->yangle -= ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_x_angle = abs(((int)pcube->full_x_angle) % 90);
	pcube->position.x = cube.dx + 0.5 + (sqrt(2) / 2.0)*cos((225 - modular_x_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + 0.5 + (sqrt(2) / 2.0)*sin((225 - modular_x_angle)*glm::pi<float>() / 180.0);
}

void Move_Method3(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'd') {
		pcube->full_x_angle += ad_angle;
		pcube->yangle -= ad_angle;
	}
	else if (keymode == 'a') {
		pcube->full_x_angle -= ad_angle;
		pcube->yangle += ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_x_angle = abs(((int)pcube->full_x_angle) % 90);
	pcube->position.x = cube.dx + (-0.5) + (sqrt(2) / 2.0)*cos((45 - modular_x_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + 0.5 + (sqrt(2) / 2.0)*sin((45 - modular_x_angle)*glm::pi<float>() / 180.0);
	if (modular_x_angle == 0) {
		pcube->position.y -= 1;
	}
}

void Move_Method4(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'w') {
		pcube->full_z_angle -= ad_angle;
		pcube->zangle -= ad_angle;
	}
	else if (keymode == 's') {
		pcube->full_z_angle += ad_angle;
		pcube->zangle += ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_z_angle = abs(((int)pcube->full_z_angle) % 90);
	pcube->position.z = cube.dz + 0.5 + (sqrt(2) / 2.0)*cos((135 - modular_z_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + (-0.5) + (sqrt(2) / 2.0)*sin((135 - modular_z_angle)*glm::pi<float>() / 180.0);
}

void Move_Method5(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'w') {
		pcube->full_z_angle -= ad_angle;
		pcube->yangle -= ad_angle;
	}
	else if (keymode == 's') {
		pcube->full_z_angle += ad_angle;
		pcube->yangle += ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_z_angle = abs(((int)pcube->full_z_angle) % 90);
	pcube->position.z = cube.dz + 0.5 + (sqrt(2) / 2.0)*cos((225 - modular_z_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + 0.5 + (sqrt(2) / 2.0)*sin((225 - modular_z_angle)*glm::pi<float>() / 180.0);
}
void Move_Method6(Cube* pcube) {
	float ad_angle = pcube->ad_angle;
	if (keymode == 'w') {
		pcube->full_z_angle += ad_angle;
		pcube->yangle += ad_angle;
	}
	else if (keymode == 's') {
		pcube->full_z_angle -= ad_angle;
		pcube->yangle -= ad_angle;
	}
	SetDeltaPosition(pcube);
	float modular_z_angle = abs(((int)pcube->full_z_angle) % 90);
	pcube->position.z = cube.dz + (-0.5) + (sqrt(2) / 2.0)*cos((45 - modular_z_angle)*glm::pi<float>() / 180.0);
	pcube->position.y = cube.dy + 0.5 + (sqrt(2) / 2.0)*sin((45 - modular_z_angle)*glm::pi<float>() / 180.0);
	if (modular_z_angle == 0) {
		pcube->position.y -= 1;
	}
}

void KeyMethod(Cube* pcube) {
	int mapScan = pcube->mapScan;
	switch (keymode) {
	case 'd':
		if ((mapScan | 2) == mapScan) {
			pcube->cstatus = Climbing;
			pcube->UseMethod = 2;
		}
		else {
			pcube->UseMethod = 1;
		}
		break;

	case 'a':
		if ((mapScan | 4) == mapScan) {
			pcube->cstatus = Climbing;
			pcube->UseMethod = 3;
		}
		else {
			pcube->UseMethod = 1;
		}
		break;

	case 'w':
		if ((mapScan | 8) == mapScan) {
			pcube->cstatus = Climbing;
			pcube->UseMethod = 6;
		}
		else {
			pcube->UseMethod = 4;
		}
		break;

	case 's':
		if ((mapScan | 16) == mapScan) {
			pcube->cstatus = Climbing;
			pcube->UseMethod = 5;
		}
		else {
			pcube->UseMethod = 4;
		}
		break;
	default:
		break;
	}
}


void Move(Cube* pcube) {
	if (pcube->cstatus != Falling) {
		switch (pcube->UseMethod) {
		case 1:
			Move_Method1(pcube);
			break;
		case 2:
			Move_Method2(pcube);
			break;
		case 3:
			Move_Method3(pcube);
			break;
		case 4:
			Move_Method4(pcube);
			break;
		case 5:
			Move_Method5(pcube);
			break;
		case 6:
			Move_Method6(pcube);
			break;
		}
	}
}

glm::vec3 GetCubeCenter(Cube* pcube) {
	pcube->center.x = pcube->position.x;
	pcube->center.y = pcube->position.y;
	pcube->center.z = pcube->position.z;
	return pcube->center;
}

void SetDeltaPosition(Cube* pcube) {
	if (pcube->full_x_angle<0) {
		pcube->full_x_angle += 360;
	}
	if (pcube->full_z_angle<0) {
		pcube->full_z_angle += 360;
	}
	pcube->dx = floor(cube.xangle / 90);
	pcube->dy = floor(cube.yangle / 90);
	pcube->dz = floor(cube.zangle / 90);
}



void ScanMap(Cube* pcube) {
	int cube_data = pcube->center.x + 100 * pcube->center.y + 10000 * pcube->center.z;
	pcube->mapScan = 0;
	if (mapdata->getData(x,y - 1,z) == 1 mapdata.count(cube_data - 100)) {
		pcube->mapScan = pcube->mapScan | 1;
	}
	if (mapdata->getData(x + 1, y, z) == 1 mapdata.count(cube_data + 1)) {
		pcube->mapScan = pcube->mapScan | 2;
	}
	if (mapdata->getData(x - 1, y, z) == 1 mapdata.count(cube_data - 1)) {
		pcube->mapScan = pcube->mapScan | 4;
	}
	if (mapdata->getData(x, y, z - 1) == 1 mapdata.count(cube_data - 10000)) {
		pcube->mapScan = pcube->mapScan | 8;
	}
	if (mapdata->getData(x, y, z + 1) == 1 mapdata.count(cube_data + 10000)) {
		pcube->mapScan = pcube->mapScan | 16;
	}
	if (mapdata->getData(x + 1, y - 1, z) == 1 mapdata.count(cube_data - 99)) {
		pcube->mapScan = pcube->mapScan | 32;
	}
	if (mapdata->getData(x - 1, y - 1, z) == 1 mapdata.count(cube_data - 101)) {
		pcube->mapScan = pcube->mapScan | 64;
	}
	if (mapdata->getData(x - 1, y + 1, z) == 1 mapdata.count(cube_data + 99)) {
		pcube->mapScan = pcube->mapScan | 128;
	}
	if (mapdata->getData(x + 1, y + 1, z) == 1 mapdata.count(cube_data + 101)) {
		pcube->mapScan = pcube->mapScan | 256;
	}
	if (mapdata->getData(x, y - 1, z - 1) == 1 mapdata.count(cube_data - 10100)) {
		pcube->mapScan = pcube->mapScan | 512;
	}
	if (mapdata->getData(x, y - 1, z + 1) == 1 mapdata.count(cube_data + 9900)) {
		pcube->mapScan = pcube->mapScan | 1024;
	}
	if (mapdata->getData(x, y + 1, z - 1) == 1 mapdata.count(cube_data - 9900)) {
		pcube->mapScan = pcube->mapScan | 2048;
	}
	if (mapdata->getData(x, y + 1, z + 1) == 1 mapdata.count(cube_data + 10100)) {
		pcube->mapScan = pcube->mapScan | 4096;
	}
}
