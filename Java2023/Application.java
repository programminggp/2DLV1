
//インポートしたパッケージのクラスは、
//クラス名だけで使用できます。
import javax.swing.*;
//インポートにクラスを指定することもできます。
//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;
//awtパッケージをインポート
import java.awt.*;

//星クラスの定義
class Star {
	int x;// 星のx座標(x)
	int y;// 星のy座標(y)
	int w, h;// 幅(w), 高さ(h)
	Color c;// 色(c)

	// コンストラクタ
	Star(int x, int y, int width, int height, Color color) {
		// メンバ変数の設定
		this.x = x; // this.xはクラスのメンバ変数、xは引数
		this.y = y;
		w = width;
		h = height;
		c = color;
	}

	// 描画する
	void draw(Graphics g) {
		// 円の描画
		g.setColor(c);
		g.fillOval(x, y, w, h);
	}
}

// JComponentを継承し、画面の部品を作成します
class Screen extends JComponent {
	//星クラスの作成
	Star star;
	Star star2;
	Star star3;

	//デフォルトコンストラクタの作成
	Screen() {
		// 星クラスのインスタンスを
		// X座標0、Y座標30、幅64、高さ64、緑色で作成します。
		star = new Star(0, 30, 64, 64, new Color(0, 255, 0));
		star2 = new Star(64, 30, 64, 64, new Color(255, 255, 0));
		star3 = new Star(128, 30, 64, 64, new Color(255, 0, 0));
	}

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		// 黒色で四角形を描画
		g.setColor(Color.black);
		g.fillRect(0, 0, 300, 400);
		
		// Starクラスのdrawメソッドを呼びます
		star.draw(g);
		star2.draw(g);
		star3.draw(g);

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

		frame.setVisible(true);
	}
}
