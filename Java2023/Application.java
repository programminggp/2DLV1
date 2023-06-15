
//インポートしたパッケージのクラスは、
//クラス名だけで使用できます。
import javax.swing.*;
//インポートにクラスを指定することもできます。
//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;
//awtパッケージをインポート
import java.awt.*;
//イベントの取得
import java.awt.event.*;
//ArrayListのインポート
import java.util.*;

//ベースクラス
class Base {
	boolean enabled; // 有効フラグ：true：有効
	int vx; // vx:x移動量
	int vy; // vx:x移動量
	int x; // 中心X座標
	int y; // 中心Y座標
	int w; // 中心からの幅
	int h; // 中心からの高さ

	// Base() {
	// System.out.println("Base constructor");
	// }

	// X座標、Y座標、幅、高さの設定
	Base(int x, int y, int width, int height) {
		enabled = true; // 有効とする
		vx = 0;
		this.x = x;
		this.y = y;
		w = width;
		h = height;
		//BaseManagerに追加
		BaseManager.add(this);
	}

	void update() {
	}

	// 描画
	void draw(Graphics g) {
		// 四角形の描画
		g.setColor(Color.yellow);
		g.fillRect(x - w, y - h, w * 2, h * 2);
	}
	//衝突検出処理
	//a と b が衝突していればtrue
	boolean collision(Base a, Base b) {
		int dist;
		// X軸での距離の絶対値を求める
		dist = Math.abs(a.x - b.x);
		// 幅の合計以上か？
		if (dist >= a.w + b.w) {
			// 当たっていない
			return false;
		}
		// 課題
		dist = Math.abs(a.y - b.y);
		if (dist >= a.h + b.h) {
			return false;
		}
		// 当たっている
		return true;
	}

	//衝突処理１
	void collision() {
		BaseManager.collision(this);
	}
	//衝突処理２
	void collision(Base base) {
		if (collision(this, base)) {
			enabled = false;
		}
	}
}

class Enemy extends Base {
	static final int WIDTH = 20;
	static final int HEIGHT = 16;
	static final Color COLOR = Color.blue;
	Enemy(int x, int y)
	{
		super(x,y,WIDTH,HEIGHT);
	}

	void draw(Graphics g)
	{
		// 翼の描画
		g.setColor(COLOR);
		g.fillOval(x - w, y - h / 2, w * 2, h);
		// 機体の描画
		g.setColor(Color.white);
		g.fillOval(x - w / 4, y - h, w / 2, h * 2);
	}
}



class Bullet extends Base {
	// 定数の定義
	static final int WIDTH = 1; // 幅
	static final int HEIGHT = 5; // 高さ
	int life;

	Bullet(int x, int y) {
		super(x, y, WIDTH, HEIGHT);
		life = 25;
	}

	void update() {
		if (life > 0) {
			life--;
			y -= h * 2;
		} else {
			enabled = false; // 無効にする
		}
	}
	//衝突処理１
	void collision() {
		BaseManager.collision(this);
	}
	//衝突処理２
	//base：相手のインスタンス
	void collision(Base base) {
		//this自分と相手が衝突したら無効にする
		if (collision(this, base)) {
			enabled = false;
		}
	}
}

// プレイヤークラス
class Player extends Base implements KeyListener {
	Color color; // 色

	Player(int x, int y, int w, int h, Color c) {
		super(x, y, w, h);
		color = c;
	}

	void update() {
		x += vx;
		y += vy;
	}

	// 機体の描画
	void draw(Graphics g) {
		// 翼の描画
		g.setColor(color);
		g.fillOval(x - w, y - h / 2, w * 2, h);
		// 機体の描画
		g.setColor(Color.white);
		g.fillOval(x - w / 4, y - h, w / 2, h * 2);
	}

	public void keyTyped(KeyEvent e) {
	}

	public void keyPressed(KeyEvent e) {
		switch (e.getKeyCode()) {
			case KeyEvent.VK_A:
				vx = -4;
				break;
			case KeyEvent.VK_D:
				vx = 4;
				break;
			case KeyEvent.VK_W:
				vy = -4;
				break;
			case KeyEvent.VK_S:
				vy = 4;
				break;
			case KeyEvent.VK_SPACE:
				// 弾を生成して可変長配列に追加する
//				BaseManager.add(new Bullet(x, y - h));
				new Bullet(x, y - h);
				break;
		}
	}

	public void keyReleased(KeyEvent e) {
		switch (e.getKeyCode()) {
			case KeyEvent.VK_A:
			case KeyEvent.VK_D:
				vx = 0;
				break;
			case KeyEvent.VK_W:
			case KeyEvent.VK_S:
				vy = 0;
				break;
		}
	}

	void collision(Base base) {
		if (collision(this, base)) {
			color = Color.yellow;
		} else {
			color = Color.red;
		}
	}
}

// 星クラスの定義
class Star {
	int x; // 星のx座標(x)
	int y; // 星のy座標(y)
	int d; // 直径(d)
	Color c; // 色(c)
	// コンストラクタ(X座標,Y座標,直径,色)

