
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

class UI {
	private static int score = 0;
	private static int highScore = 0;

	public static int Score() {
		return score;
	}

	public static void Score(int score) {
		UI.score = score;
		if (score > highScore) {
			highScore = score;
		}
	}

	public static void draw(Graphics g) {
		// 白色で文字列を描画
		g.setColor(Color.white);
		g.drawString("Score " + score, 10, 20);
		g.drawString("High Score " + highScore, 100, 20);
	}

	public static int HighScore() {
		return highScore;
	}

	public static void HighScore(int score) {
		highScore = score;
	}

}

// ベースクラス
class Base {
	enum State {
		NORMAL, // 通常
		HIT, // 被弾
	}

	// 状態Stateの変数stateの宣言
	State state;

	enum Tag {
		ZERO,
		ENEMY,
		BULLET,
		PLAYER,
	}

	Tag tag;
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
		state = State.NORMAL;
		tag = Tag.ZERO;
		enabled = true; // 有効とする
		vx = 0;
		this.x = x;
		this.y = y;
		w = width;
		h = height;
		// BaseManagerに追加
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

	// 衝突検出処理
	// a と b が衝突していればtrue
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

	// 衝突処理１
	void collision() {
		BaseManager.collision(this);
	}

	// 衝突処理２
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

	Enemy(int x, int y) {
		super(x, y, WIDTH, HEIGHT);
	}

	void draw(Graphics g) {
		// 翼の描画
		g.setColor(COLOR);
		if (state == State.HIT) {
			g.setColor(Color.yellow);
		}
		g.fillOval(x - w, y - h / 2, w * 2, h);
		// 機体の描画
		g.setColor(Color.white);
		g.fillOval(x - w / 4, y - h, w / 2, h * 2);
	}

	// 衝突処理１
	void collision() {
		BaseManager.collision(this);
	}

	// 衝突処理２
	void collision(Base base) {
		if (collision(this, base)) {
			// 状態を被弾にします
			state = State.HIT;
		}
	}

	void update() {
		if (state == State.HIT) {
			w += 2;
			h += 2;
			if (w > 30) {
				enabled = false;
				UI.Score(UI.Score() + 10);
			}
		}

		y += 6;
		if (y > 500) {
			y = 0;
		}
	}
}

class Input implements KeyListener {
	private static boolean key[] = new boolean[256];

	public static boolean key(int keycode) {
		return key[keycode];
	}

	public void keyTyped(KeyEvent e) {
	}

	public void keyPressed(KeyEvent e) {
		key[e.getKeyCode()] = true;
	}

	public void keyReleased(KeyEvent e) {
		key[e.getKeyCode()] = false;
	}
}

class Game extends KeyAdapter {
	// 状態管理
	enum State {
		GAME, // ゲーム中
		GAMEOVER, // ゲームオーバー
	}

	// 状態の変数
	private State state = State.GAME;

	// 状態の取得
	public State state() {
		return state;
	}

	private static int left = 2; // 残数
	// 残機表示用の機体
	private Player playerLeft = new Player(10, 390, 8, 6);

	// 残数処理
	public static int left() {
		return left;
	}

	public static void left(int i) {
		left = i;
	}

	public void draw(Graphics g) {
		if (left < 0) {
			state = State.GAMEOVER;
		}
			g.drawString("Game Over !!", 120, 200);
			g.drawString("Push Enter", 120, 220);
		// 残機描画
		for (int i = 0; i < left; i++) {
			playerLeft.draw(g);
			playerLeft.x = 20 * i + 10;
		}
	}

	public void keyTyped(KeyEvent e) {
		// keyTypedではgetKeyChar()を使う
		if (state == State.GAMEOVER
				&& e.getKeyChar() == KeyEvent.VK_ENTER) {
			state = State.GAME;
			left = 2;
		}
	}
}

/*
 * class Game extends KeyAdapter {
 * 
 * private static int left = 2; // 残機
 * 
 * // 状態管理
 * enum State {
 * GAME,
 * GAMEOVER,
 * }
 * private State state = State.GAME;
 * 
 * // 残機用の機体
 * private Player playerLeft = new Player(10, 390, 8, 6);
 * // プレイヤー
 * private Player player;
 * 
 * Game()
 * {
 * start();
 * }
 * 
 * // 残機処理
 * public static int left() {
 * return left;
 * }
 * 
 * public static void left(int i) {
 * left = i;
 * }
 * 
 * public void draw(Graphics g) {
 * switch (state) {
 * case GAME:
 * // 残機描画
 * for (int i = 0; i < left; i++) {
 * playerLeft.draw(g);
 * // player.x += 20;
 * playerLeft.x = 20 * i + 10;
 * }
 * if (left < 0) {
 * state = State.GAMEOVER;
 * }
 * break;
 * case GAMEOVER:
 * g.drawString("Game Over !!", 120, 200);
 * break;
 * }
 * }
 * 
 * public State state() {
 * return state;
 * }
 * 
 * public void start() {
 * left = 2;
 * state = State.GAME;
 * UI.Score((0));
 * BaseManager.clear();
 * player = new Player(150, 300, 20, 16, Color.red);
 * Screen.instance().addKeyListener(player);
 * }
 * 
 * public void keyTyped(KeyEvent e) {
 * // keyTypedではgetKeyChar()を使う
 * if (state == State.GAMEOVER
 * && e.getKeyChar() == KeyEvent.VK_ENTER) {
 * // キーリスナ―から削除
 * Screen.instance().removeKeyListener(player);
 * start();
 * }
 * }
 * }
 */

