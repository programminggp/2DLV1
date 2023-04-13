public class Application {
    public static void main(String[] arg) {//プログラムはmainメソッドから実行開始
        //int型の変数hを作成します
        int h;
        //変数hに100を代入します
        h = 100;
        // int型の変数wを作成し、200を代入します
        int w = 200;
        //frmもJFrameの変数です。
        javax.swing.JFrame f = new javax.swing.JFrame();
        /*wに200が、hに100が代入されているので、
        frm.setSize(200,100)となります。	*/
        f.setSize(w,h);
        f.setDefaultCloseOperation(javax.swing.JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);
    }
}
