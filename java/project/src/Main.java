
import javax.swing.*;
public class Main {
    public static void main(String[] args) {
        JFrame jFrame = new JFrame();
        Gameplay gameplay = new Gameplay();
        jFrame.add(gameplay);
        jFrame.setResizable(false);
        jFrame.setTitle("Asteriods!");
        jFrame.setBounds(Commons.window_x, Commons.window_y, Commons.WIDTH, Commons.HEIGHT);
        jFrame.setVisible(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
