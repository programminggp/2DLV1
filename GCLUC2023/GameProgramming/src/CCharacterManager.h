#pragma once
#include "CCharacter.h"
#include <vector>
/*
* CCharacterクラスのインスタンスを管理する
*/
class CCharacterManager
{
private:
	//CCharacterのポインタの可変長配列
	std::vector<CCharacter*> mpCharacters;
	//キャラクターマネージャーのインスタンス
	static CCharacterManager* mpinstance;
public:
	//全インスタンス削除
	void AllDelete();
	//不要なポインタを削除する
	void Delete();
	//インスタンス作成
	static CCharacterManager* Instance();

	//衝突処理１
	void Collision();
	//衝突処理３
	//Collision(衝突元のポインタ)
	void Collision(CCharacter* character);

	//Add(CChracterのポインタ)
	//可変長配列の後ろに追加する
	void Add(CCharacter* c);
	//可変長配列にあるポインタのUpdate()を実行していく
	void Update();
	//可変長配列にあるポインタのRender()を実行していく
	void Render();

};