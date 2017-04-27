import javax.swing.*;
import java.awt.*;

/**
 * Created by ginko on 27.04.17.
 */
public class Bullet {
    private int x;
    private int y;

    private int angle;

    private static final Image image = new ImageIcon("bullet.png").getImage();

    public Bullet(int x, int y, int angle) {
        this.angle = angle;
        this.x = x;
        this.y = y;
    }

    public Image getImage() {
        return image;
    }

    public void move() {
        x += (double)Commons.SHIP_SPEED * Math.cos(Math.toRadians(angle - 90));
        y += (double)Commons.SHIP_SPEED * Math.sin(Math.toRadians(angle - 90));
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
