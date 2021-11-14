#ifndef CROADMANAGER_H
#define CROADMANAGER_H

#include "CObjFloor.h"

class CRoadManager : public CObjFloor
{
public:
	//CRoadManager(モデルデータのポインタ,位置,回転,拡大縮小,スタート位置,進行方向,各ポイントの半径,ポイント間の最小の間隔)
	CRoadManager(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval=1);
	//Init(モデルデータのポインタ,位置,回転,拡大縮小,スタート位置,進行方向,各ポイントの半径,ポイント間の最小の間隔)
	void Init(CModel*, const CVector& pos, const CVector& rot, const CVector& scale, const CVector& startPos, const CVector& foward, const float radius, const float interval=1);
};

#endif
