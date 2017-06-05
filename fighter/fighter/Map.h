#pragma once

#include"stdafx.h"
#include"SpriteDib.h"
#include"DefineEnum.h"

#define dftileMap_Max 100
#define dfTileSize 64

class CMap
{
protected :

	BYTE TileMap[dftileMap_Max][dftileMap_Max];
	int LeftX;
	int TopY;

public :

	CMap (void)
	{
		memset (TileMap, 0, sizeof (TileMap));
	}
	~CMap ()
	{

	}
	void DrawMap (int LeftTopX, int LeftTopY, BYTE *bypDest, int iDestWidth, int iDestHeight, int iDestPitch);
	int GetDrawPosX (void);
	int GetDrawPosY (void);

};