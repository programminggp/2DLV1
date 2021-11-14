#include "CSceneTitle.h"
#include "CRectangle.h"

#define WAITTIME_STARTLOAD 150 //選択決定後、次のシーン移行までの時間
#define WAITTIME_NOWLOADING  110 //「NOW LOADING」が表示されるまでの時間
#define WAITTIME_STARTFADEOUT  WAITTIME_STARTLOAD - 90 //「NOW LOADING」がフェードアウトが始まるまでの時間

//int CSceneTitle::mCource_Number = 1; //コースやLap数の初期設定
CSceneTitle::ECPU_Level CSceneTitle::mCPU_Level = CSceneTitle::ENORMAL;//敵AIの強さの初期設定

//int CSceneTitle::mCource_Number;//コースNo.
CSceneTitle::ECource CSceneTitle::mCource = CSceneTitle::ECOURCE1;

CSceneTitle::EMode CSceneTitle::mMode = CSceneTitle::EMODE_GRANDPRIX;

int CSceneTitle::RecordHigh_Ranking = ENEMYS_AMOUNT + 1;

//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene(){
	return mScene;
}

//初期化処理のオーバーライド
void CSceneTitle::Init() {
	//テクスチャファイルを読み込む
	//フォントの設定
	CText::mFont.Load("font\\font2nd.tga");
	CText::mFont.SetRowCol(8, 256 / 16);
	CText::mFont2.Load("font\\FontG.tga");
	CText::mFont2.SetRowCol(1, 4096 / 64);
	CText::mFont3.Load("font\\FontDIY.tga");//自作フォント
	CText::mFont3.SetRowCol(8, 176 / 11);
	//画像の読み込み
	Texture_GoldTrophy.Load("texture\\trophy_gold.tga");
	Texture_SilverTrophy.Load("texture\\trophy_silver.tga");
	Texture_BronzeTrophy.Load("texture\\trophy_bronze.tga");
	Texture_DetailGP.Load("texture\\detail_GP.tga");
	Texture_DetailTA.Load("texture\\detail_TA.tga");
	
	//シーンの設定
	mScene = ETITLE;

	mLevel = mCPU_Level;
	mCourceNum = mCource;
	mSelect_Step = 0;
	mCarsol_Pos = mCarsol_mode = 0;
	mStart = false;
	mStartWaitTime = 0;
	SoundMoveCarsol.Load("SE\\Carsol2.wav");
	SoundDecide.Load("SE\\Decision_Small(SF).wav");
	SoundCancel.Load("SE\\Cancel2.wav");	
}
//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)){
		//開始フラグが建ったら連打しようが音は鳴らない
		if (mStart == false){
			SoundDecide.Play();
		}

		if (mSelect_Step == 0){
			//次に選ぶ項目へ
			if (mCarsol_mode == 0)
				mSelect_Step = 2;
			else if (mCarsol_mode == 1)
				mSelect_Step = 1;
		}
		else if (mSelect_Step == 1 || mSelect_Step == 2){
			//選び終えたらゲーム開始
			mStart = true;
		}
	}

	if (mStart){
		if (mStartWaitTime < WAITTIME_STARTLOAD){
			mStartWaitTime++;
		}
		else{
			switch (mLevel)
			{
			case 1:
				mCPU_Level = EEASY;
				break;
			case 2:
				mCPU_Level = ENORMAL;
				break;
			case 3:
				mCPU_Level = EHARD;
				break;
			default:
				printf("不明な難易度を検出しました　難易度をnormalに設定します\n");
				mCPU_Level = ENORMAL;
				break;
			}
			
			//現在のレース数の初期化
			CSceneRace::mCurrent_RaceNumber = 0;

			if (mMode == EMODE_GRANDPRIX){
				printf("グランプリモード　CPUレベル:%d\n", mCPU_Level);
				//コース1→コース2→コース5の順に回る
				mCource = ECOURCE1;
				mScene = ERACE1;
				//mScene = ERACE;
			}				
			else if (mMode == EMODE_TIMEATTACK){
				printf("タイムアタックモード　コースNo.%d\n", mCource);
				//選択したコースに対応するシーンへ移行			
				if (mCource == 1){
					//次のシーンはコース1
					mScene = ERACE1;
				}
				else if (mCource == 2){
					//次のシーンはコース2
					mScene = ERACE2;
				}
				else if (mCource == 3){
					//次のシーンはコース3
					mScene = ERACE3;
				}
				else if (mCource == 4){
					//次のシーンはコース3
					mScene = ERACE4;
				}
				else if (mCource == 5){
					//次のシーンはコース3
					mScene = ERACE5;
				}
				else if (mCource == 0){
					//コースエディタに移行
					mScene = EEDIT;
				}
			}
			else{
				printf("シーン遷移に失敗しました\n");
				mStart = false;
				mStartWaitTime = 0;
			}
		}
	}
	//まだ選択してない時
	if (mStart == false){
		//矢印キーで選択

		//選択画面0:グランプリ(GP)モードorタイムアタック(TA)モードの選択
		if (mSelect_Step == 0){
			//←,→キーでコース選択
			if (CKey::Once(VK_UP)){
				//次のシーンはゲーム
				if (mCarsol_mode > 0){
					mCarsol_mode--;
					SoundMoveCarsol.Play();
				}
			}
			if (CKey::Once(VK_DOWN)){
				//次のシーンはゲーム
				if (mCarsol_mode < 1){
					mCarsol_mode++;
					SoundMoveCarsol.Play();
				}
			}
		}
		//選択画面1:コースの選択
		else if (mSelect_Step == 1){
			//←,→キーでコース選択
			if (CKey::Once(VK_LEFT)){
				//次のシーンはゲーム
				if (mCarsol_Pos > 0){
					mCarsol_Pos -= 1;
					SoundMoveCarsol.Play();
				}				
			}
			if (CKey::Once(VK_RIGHT)){
				//次のシーンはゲーム
				if (mCarsol_Pos < 2){
					mCarsol_Pos += 1;
					SoundMoveCarsol.Play();					
				}
			}
			//Escキーか、BackSpaceキーで、前の選択画面に戻る
			if (CKey::Once(VK_BACK) || CKey::Once(VK_ESCAPE)){
				mSelect_Step = 0;
				SoundCancel.Play();
			}
		}
		//選択画面2：敵AIの強さの設定
		else if (mSelect_Step == 2){
			if (CKey::Once(VK_LEFT)){
				if (mLevel > 1){
					mLevel--;
				}
				else{
					mLevel = 3;
				}
				SoundMoveCarsol.Play();
			}
			if (CKey::Once(VK_RIGHT)){
				if (mLevel < 3){
					mLevel++;
				}
				else{
					mLevel = 1;
				}
				SoundMoveCarsol.Play();
			}
			//Escキーか、BackSpaceキーで、前の選択画面に戻る
			if (CKey::Once(VK_BACK) || CKey::Once(VK_ESCAPE)){
				mSelect_Step = 0;
				SoundCancel.Play();
			}
		}
	}

	if (mMode == EMODE_TIMEATTACK){
		if (mCarsol_Pos == 0){
			mCource = ECOURCE1;
		}
		else if (mCarsol_Pos == 1){
			mCource = ECOURCE2;
		}
		else if (mCarsol_Pos == 2){
			mCource = ECOURCE5;
		}
	}	

	if (mCarsol_mode == 0)
		mMode = EMODE_GRANDPRIX;
	else if (mCarsol_mode == 1)
		mMode = EMODE_TIMEATTACK;

	Render();//テキスト等の描画
}

