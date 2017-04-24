import javax.swing.*;

/**
 * Created by ginko on 14.04.17.
 */
public class Bullet extends Sprite {
    private double angle;
    private double a;
    private double b;

    public Bullet(int start_x, int start_y) {
        this.x = start_x;
        this.y = start_y;
        this.angle = Tank.angle;
        a = Math.tan(angle);
        b = start_y - (Math.tan(angle) * start_x);

        ImageIcon ii = new ImageIcon(Commons.BULLET_IMG);
        setImage(ii.getImage());
    }

    public void move() {
       y += Math.sin(angle) * Commons.BULLET_SPEED;
       x += Math.cos(angle) * Commons.BULLET_SPEED;
    }
}