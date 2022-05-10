#pragma once
#include "CCharacter.h"
#include <vector>
/*
* CCharacterクラスのインスタンスを管理する
*/
class CCharacterManager
{
public:
	//staticメソッドは最初から作成され、
	//インスタンス不要で、どこでも呼ぶことができる。
	//CCharacterManagerのインスタンスのポインタを返す
	static CCharacterManager* Get();
	//Add(CChracterのポインタ)
	//可変長配列の後ろに追加する
	void Add(CCharacter* c);
	//可変長配列にあるポインタのUpdate()を実行していく
	void Update();
	//可変長配列にあるポインタのRender()を実行していく
	void Render();
	void Collision();
	//可変長配列にあるポインタのmEnabledが
	//falseのインスタンスを削除していく
	void Delete();
private:
	//CCharacterのポインタの可変長配列
	std::vector<CCharacter*> mpCharacters;
};
