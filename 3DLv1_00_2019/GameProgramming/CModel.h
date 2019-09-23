#ifndef CMODEL_H
#define CMODEL_H
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char *model,char *mtl);
};

#endif
