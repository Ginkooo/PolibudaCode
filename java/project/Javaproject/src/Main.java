import javax.swing.*;
import java.awt.*;

/**
 * Created by ginko on 14.04.17.
 */
public class Main extends JFrame implements Commons {

    public static Main main;

    public Main() { initUI(); }
    public void initUI() {
        add(new GameWindow());
        setSize(new Dimension(Commons.WIDTH, Commons.HEIGHT));
        setTitle(Commons.TITLE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    public static void main(String[] args) {
        Menu.menu = new Menu();
        Menu.menu.setVisible(true);
    }
}