	Star(int x, int y, int diameter, Color color) {
		// メンバ変数の設定
		this.x = x; // this.xはクラスのメンバ変数、xは引数
		this.y = y;
		d = diameter;
		c = color;
	}

	// 描画する
	void draw(Graphics g) {
		// 円の描画
		g.setColor(c);
		g.fillOval(x, y, d, d);
	}

	// 更新処理
	void update() {
		y += d;
		if (y > 400) {
			y = 0;
		}
	}
}

//Baseクラスの管理クラス
class BaseManager {
	//可変長配列
	static ArrayList<Base> arrayList = new ArrayList<Base>();
	//追加処理
	static void add(Base base) {
		arrayList.add(base);
	}
	//更新処理
	static void update() {
		//拡張for文
		for(Base base : arrayList)
		{
			base.update();
		}
	}
	//描画処理
	static void draw(Graphics g) {
		for (int i = 0; i < arrayList.size(); i++) {
			arrayList.get(i).draw(g);
		}
	}
	static void remove() {
		// enabledがfalseの要素を削除するラムダ式
		arrayList.removeIf(base -> base.enabled == false);
	}

	//衝突処理１
	//全要素の衝突処理１を呼び出す
	static void collision() {
		//拡張for文
		for(Base base : arrayList)
		{
			base.collision();
		}
	}
	//衝突処理２
	//baseの衝突処理２を、全要素に対して行う
	static void collision(Base base) {
		//イテレータの作成
		Iterator<Base> iterator = arrayList.iterator();
		//次の要素があるか判定
		while (iterator.hasNext()) {
			//イテレータで次の要素取り出して代入
			Base element = iterator.next();
			if(element != base)
			{
				base.collision(element);
			}
		}
	}
}


// JComponentを継承し、画面の部品を作成します
class Screen extends JComponent {

	Player player = new Player(150, 300, 20, 16, Color.red);
	// Baseクラスのインスタンス作成
//	Base base = new Base(150, 100, 20, 16);
	Base base = new Enemy(150, 100);

	// Starクラスの配列を宣言
	Star[] stars;

	// デフォルトコンストラクタの作成
	Screen() {
		// Starクラスの配列を作成
		stars = new Star[100];
		// 配列の要素分、インスタンスを作成
		for (int i = 0; i < stars.length; i++) {
			// 配列にインスタンスを代入
			stars[i] = new Star(
					(int) (Math.random() * 300),
					(int) (Math.random() * 400),
					(int) (Math.random() * 5) + 1,
					new Color(
							(int) (Math.random() * 128) + 128,
							(int) (Math.random() * 128) + 128,
							(int) (Math.random() * 128) + 128));
		}
		// base = new Base(150, 100, 20, 16);
		// player = new Player(150, 300, 20, 16, Color.blue);
		// キーリスナーへ登録
		addKeyListener(player);
		// フォーカスを得る
		setFocusable(true);
		// 可変長配列に追加
//		BaseManager.add(base);
//		BaseManager.add(player);
		// 変数なしで配列に追加
//		BaseManager.add(new Base(100, 100, 20, 16));
//		BaseManager.add(new Base(200, 100, 20, 16));

		setBounds(50,100,200,300);
	}

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {

		BaseManager.update();
		BaseManager.collision();
		BaseManager.remove();

		// 更新処理を呼びます
		for (Star star : stars) {
			star.update();
		}

		// 衝突処理
		//player.collision(base);

		// 黒色で四角形を描画
		g.setColor(Color.black);
		g.fillRect(0, 0, 300, 400);

		// Starクラスのdrawメソッドを呼びます
		for (int i = 0; i < stars.length; i++) {
			stars[i].draw(g);
		}

		BaseManager.draw(g);

		// 白色で文字列を描画
		g.setColor(Color.white);
		g.drawString("Score", 10, 20);
		g.drawString("High Score", 100, 20);
	}
}

public class Application {
	public static void main(String[] arg) {// プログラムはmainメソッドから実行開始
		int height;
		height = 400;
		int width = 300;

		// importによりjavax.swingパッケージのクラスは、
		// クラス名だけの記述が可能
		JFrame frame = new JFrame();

		// フレーム内部の大きさを幅width(代入値200)
		// 高さheight(代入値100)に設定
		// java.awt.Dimensionはインポートにより、
		// Dimensionだけでよい
		frame.getContentPane().setPreferredSize(
				new Dimension(width, height));

		// フレームのサイズ調整
		frame.pack();

		// importにより、javax.swing.の記述は不要
		frame.setDefaultCloseOperation(
				JFrame.EXIT_ON_CLOSE);

		// 新しく作成したScreenクラスのインスタンスを作成
		Screen screen = new Screen();
		// フレームにscreenを追加します
		frame.add(screen);

		frame.setLayout(null);

		frame.setVisible(true);

		// 更新ループ処理
		while (true) { // 条件が常にtrue（真）のため永久ループします

			// 再描画します（paintComponentメソッドが呼び出されます）
			frame.repaint();
			// 画面の移動を可能とする
			screen.setBounds(0,0,300,400);
			// 停止します
			try {
				Thread.sleep(33); // 33ミリ秒停止します
			} catch (InterruptedException e) {
			}
		}
	}
}
