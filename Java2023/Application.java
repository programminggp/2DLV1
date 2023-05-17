
//インポートしたパッケージのクラスは、
//クラス名だけで使用できます。
import javax.swing.*;
//インポートにクラスを指定することもできます。
//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;
//awtパッケージをインポート
import java.awt.*;
import java.awt.event.*;
import java.util.*;

//ベースクラス
class Base {
	int x; // 中心X座標
	int y; // 中心Y座標
	int w; // 中心からの幅
	int h; // 中心からの高さ

	// Base() {
	// }

	// X座標、Y座標、幅、高さの設定
	Base(int x, int y, int width, int height) {
		this.x = x;
		this.y = y;
		w = width;
		h = height;
	}

	void update() {
	}

	// 描画
	void draw(Graphics g) {
		// 四角形の描画
		g.setColor(Color.cyan);
		g.fillRect(x - w, y - h, w * 2, h * 2);
	}
}

// プレイヤークラス
class Player extends Base implements KeyListener {
	Color color;
	int movex;

	Player(int x, int y, int w, int h, Color c) {
		super(x, y, w, h);
		color = c;
		movex = 0;
	}

	void update() {
		x = x + movex;
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
				movex = -4;
				break;
			case KeyEvent.VK_D:
				movex = 4;
				break;
		}
	}

	public void keyReleased(KeyEvent e) {
		switch (e.getKeyCode()) {
			case KeyEvent.VK_A:
			case KeyEvent.VK_D:
				movex = 0;
				break;
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

// JComponentを継承し、画面の部品を作成します
class Screen extends JComponent {
	ArrayList<Base> arrayList = new ArrayList<>();
	Base player;
	Base base;
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
		base = new Base(150, 100, 20, 16);
		player = new Player(150, 300, 20, 16, Color.blue);
		addKeyListener((Player) player);
		setFocusable(true);
		arrayList.add(base);
		arrayList.add(player);
	}

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		// 黒色で四角形を描画
		g.setColor(Color.black);
		g.fillRect(0, 0, 300, 400);

		// Starクラスのdrawメソッドを呼びます
		for (int i = 0; i < stars.length; i++) {
			stars[i].draw(g);
		}

		// plane.draw(g);
		// player.draw(g);

		for (int i = 0; i < arrayList.size(); i++) {
			arrayList.get(i).draw(g);
		}

		// 白色で文字列を描画
		g.setColor(Color.white);
		g.drawString("Score", 10, 20);
		g.drawString("High Score", 100, 20);
	}

	// loopメソッドを追加します
	void loop() {
		/*
		 * while(条件)
		 * 条件を満たす間、{ から } までの処理を繰り返します。
		 * { } が無い場合、次の１命令だけを繰り返します。
		 */
		while (true) { // 条件が常にtrue（真）のため永久ループします
			// 更新処理を呼びます
			for (Star star : stars) {
				star.update();
			}

			player.update();

			// 再描画します（paintComponentメソッドが呼び出されます）
			repaint();

			// 停止します
			try {
				Thread.sleep(33); // 33ミリ秒停止します
			} catch (InterruptedException e) {
			}
		}
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

		frame.setVisible(true);

		screen.loop();
	}
}