class Stage1 {
	private static int count = 1;

	public static void update() {
		count %= 40;
		if (count++ == 0) {
			new Enemy(((int) (Math.random() * 5) + 1) * 50, 0);
		}
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

	// 衝突処理１
	void collision() {
		BaseManager.collision(this);
	}

	// 衝突処理２
	// base：相手のインスタンス
	void collision(Base base) {
		// this自分と相手が衝突したら無効にする
		if (collision(this, base)) {
			enabled = false;
		}
	}
}

// プレイヤークラス
class Player extends Base implements KeyListener {
	Color color; // 色
	int invincible = 0; // 無敵カウンタ

	// 残機用のコンストラクタ
	Player(int x, int y, int w, int h) {
		super(x, y, w, h);
		color = Color.red;
		enabled = false;
	}

	Player(int x, int y, int w, int h, Color c) {
		super(x, y, w, h);
		color = c;
	}

	void update() {
		x += vx;
		y += vy;
		if (invincible > 0) {
			invincible--;
			if (invincible == 0)
				color = Color.red;
		}
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
			// 30フレーム無敵
			invincible = 30;
			Game.left(Game.left() - 1);
		}
		// else {
		// color = Color.red;
		// }
	}

	// 衝突処理１
	void collision() {
		// 無敵時は衝突判定なし
		if (invincible > 0) {
			return;
		}
		BaseManager.collision(this);
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

// Baseクラスの管理クラス
class BaseManager {
	// 可変長配列
	static ArrayList<Base> arrayList = new ArrayList<Base>();

	// 追加処理
	static void add(Base base) {
		arrayList.add(base);
	}

	// 更新処理
	static void update() {
		// 拡張for文
		for (Base base : arrayList) {
			base.update();
		}
	}

	// 描画処理
	static void draw(Graphics g) {
		for (int i = 0; i < arrayList.size(); i++) {
			arrayList.get(i).draw(g);
		}
	}

	static void remove() {
		// enabledがfalseの要素を削除するラムダ式
		arrayList.removeIf(base -> base.enabled == false);
	}

	// 衝突処理１
	// 全要素の衝突処理１を呼び出す
	static void collision() {
		// 拡張for文
		for (Base base : arrayList) {
			base.collision();
		}
	}

	// 衝突処理２
	// baseの衝突処理２を、全要素に対して行う
	static void collision(Base base) {
		// イテレータの作成
		Iterator<Base> iterator = arrayList.iterator();
		// 次の要素があるか判定
		while (iterator.hasNext()) {
			// イテレータで次の要素取り出して代入
			Base element = iterator.next();
			if (element != base) {
				base.collision(element);
			}
		}
	}

	static void clear() {
		arrayList.clear();
	}
}

// JComponentを継承し、画面の部品を作成します
class Screen extends JComponent {
	// インスタンスの保存
	private static Screen instance;

	// インスタンスの取得
	public static Screen instance() {
		return instance;
	}

	Game game;

	Player player = new Player(150, 300, 20, 16, Color.red);

	// Starクラスの配列を宣言
	Star[] stars;

	// デフォルトコンストラクタの作成
	Screen() {
		// インスタンスの退避
		instance = this;
		game = new Game();
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
		// キーリスナーへ登録
		addKeyListener(player);
		addKeyListener(game);
		// フォーカスを得る
		setFocusable(true);

		// addKeyListener(new Input());

		// setBounds(50,100,200,300);
	}

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		if (game.state() == Game.State.GAME) {
			Stage1.update();
			BaseManager.update();
			BaseManager.collision();
		}
		BaseManager.remove();

		// 更新処理を呼びます
		for (Star star : stars) {
			star.update();
		}

		// 黒色で四角形を描画
		g.setColor(Color.black);
		g.fillRect(0, 0, 300, 400);

		// Starクラスのdrawメソッドを呼びます
		for (int i = 0; i < stars.length; i++) {
			stars[i].draw(g);
		}

		BaseManager.draw(g);

		UI.draw(g);

		game.draw(g);
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
			screen.setBounds(0, 0, 300, 400);
			// 停止します
			try {
				Thread.sleep(33); // 33ミリ秒停止します
			} catch (InterruptedException e) {
			}
		}
	}
}
