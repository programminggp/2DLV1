#include "CXCharacter.h"

//キャラクタからのカメラの相対位置
#define CAMERA_POSITION 0.0f, 4.0f, -6.0f
#define TARGET_POSITION 0.0f, 3.0f, 6.0f

/*
Init
初期化処理
*/
void CXCharacter::Init(CModelX *model) {
	mpModel = model;
	//合成行列退避エリアの確保
	mpCombinedMatrix = new CMatrix44[model->mFrame.size()];
	//最初のアニメーションにする
	mAnimationIndex = 0;
	//繰り返し再生する
	mAnimationLoopFlg = true;
	//1アニメーション60フレーム
	mAnimationFrameSize = 60.0f;
	//アニメーションのフレームを最初にする
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
	//アニメーションの重みを1.0（100%)にする
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
	mState = EIDLE;
	mScale = CVector3(1.0f, 1.0f, 1.0f);
}

/*
ChangeAnimation
アニメーションを切り替える
index:アニメーションの番号
loop:true 繰り返す
framesize：最後まで再生するのに使用されるフレーム数
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//同じ場合は切り替えない
	if (mAnimationIndex == index) return;
	//今のアニメーションの重みを0.0（0%)にする
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 0.0f;
	//番号、繰り返し、フレーム数を設定
	mAnimationIndex = index % mpModel->mAnimationSet.size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//アニメーションのフレームを最初にする
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
	//アニメーションの重みを1.0（100%)にする
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}

/*
Update
更新する
matrix：移動、回転、拡大縮小の行列
*/
void CXCharacter::Update(CMatrix44 &matrix, bool addframe = true) {
	//24 アニメーションセットのリセット
	for (int i = 0; i < mpModel->mAnimationSet.size(); i++) {
		mpModel->mAnimationSet[i]->mWeight = 0.0f;
	}
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;

	//最後まで再生していない
	if (mAnimationFrame < mAnimationFrameSize) {
		//アニメーションの時間を計算
		if (addframe)
			//フレームを進める
			mAnimationFrame++;
	}
	else {
		//繰り返しの場合は、フレームを0に戻す
		if (mAnimationLoopFlg) {
			//アニメーションのフレームを最初にする
			mAnimationFrame = 0.0f;
		}
	}
	//アニメーションの時間を計算
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mpModel->mAnimationSet[mAnimationIndex]->mMaxTime * mAnimationFrame / mAnimationFrameSize;
	//フレームの変換行列をアニメーションで更新する
	mpModel->AnimateFrame();
	//フレームの合成行列を計算する
	mpModel->mFrame[0]->Animate(&matrix);
	//合成行列の退避
	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
}

/*
描画する
*/
void CXCharacter::Render() {
	//位置調整
	mPosition = mPosition + mAdjust;
	//描画する
	mpModel->RenderShader(mpCombinedMatrix);
}
//更新処理
void CXCharacter::Update() {
	CMatrix44 pos, rot, rotx, rotz, scale;;
	//位置の行列を取得
	pos.translate(mPosition);
	//回転（Y軸）の行列を取得
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	rotz.rotationZ(mRotation.z);
	scale.scale(mScale);
	//位置回転行列計算
	mMatrix = pos * rot * rotx * rotz * scale;
	//アニメーションを更新する
	Update(mMatrix);
}
//重力処理
void CXCharacter::Gravity() {
	//速度分移動
	mPosition.y += mVelocityG;
	//速度を加速
	mVelocityG -= 0.01f;
}
//カメラ位置の取得
CVector3 CXCharacter::GetCameraPosition() {
	CMatrix44 pos, rot, rotx, Matrix;
	//位置の行列を取得
	pos.translate(mPosition);
	//回転（Y軸）の行列を取得
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	//位置回転行列計算
	Matrix = pos * rot * rotx;
	CMatrix44 crot;
	//回転（Y軸）の行列を取得
	crot.rotationY(mCameraRotation.y);
	return CVector3(CAMERA_POSITION) * crot * Matrix;
}
//カメラ位置の取得
CVector3 CXCharacter::GetTargetPosition() {
	CMatrix44 pos, rot, rotx, Matrix;
	//位置の行列を取得
	pos.translate(mPosition);
	//回転（Y軸）の行列を取得
	rot.rotationY(mRotation.y);
	rotx.rotationX(mRotation.x);
	//位置回転行列計算
	Matrix = pos * rot * rotx;
	CMatrix44 crot;
	//回転（Y軸）の行列を取得
	crot.rotationY(mCameraRotation.y);
	return CVector3(TARGET_POSITION) * crot * Matrix;
}

void CXCharacter::UpdateAdjust(const CVector3 v) {
	if (mAdjust.x < abs(v.x))
		mAdjust.x = v.x;
	if (mAdjust.y < abs(v.y))
		mAdjust.y = v.y;
	if (mAdjust.z < abs(v.z))
		mAdjust.z = v.z;
}
