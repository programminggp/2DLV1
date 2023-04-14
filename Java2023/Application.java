//インポートしたパッケージのクラスは、
//クラス名だけで使用できます。
import javax.swing.*;
//インポートにクラスを指定することもできます。
//.で区切られた最後がクラス名、それ以外はパッケージ名です。
import java.awt.Dimension;

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
        frame.setVisible(true);
    }
}