void CSceneTitle::Render(){
	//2D描画開始
	Start2D(0, 800, 0, 600);	
	float c[] = { 1.0f, 1.0f, 1.0f, 1.0f };//{ R,G,B,α }

	//文字列の描画
	CText::DrawString("3D-RACE", 190, 430, 36, 36);
	CText::DrawString("Push Enter Key", 200, 177, 16, 16);
	if (mSelect_Step == 0){//コース選択のカーソル
		CText::DrawString("[", 185, 312 + mCarsol_mode * -50, 20, 30, 2);
		CText::DrawString("]", 604, 312 + mCarsol_mode * -50, 20, 30, 2);
	}
	if (mSelect_Step == 1){//コース選択のカーソル
		CText::DrawString("[", 66 + mCarsol_Pos * 250, 104, 20, 30, 2);
		CText::DrawString("]", 262 + mCarsol_Pos * 250, 104, 20, 30, 2);
	}
	if (mSelect_Step == 2 && mStart == false){
		if (mLevel == 1){//CPUの強さ選択のカーソル
			CText::DrawString("[", 190, 102, 16, 24, 2);
			CText::DrawString("]", 278, 102, 16, 24, 2);
		}
		if (mLevel == 2){
			CText::DrawString("[", 338, 102, 16, 24, 2);
			CText::DrawString("]", 474, 102, 16, 24, 2);
		}
		if (mLevel == 3){
			CText::DrawString("[", 534, 102, 16, 24, 2);
			CText::DrawString("]", 622, 102, 16, 24, 2);
		}
	}

	//ここより前は選択時に点滅しない
	if (mStartWaitTime > 20 || mStart == false){
		c[0] = c[1] = c[2] = 1.0f;
	}
	else if (mStartWaitTime % 8 < 4){
		c[0] = c[1] = c[2] = 0.5f;
	}
	glColor4fv(c);
	//ここから先が選択完了時に点滅する

	
	//コース選択系のテキスト
	for (int i = 0; i <= 1; i++){
		if (mCarsol_mode == i){
			c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
		}
		else{
			c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
		}
		//選択時に点滅する
		if (mStart && mCarsol_mode == i){
			if (mStartWaitTime > 20){
				c[0] = c[1] = c[2] = 1.0f;
			}
			else if (mStartWaitTime % 8 < 4){
				c[0] = c[1] = c[2] = 0.5f;
			}
		}
		glColor4fv(c);
		
		if (i == 0){
			CText::DrawString("GRAND-PRIX MODE", 200, 310, 14, 17);
			
		}			
		else if (i == 1){
			CText::DrawString("TIMEATTACK MODE", 200, 260, 14, 17);
			
		}			
	}
	
	if (mCarsol_mode == 1){
		//コース選択系のテキスト
		for (int i = 0; i <= 2; i++){
			if (mCarsol_Pos == i && mSelect_Step == 1){
				c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
			}
			else{
				c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
			}
			//選択時に点滅する
			if (mStart && mCarsol_Pos == i){
				if (mStartWaitTime > 20){
					c[0] = c[1] = c[2] = 1.0f;
				}
				else if (mStartWaitTime % 8 < 4){
					c[0] = c[1] = c[2] = 0.5f;
				}
			}
			glColor4fv(c);
			if (i == 0){
				CText::DrawString("COURCE-1", 80, 100, 12, 14);
			}
			else if (i == 1){
				CText::DrawString("COURCE-2", 330, 100, 12, 14);
			}
			else if (i == 2){
				CText::DrawString("COURCE-3", 580, 100, 12, 14);
			}
		}
	}

	if (mCarsol_mode == 0){
		//CPUレベルのテキスト
		for (int i = 1; i <= 3; i++){
			if (mLevel == i && mSelect_Step == 2){
				c[0] = c[1] = c[2] = 1.0f; c[3] = 1.0f;
			}
			else{
				c[0] = c[1] = c[2] = 0.5f; c[3] = 1.0f;
			}
			//選択時に点滅する
			if (mStart && mLevel == i){
				if (mStartWaitTime > 20){
					c[0] = c[1] = c[2] = 1.0f;
				}
				else if (mStartWaitTime % 8 < 4){
					c[0] = c[1] = c[2] = 0.5f;
				}
			}
			glColor4fv(c);
			if (i == 1){
				CText::DrawString("EASY", 200, 100, 12, 12);
			}
			else if (i == 2){
				CText::DrawString("NORMAL", 347, 100, 12, 12);
			}
			else if (i == 3){
				CText::DrawString("HARD", 543, 100, 12, 12);
			}
		}
	}	
	//全ての値を1.0fに戻しておく
	c[0] = c[1] = c[2] = c[3] = 1.0f;
	glColor4fv(c);

	if (mSelect_Step == 0){
		if (mCarsol_mode == 0){
			CRectangle::RenderImage(Texture_DetailGP, 400, 40, 277, 15, 692, 38);
		}
		else if (mCarsol_mode == 1){
			CRectangle::RenderImage(Texture_DetailTA, 400, 40, 258, 15, 645, 38);
		}
	}
	if (mSelect_Step == 1){
		//そのコースのベスト記録が左上に表示される
		char record[16];
		if (mCource == 0){
			sprintf(record, "EDIT");
			CText::DrawString(record, 20, 580, 10, 12);
		}
		else{
			for (int i = 1; i <= COURCE_TOTAL; i++){
				if (mCource == i){
					sprintf(record, "BEST:%02d:%02d:%02d", CSceneRace::mRecords[i] / 10000 % 100, CSceneRace::mRecords[i] / 100 % 100, CSceneRace::mRecords[i] % 100);
					CText::DrawString(record, 20, 580, 10, 12);
				}
			}
		}
	}
	
	//グランプリの過去最高順位に応じてトロフィー表示
	switch (RecordHigh_Ranking)
	{
	case 1:
		CRectangle::RenderImage(Texture_GoldTrophy, 700, 444, 99, 99, 555, 555);
		break;
	case 2:
		CRectangle::RenderImage(Texture_SilverTrophy, 700, 444, 88, 88, 555, 555);
		break;
	case 3:
		CRectangle::RenderImage(Texture_BronzeTrophy, 700, 444, 77, 77, 555, 555);
		break;
	default:
		break;
	}
	
	c[0] = c[1] = c[2] = 1.0f;
	glColor4fv(c);
	
	//フェードアウトの表現
	if (mStartWaitTime >= WAITTIME_STARTFADEOUT){
		c[0] = c[1] = c[2] = 0.0f;
		c[3] = 0.025f * (mStartWaitTime - (WAITTIME_STARTFADEOUT));
		glColor4fv(c);
		CRectangle::Render(400, 300, 400, 300);
	}
	//全ての値を1.0fに戻しておく
	c[0] = c[1] = c[2] = c[3] = 1.0f;
	glColor4fv(c);
	
	//シーンが移行する直前で表示
	if (mStartWaitTime > WAITTIME_NOWLOADING){
		CText::DrawString("Please Wait...", 555, 14, 9, 11);
	}
	//2D描画終了
	End2D();
}