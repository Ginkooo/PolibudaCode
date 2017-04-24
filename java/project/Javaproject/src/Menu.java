import javax.swing.*;
import java.awt.*;
public class Menu extends JFrame {
    public static Menu menu;
    private JButton playButton;
    private JLabel label;

    public void setText(String message) {
        label.setText(message);
    }

    public Menu() {

        setSize(new Dimension(Commons.WIDTH, Commons.HEIGHT));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        add(label);
        add(playButton);
            playButton.addActionListener(e -> {
                setVisible(false);
                EventQueue.invokeLater(() -> {
                    Main.main = new Main();
                    Main.main.setVisible(true);
                });
            });
        }
}
