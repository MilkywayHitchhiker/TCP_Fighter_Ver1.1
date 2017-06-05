#include"stdafx.h"
#include"Map.h"
#include"SpriteDib.h"

extern CSpriteDib g_cSprite;

void CMap::DrawMap (int LeftTopX, int LeftTopY, BYTE *bypDest, int iDestWidth, int iDestHeight, int iDestPitch)
{
	int TileIndexY;
	int TileIndexX;
	
	//XÁÂÇ¥ ¸Ê ¹þ¾î³ª´Â°Í Ã¼Å©
	if ( LeftTopX < 0 )
	{
		LeftTopX = 0;
	}
	else if(LeftTopX + 640 > dfRANGE_MOVE_RIGHT )
	{
		LeftTopX = dfRANGE_MOVE_RIGHT - 640;
	}

	//YÁÂÇ¥ ¸Ê ¹þ¾î³ª´Â°Í Ã¼Å©
	if ( LeftTopY < 0 )
	{
		LeftTopY = 0;
	}
	else if ( LeftTopY + 480 > dfRANGE_MOVE_BOTTOM )
	{
		LeftTopY = dfRANGE_MOVE_BOTTOM - 480;
	}

	LeftX = LeftTopX;
	TopY = LeftTopY;
	
	//¿ÞÂÊ »ó´Ü Ã¹¹øÂ° ¸ÊÀÇ ÁÂÇ¥¸¦ ±¸ÇÔ.
	TileIndexX = (int)LeftTopX / dfTileSize;
	TileIndexY = (int)LeftTopY / dfTileSize;

	//ÇØ´ç Ã¹¹øÂ° Å¸ÀÏÀÇ 0,0 ½ÃÀÛÁöÁ¡À» ±¸ÇÔ.
	int TileStartX = (TileIndexX * dfTileSize) - LeftTopX;
	int TileStartY = (TileIndexY * dfTileSize) - LeftTopY;

	int SetTilePosX = TileStartX;
	int SetTilePosY = TileStartY;

	for ( int cntY = 0; cntY < 9; cntY++ )
	{
		for ( int cntX = 0; cntX < 11; cntX++ )
		{
			g_cSprite.DrawImage (eTile, SetTilePosX, SetTilePosY,bypDest,iDestWidth,iDestHeight,iDestPitch);
			SetTilePosX += 64;
		}
		SetTilePosX = TileStartX;
		SetTilePosY += 64;
	}

}

int CMap::GetDrawPosX (void)
{
	return LeftX;
}
int CMap::GetDrawPosY (void)
{
	return TopY;
}