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
	int ox;//円のX座標の変数を作成
	int oy;//円のY座標の変数を作成
	int ow;//円の幅の変数を作成
	int oh;//円の高さの変数を作成
	//Colorクラスのインスタンスを代入する変数を作成します
	Color oc;//円の色の変数を作成

	//描画が必要なときに実行されるメソッド
	public void paintComponent(Graphics g) {
		//描画色を青にする
		g.setColor(Color.black);
		//X座標0、Y座標0から、幅150、高さ200の四角形を塗りつぶす
		g.fillRect(0,0,300,400);

		//X座標、Y座標、幅、高さを設定します
        ox = 100;//円のX座標
        oy = 32;//円のY座標
        ow = 64;//円の幅
        oh = 64;//円の高さ
        /*	Color(r, b, g)で色を作成することができます。
            rは赤、bは青、gは緑として、0から255の値の範囲を指定します。
            それぞれの値を光の三原色の値として、色を作成します。
            Color(255,0,0)では、赤が最大、青と緑は0なので、赤色が作成されます。*/
        oc = new Color(255,0,0);//円の色
        g.setColor(oc);//描画色の設定
        //X座標hsx(20)、Y座標hsy(30)を左上座標として、
        //幅hsw(8)、高さhsh(8)の四角形に内接する円を描きます。
        g.fillOval(ox, oy, ow, oh);//円の描画

        //２つ目の円の追加
		ox = 220;
		oy = 320;
		ow = 80;
		oh = 80;
		oc = new Color(0,255,0);//緑色を作成
		g.setColor(oc);
        g.fillOval(ox, oy, ow, oh);//円の描画

        //２つ目の円の追加
		ox = 0;
		oy = 352;
		ow = 48;
		oh = 48;
		oc = new Color(0,0,255);//緑色を作成
		g.setColor(oc);
        g.fillOval(ox, oy, ow, oh);//円の描画

        //描画色を白色にします
        g.setColor(Color.white);
        //X座標20、Y座標10にHello world!と文字列を描画します
        g.drawString("Score",10,20);// "で囲むと文字列データになります
        g.drawString("High Score",100,20);
	}
}

public class Application {
    public static void main(String[] arg) {//プログラムはmainメソッドから実行開始
        int height;
        height = 400;
        int width = 300;
    
        //importによりjavax.swingパッケージのクラスは、
        //クラス名だけの記述が可能
        JFrame frame = new JFrame();
            
        //フレーム内部の大きさを幅width(代入値200)
        //高さheight(代入値100)に設定
        //java.awt.Dimensionはインポートにより、
        //Dimensionだけでよい
        frame.getContentPane().setPreferredSize(
            new Dimension(width, height));
    
        //フレームのサイズ調整
        frame.pack();
    
        //importにより、javax.swing.の記述は不要
        frame.setDefaultCloseOperation(
            JFrame.EXIT_ON_CLOSE);

        //新しく作成したScreenクラスのインスタンスを作成
		Screen screen = new Screen();
        //フレームにscreenを追加します
        frame.add(screen);

        frame.setVisible(true);
    }
}


