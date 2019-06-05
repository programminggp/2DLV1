#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CRectangle.h"
//#include "CTask.h"

class CSceneGame;

//class CCharacter : public CRectangle, public CTask {
class CCharacter : public CRectangle {
public:
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		ESHOOTPLAYER,
		ESHOOTBOSS,
		ESHOOTENEMY,
		EENEMY
	};

	ETag mTag;

	//enum EState {
	//	EDISABLED,
	//	EENABLED,
	//	false,
	//};

	bool mEnabled;

	CCharacter();
	virtual ~CCharacter();

	virtual void Update() {};
	virtual void Render() {};
	virtual void Collision(CCharacter* mc, CCharacter* yc) {};

};

#endif
