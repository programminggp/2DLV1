	//インポートしたパッケージのクラスは、クラス名だけで使用できます。
import javax.swing.*;
	//インポートにクラスを指定することもできます。
	//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;


//import javax.swing.*;
import java.awt.*;

	//JComponentを継承し、画面の部品を作成します
class Gamen extends JComponent {
		//描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
			//描画色を青にする
		g.setColor(Color.black);
			//X座標0、Y座標0から、幅150、高さ200の四角形を塗りつぶす
		g.fillRect(0, 0, 300, 400);
		g.setColor(Color.white);//描画色を白色にします
			//X座標20、Y座標10にHello world!と文字列を描画します
		g.drawString("Hello world!",20,10);// "で囲むと文字列データになります
	}
}


class Main {
	public static void main(String[] arg) {
		int width = 300;
		int height;
		height = 400;

		JFrame frame = new JFrame();
		frame.getContentPane().setPreferredSize(new Dimension(width, height));
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			//新しく作成したGamenクラスのインスタンスを作成
		Gamen gamen = new Gamen();
			//フレームにgamenを追加します
		frame.add(gamen);
		frame.setVisible(true);
	}

}
