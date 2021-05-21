#ifndef CSCENETITLE_H
#define CSCENETITLE_H
#include "CText.h"
#include "CScene.h"
#include "CKey.h"
#include <Windows.h>
#include "CSound.h"
//・・・
#include "CSceneRace.h"

#define WAITTIME_STARTLOAD 60 //選択を決めてから次のシーンに移行するまでの時間
#define WAITTIME_NOWLOADING  WAITTIME_STARTLOAD - 10 //「NOW LOADING」が表示されるまでの時間

class CSceneTitle : public CScene {
public:
	//初期化処理のオーバーライド
	void Init() {
		//テクスチャファイルを読み込む
		//フォントの設定
		CText::mFont.Load("font2nd.tga");
		CText::mFont.SetRowCol(8, 256 / 16);
		CText::mFont2.Load("FontG.tga");
		CText::mFont2.SetRowCol(1, 4096 / 64);
		CText::mFont3.Load("FontDIY.tga");//自作フォント
		CText::mFont3.SetRowCol(8, 176 / 11);
		//CText::mFont3.Load("FontDIYx5.tga");//自作フォント
		//CText::mFont3.SetRowCol(8, 880 / 55);//サイズ5倍(没)
		

		//シーンの設定
		mScene = ETITLE;

		mSelectScene_Level = 1;
		mPrevDifficulty = mDifficulty;
		mVariable1 = 0;
		mPrevVariable1 = mVariable1;
		mVariable2 = 0;
		mPrevVariable2 = mVariable2;
		mStart = false;
		mStartWaitTime = 0;
		SoundMoveCarsol.Load("SE\\Carsol2.wav");
		SoundDecide.Load("SE\\Decision_Small(SF).wav");
		SoundCancel.Load("SE\\Cancel2.wav");
	}
	//更新処理のオーバーライド
	void Update() {
		//2D描画開始
		Start2D(0, 800, 0, 600);
		//R,G,B,α
		float c[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		//文字列の描画
		CText::DrawString("3D-RACE", -278 + 400 + 68, 430, 36, 36);
		//CText::DrawString("EXTREME", -278 + 400 + 68+96-24 +6*5, 377, 18, 18, 2);
		c[0] = c[1] = c[2] = 0.0f;
		glColor4fv(c);
		CText::DrawString("Demo Ver0.0", -278 + 400 + 68 + 131, 345+32, 8, 8, 3);
		c[0] = c[1] = c[2] = 1.0f;
		glColor4fv(c);
		CText::DrawString("Push Enter Key", 200, 177, 16, 16);
		//
		if (mSelectScene_Level == 1){
			CText::DrawString("[", 66 + mVariable2 * 250, 284 + mVariable1 * 50, 20, 30, 2);
			CText::DrawString("]", 262 + mVariable2 * 250, 284 + mVariable1 * 50, 20, 30, 2);
		}
		if (mSelectScene_Level == 2 && mStart == false){
			if (mDifficulty == 1){
				CText::DrawString("[", 190, 102, 16, 24, 2);
				CText::DrawString("]", 278, 102, 16, 24, 2);
			}
			if (mDifficulty == 2){
				CText::DrawString("[", 338, 102, 16, 24, 2);
				CText::DrawString("]", 474, 102, 16, 24, 2);
			}
			if (mDifficulty == 3){
				CText::DrawString("[", 534, 102, 16, 24, 2);
				CText::DrawString("]", 622, 102, 16, 24, 2);
			}
		}
		
		//ここより前は選択時に点滅しない
		if (mStartWaitTime > 20 || mStart == false){
			c[0] = c[1] = c[2] = 1.0f;
		}
		else if(mStartWaitTime % 8 < 4){
			c[0] = c[1] = c[2] = 0.5f;
		}
		glColor4fv(c);
		//ここから先は選択時に点滅させることが可能

		////モード選択と難易度選択でカーソルの基点も違う
		//if (mSelectScene_Level == 1){
		//	//CText::DrawString("O", 170 + mVariable2 * 250, 300 + mVariable1 * 50, 10, 10);
		//}
		////else if (mSelectScene_Level == 2){
		////	//if (mDifficulty == 1){
		////	//	//CText::DrawString("O", 175, 100, 10, 10);
		////	//	CText::DrawString("[", 190, 102, 16, 24, 2);
		////	//	CText::DrawString("]", 278, 102, 16, 24, 2);
		////	//}
		////	//if (mDifficulty == 2){
		////	//	//CText::DrawString("O", 323, 100, 10, 10);
		////	//	CText::DrawString("[", 338, 102, 16, 24, 2);
		////	//	CText::DrawString("]", 474, 102, 16, 24, 2);
		////	//}
		////	//if (mDifficulty == 3){
		////	//	//CText::DrawString("O", 519, 100, 10, 10);
		////	//	CText::DrawString("[", 534, 102, 16, 24, 2);
		////	//	CText::DrawString("]", 622, 102, 16, 24, 2);
		////	//}
		////	//CText::DrawString("O", -80 + mDifficulty * 250, 100, 10, 10);
		////}


		/*難易度選択(敵AIの強さ)*/
		if (mDifficulty == 1 && mSelectScene_Level == 2){//難易度:EASY
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mDifficulty == 1){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("EASY", 200, 100, 12, 12);

		if (mDifficulty == 2 && mSelectScene_Level == 2){//難易度:NORMAL
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mDifficulty == 2){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("NORMAL", 347, 100, 12, 12);

		if (mDifficulty == 3 && mSelectScene_Level == 2){//難易度:HARD
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mDifficulty == 3){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("HARD", 543, 100, 12, 12);

		/*モード選択(ステージ選択)の項目*/
		if (mVariable1 == 0 && mVariable2 == 0){
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mVariable1 == 0 && mVariable2 == 0){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("COURCE-1", 80, 280, 12, 14);

		if (mVariable1 == 0 && mVariable2 == 1){
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mVariable1 == 0 && mVariable2 == 1){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("COURCE-2", 330, 280, 12, 14);

		if (mVariable1 == 0 && mVariable2 == 2){
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mVariable1 == 0 && mVariable2 == 2){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		CText::DrawString("COURCE-3", 580, 280, 12, 14);

		//if (mVariable1 == -1 && mVariable2 == 0){
		//	c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		//}
		//else{
		//	c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		//}
		////選択時に点滅する
		//if (mStart && mVariable1 == -1 && mVariable2 == 0){
		//	if (mStartWaitTime > 20){
		//		c[0] = c[1] = c[2] = 1.0f;
		//	}
		//	else if (mStartWaitTime % 8 < 4){
		//		c[0] = c[1] = c[2] = 0.5f;
		//	}
		//}
		//glColor4fv(c);
		//CText::DrawString("Map-D", 80, 250, 16, 16);
		//
		//if (mVariable1 == -1 && mVariable2 == 1){
		//	c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		//}
		//else{
		//	c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		//}
		////選択時に点滅する
		//if (mStart && mVariable1 == -1 && mVariable2 == 1){
		//	if (mStartWaitTime > 20){
		//		c[0] = c[1] = c[2] = 1.0f;
		//	}
		//	else if (mStartWaitTime % 8 < 4){
		//		c[0] = c[1] = c[2] = 0.5f;
		//	}
		//}
		//glColor4fv(c);
		//CText::DrawString("Map-E", 330, 250, 16, 16);
		//
		//if (mVariable1 == -1 && mVariable2 == 2){
		//	c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		//}
		//else{
		//	c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		//}
		////選択時に点滅する
		//if (mStart && mVariable1 == -1 && mVariable2 == 2){
		//	if (mStartWaitTime > 20){
		//		c[0] = c[1] = c[2] = 1.0f;
		//	}
		//	else if (mStartWaitTime % 8 < 4){
		//		c[0] = c[1] = c[2] = 0.5f;
		//	}
		//}
		//glColor4fv(c);
		//CText::DrawString("Map-F", 580, 250, 16, 16);

		//最後に値を1.0fに戻す
		c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		glColor4fv(c);	

		
		
		char mrecord[70];// :も含めた最大文字数の設定
		if (mMode == 1){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_A / 10000 % 100, CSceneRace::mRecord_A / 100 % 100, CSceneRace::mRecord_A % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		else if (mMode == 2){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_B / 10000 % 100, CSceneRace::mRecord_B / 100 % 100, CSceneRace::mRecord_B % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		else if (mMode == 3){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_C / 10000 % 100, CSceneRace::mRecord_C / 100 % 100, CSceneRace::mRecord_C % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		else if (mMode == 4){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_D / 10000 % 100, CSceneRace::mRecord_D / 100 % 100, CSceneRace::mRecord_D % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		else if (mMode == 5){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_E / 10000 % 100, CSceneRace::mRecord_E / 100 % 100, CSceneRace::mRecord_E % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		else if (mMode == 6){
			sprintf(mrecord, "BEST:%02d:%02d:%02d", CSceneRace::mRecord_F / 10000 % 100, CSceneRace::mRecord_F / 100 % 100, CSceneRace::mRecord_F % 100);
			CText::DrawString(mrecord, 20, 580, 10, 12);
		}
		//シーンが移行する直前で表示
		if (mStartWaitTime > WAITTIME_NOWLOADING){
			CText::DrawString("Please Wait...", 555, 14, 9, 11);
		}
		//2D描画終了
		End2D();

		if (CKey::Once(VK_RETURN)){
			//開始フラグが建ったら連打しようが音は鳴らない
			if (mStart == false){
				SoundDecide.Play();
			}
			if (mSelectScene_Level < 2){
				//次に選ぶ項目へ
				mSelectScene_Level++;
			}
			else{
				//選び終えたらゲーム開始
				mStart = true;
			}
		}
		if (mStart){
			if (mStartWaitTime < WAITTIME_STARTLOAD){
				mStartWaitTime++;
			}
			else{
				//次のシーンはレース画面
				printf("選択したコース番号:No.%d  ", mMode);
				printf("選択したCPUのレベル:%d\n", mDifficulty);
				//選択したコースに対応するシーンへ移行			
				if (mMode == 1){
					//次のシーンはコース1
					mScene = ERACE1;
					//ECource mCource = ECOURCE1;
				}
				else if (mMode == 2){
					//次のシーンはコース2
					mScene = ERACE2;
					//ECource mCource = ECOURCE2;
				}
				else if (mMode == 3){
					//次のシーンはコース3
					mScene = ERACE3;
					//ECource mCource = ECOURCE3;
				}
				else if (mMode == 4){
					//次のシーンはコース3
					mScene = ERACE4;
					//ECource mCource = ECOURCE4;
				}
				else if (mMode == 5){
					//次のシーンはコース3
					mScene = ERACE5;
					//ECource mCource = ECOURCE4;
				}
				else if (mMode == 6){
					//次のシーンはコース3
					mScene = ERACE6;
					//ECource mCource = ECOURCE4;
				}
			}			
		}

		//まだ選択してない時
		if (mStart == false){
			//矢印キーで選択
			//選択画面1:モードの選択
			if (mSelectScene_Level == 1){
				//if (CKey::Once(VK_UP)){
				//	//次のシーンはゲーム
				//	if (mVariable1 < 0){
				//		mVariable1 += 1;
				//	}
				//}
				//if (CKey::Once(VK_DOWN)){
				//	//次のシーンはゲーム
				//	if (mVariable1 > -1){
				//		mVariable1 -= 1;
				//	}
				//}
				if (CKey::Once(VK_LEFT)){
					//次のシーンはゲーム
					if (mVariable2 > 0){
						mVariable2 -= 1;
					}
				}
				if (CKey::Once(VK_RIGHT)){
					//次のシーンはゲーム
					if (mVariable2 < 2){
						mVariable2 += 1;
					}
				}
			}
			//選択画面2：敵AIの強さの設定
			else if (mSelectScene_Level == 2){
				if (CKey::Once(VK_LEFT)){
					if (mDifficulty > 1){
						mDifficulty--;
					}
					else{
						mDifficulty = 3;
					}
				}
				if (CKey::Once(VK_RIGHT)){
					if (mDifficulty < 3){
						mDifficulty++;
					}
					else{
						mDifficulty = 1;
					}
				}
				//Escキーか、BackSpaceキーで、前の選択画面に戻る
				if (CKey::Once(VK_BACK) || CKey::Once(VK_ESCAPE)){
					mSelectScene_Level--;
					SoundCancel.Play();
				}
			}
		}
		if (mVariable1 == 0 && mVariable2 == 0){
			mMode = 1;
		}
		else if (mVariable1 == 0 && mVariable2 == 1){
			mMode = 2;
		}
		else if (mVariable1 == 0 && mVariable2 == 2){
			mMode = 5;
		}
		else if (mVariable1 == -1 && mVariable2 == 0){
			mMode = 4;
		}
		else if (mVariable1 == -1 && mVariable2 == 1){
			mMode = 3;
		}		
		else if (mVariable1 == -1 && mVariable2 == 2){
			mMode = 6;
		}

		//カーソルの場所が1f前と変わった瞬間
		if (mPrevVariable1 != mVariable1 || mPrevVariable2 != mVariable2 || mPrevDifficulty != mDifficulty){
			SoundMoveCarsol.Play();
			mPrevVariable1 = mVariable1;
			mPrevVariable2 = mVariable2;
			mPrevDifficulty = mDifficulty;
		}

	}
	//描画処理絶対君主
	void Render();

	//次のシーンの取得
	EScene GetNextScene();

	int mVariable1;
	int mPrevVariable1;
	int mVariable2;
	int mPrevVariable2;
	CSound SoundMoveCarsol;
	CSound SoundDecide;
	CSound SoundCancel;
	bool mStart;
	int mStartWaitTime;
	static int mMode;
	static int mDifficulty;
	int mPrevDifficulty;
	int mSelectScene_Level;//選択画面の何段階目か

	////各コースを列挙型で定義する
	//enum ECource
	//{
	//	ECOURCE1,
	//	ECOURCE2,
	//	ECOURCE3,
	//	ECOURCE4
	//};
	//static ECource mCource;
};

#endif