class Item:
    def __init__(self, name:str, value:int, weight:int):
        self.name = name
        self.value = value
        self.weight = weight

items = [
            Item("本",10,500), Item("傘",90,500), Item("下着",90,300), Item("ジャケット",30,1000),
            Item("薬",100,20), Item("MDプレーヤ",20,400), Item("地図",70,200), Item("宿チケット",100,10),
            Item("航空券",100,10), Item("洗面用具",50,300)
        ]
N = len(items)    # 候補数
sel = [False]*N   # N個だけFalseが並んだリスト
optsel = [False]*N
limw = 500
maxv = 0

import copy    # 配列のコピーを行うためにcopyモジュールをインポート

def try_item(i:int, tw:int, av:int):
    global sel, optsel, maxv
    
    # 現在考慮すべき品物(番号i)をカバンにつめる場合
    if tw+items[i].weight <= limw:    # 制限重量を越えていないのなら
        sel[i] = True    # カバンにつめる品物の集合に登録
        if i < N-1:    # 全ての品物を試したわけでないのなら
            try_item(i+1, tw+items[i].weight, av)    # 残りの品物についても考える
        elif av > maxv:    # 全品物を試し終わり今求めた組合せの価値が高い
            maxv = av
            optsel = copy.copy(sel)    # その組合せを現在の最適解として登録（selの内容をoptselにコピー）
        sel[i] = False    # 別解のため品物iをつめる品の集合から除く
        
    # 現在考慮すべき品物(番号i)をカバンにつめない場合
    av1 = av-items[i].value    # 品物iをつめないので到達可能な価値はその分下がる
    if av1 > maxv:    # 到達可能な価値が今までの最適値より大きければ望みがある
        if i < N-1:    # 全ての品物を試したわけでないのなら
            try_item(i+1, tw, av1)    # 残りの品物についても考える
        else:    # 到達可能な価値が今までの最適値よりも大きく，残りの品物もないので最適解として登録
            maxv = av1
            optsel = copy.copy(sel)

totv = sum([it.value for it in items])    # 総価値の計算
for limw in range(500, 3001, 500):    # いくつかの制限重量で計算
    # 選択品物の情報初期化
    maxv = 0
    sel = [False]*N
    optsel = [False]*N
    
    # 組み合わせを求める
    try_item(0, 0, totv)
    
    # 結果の表示
    print("重量制限 {:4d}gの場合: 総価値 {:3d}: ".format(limw, maxv), end="")
    sel_names = [] # optselで選択した品物の名前のリスト
    for it,s in zip(items,optsel):
        if s:
            sel_names.append(it.name)
    print(" ".join(sel_names))    # " "を挟んで結合して表示


