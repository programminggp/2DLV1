#pragma once
#include "stdio.h"
#include "CVector3.h"

class CLightBase {
private:
	CVector3 mPosition;
	CVector3 m_lightDir;
	CVector3 m_AmbientColor;
	CVector3 m_DiffuseColor;
public:
	void setPosition(const CVector3& v) {
		mPosition = v;
		m_lightDir = CVector3() - mPosition;
		m_lightDir = m_lightDir.normalize();
	}
	void setPosition(const CVector3& eye, const CVector3& tgt) {
		mPosition = eye;
		m_lightDir = tgt - mPosition;
		m_lightDir = m_lightDir.normalize();
	}
	void setDir(CVector3 v){
		m_lightDir = v;
	}
	void setColor(CVector3 a,CVector3 d){
		m_AmbientColor = a;
		m_DiffuseColor = d;
	}
	CVector3 getDir(){
		return m_lightDir;
	}
	CVector3 getAmbientColor(){
		return m_AmbientColor;
	}
	CVector3 getDiffuseColor(){
		return m_DiffuseColor;
	}
	CVector3 getPosition() {
		return mPosition;
	}

};
class CLight {
public:
	static const int LIGHT_MAX = 5;
private:
	static CLightBase *m_light;
public:
	static CLightBase* getLight(int no) {
		if(m_light==NULL) m_light = new CLightBase[LIGHT_MAX];
		return &m_light[no];
	}

};