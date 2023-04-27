
//インポートしたパッケージのクラスは、
//クラス名だけで使用できます。
import javax.swing.*;
//インポートにクラスを指定することもできます。
//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;
//awtパッケージをインポート
import java.awt.*;

//JComponentを継承し、画面の部品を作成します
class Screen extends JComponent {
	int[] ox = {100,220,252};// 円のX座標を配列で２つ作成
	int[] oy = {32,320,0};// 円のY座標を配列で２つ作成
	int[] ow = {64,80,48};// 円の幅を配列で２つ作成
	int[] oh = {64,80,48};// 円の高さを配列で２つ作成
	// Colorクラスのインスタンスを配列で２つ作成
	Color[] oc = {new Color(255,0,0),new Color(0,255,0)
		,new Color(255,255,0)};

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		// 描画色を青にする
		g.setColor(Color.black);
		// X座標0、Y座標0から、幅150、高さ200の四角形を塗りつぶす
		g.fillRect(0, 0, 300, 400);

		g.setColor(oc[0]);// 描画色の設定
		g.fillOval(ox[0], oy[0], ow[0], oh[0]);// 円の描画

		// ２つ目の円の追加
		g.setColor(oc[1]);// 描画色の設定
		g.fillOval(ox[1], oy[1], ow[1], oh[1]);// 円の描画

		// ３つ目の円の追加
		g.setColor(oc[2]);// 描画色の設定
		g.fillOval(ox[2], oy[2], ow[2], oh[2]);// 円の描画

		// 描画色を白色にします
		g.setColor(Color.white);
		// X座標20、Y座標10にHello world!と文字列を描画します
		g.drawString("Score", 10, 20);// "で囲むと文字列データになります
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
