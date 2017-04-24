import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;

/**
 * Created by ginko on 14.04.17.
 */

public class Tank extends Sprite {

    public static double angle = 0.0;
    private int planetCenter_y;
    private int planetCenter_x;
    private String movingDirection = "none";

    private void incAngle(double amount) {
        angle += amount;
    }

    @Override
    public int getX() {
        move();
        return (int) (planetCenter_x + (Commons.PLANET_RADIUS + Commons.TANK_OFFSET) * Math.cos(angle));
    }

    @Override
    public int getY() {
        move();
        return (int) (planetCenter_y + (Commons.PLANET_RADIUS + Commons.TANK_OFFSET) * Math.sin(angle));
    }

    public Tank (int planetCenter_x, int planetCenter_y) {
        this.planetCenter_x = planetCenter_x;
        this.planetCenter_y = planetCenter_y;
        this.x = Commons.WIDTH / 2;
        this.y = Commons.HEIGHT / 2 - Commons.PLANET_RADIUS;

        hp = Commons.ASTEROID_HEALTH;

        ImageIcon ii = new ImageIcon(Commons.TANK_IMG);

        setImage(ii.getImage());
    }

    private void move() {
        if ("left".equals(movingDirection)) {
            incAngle(-Commons.TANK_ANGLE_SPEED);
        }
        if ("right".equals(movingDirection)){
            incAngle(Commons.TANK_ANGLE_SPEED);
        }
    }

    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if(key == KeyEvent.VK_LEFT) {
            movingDirection= "left";
        }
        if(key == KeyEvent.VK_RIGHT) {
            movingDirection = "right";
        }
    }

    public void keyReleased() {
        movingDirection = "none";
    }

}
