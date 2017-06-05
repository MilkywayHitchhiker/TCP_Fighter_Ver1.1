#include"stdafx.h"
#include"Map.h"
#include"SpriteDib.h"

extern CSpriteDib g_cSprite;

void CMap::DrawMap (int LeftTopX, int LeftTopY, BYTE *bypDest, int iDestWidth, int iDestHeight, int iDestPitch)
{
	int TileIndexY;
	int TileIndexX;
	
	//X��ǥ �� ����°� üũ
	if ( LeftTopX < 0 )
	{
		LeftTopX = 0;
	}
	else if(LeftTopX + 640 > dfRANGE_MOVE_RIGHT )
	{
		LeftTopX = dfRANGE_MOVE_RIGHT - 640;
	}

	//Y��ǥ �� ����°� üũ
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
	
	//���� ��� ù��° ���� ��ǥ�� ����.
	TileIndexX = (int)LeftTopX / dfTileSize;
	TileIndexY = (int)LeftTopY / dfTileSize;

	//�ش� ù��° Ÿ���� 0,0 ���������� ����.
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