import javax.swing.*;
import java.awt.*;

/**
 * Created by ginko on 27.04.17.
 */
public class Asteroid {
    private int x, y, angle;

    private Image image;

    public Asteroid(int x, int y, int angle, String size) {
        this.x = x;
        this.y = y;
        this.angle = angle;
        image = resolveImage(size);
    }

    private Image resolveImage(String size) {
        if("small".equals(size))
            return new ImageIcon("small.png").getImage();
        if("medium".equals(size))
            return new ImageIcon("medium.png").getImage();
        return new ImageIcon("big.png").getImage();
    }

    public Image getImage() {
        return image;
    }

    public void move() {
        x += (double)Commons.SHIP_SPEED * Math.cos(Math.toRadians(angle - 90));
        y += (double)Commons.SHIP_SPEED * Math.sin(Math.toRadians(angle - 90));
    }
}
