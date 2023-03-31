	//インポートしたパッケージのクラスは、クラス名だけで使用できます。
import javax.swing.*;
	//インポートにクラスを指定することもできます。
	//.で区切られた最後がクラス名、それ以外はパッケージ名です。
//import java.awt.Dimension;


//import javax.swing.*;
import java.awt.*;

	//JComponentを継承し、画面の部品を作成します
class Gamen extends JComponent {
	int hsx;//星のX座標の変数を作成
	int hsy;//星のY座標の変数を作成
	int hsw;//星の幅の変数を作成
	int hsh;//星の高さの変数を作成

	//Colorクラスのインスタンスを代入する変数を作成します
	Color hsc;//星の色の変数を作成

	//描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
			//描画色を青にする
		g.setColor(Color.black);
			//X座標0、Y座標0から、幅150、高さ200の四角形を塗りつぶす
		g.fillRect(0, 0, 300, 400);

		//X座標、Y座標、幅、高さを設定します
		hsx = 20;//星のX座標
		hsy = 30;//星のY座標
		hsw = 8;//星の幅
		hsh = 8;//星の高さ
		/*	Color(r, b, g)で色を作成することができます。
			rは赤、bは青、gは緑として、0から255の値の範囲を指定します。
			それぞれの値を光の三原色の値として、色を作成します。
			Color(255,0,0)では、赤が最大、青と緑は0なので、赤色が作成されます。*/
		hsc = new Color(255, 0,0);//星の色
		g.setColor(hsc);//描画色の設定	
		//X座標hsx(20)、Y座標hsy(30)を左上座標として、
		//幅hsw(8)、高さhsh(8)の四角形に内接する円を描きます。
		g.fillOval(hsx, hsy, hsw, hsh);//円の描画

		//変数に値を代入します
		hsx = 200;
		hsy = 300;
		hsw = 16;
		hsh = 16;
		hsc = new Color(0,255,0);//緑色を作成
		g.setColor(hsc);
		g.fillOval(hsx, hsy, hsw, hsh);//2番目の円を描画

		//変数に値を代入します
		hsx = 100;
		hsy = 200;
		hsw = 24;
		hsh = 24;
		hsc = new Color(0,0,255);//緑色を作成
		g.setColor(hsc);
		g.fillOval(hsx, hsy, hsw, hsh);//2番目の円を描画

		g.setColor(Color.white);//描画色を白色にします
		//X座標20、Y座標10にHello world!と文字列を描画します
		g.drawString("Score",10,20);
		g.drawString("High Score",100,20);
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
