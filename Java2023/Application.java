
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
	int[] ox = { 100, 220, 252 };// 円のX座標を配列で２つ作成
	int[] oy = { 32, 320, 0 };// 円のY座標を配列で２つ作成
	int[] ow = { 64, 80, 48 };// 円の幅を配列で２つ作成
	int[] oh = { 64, 80, 48 };// 円の高さを配列で２つ作成
	// Colorクラスのインスタンスを配列で２つ作成
	Color[] oc = { new Color(255, 0, 0), new Color(0, 255, 0), new Color(255, 255, 0) };

	// 描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		// 黒色で四角形を描画
		g.setColor(Color.black);
		g.fillRect(0, 0, 300, 400);

		// 繰り返し処理
		for (int i = 1; i < ox.length; i++) {
			// 配列の添字に変数を使用できます
			// iが0の時はoc[0]、iが1の時はoc[1]と同様
			g.setColor(oc[i]);
			g.fillOval(ox[i], oy[i], ow[i], oh[i]);
		}

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
