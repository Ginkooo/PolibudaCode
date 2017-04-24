import javax.swing.*;
import java.util.Random;

/**
 * Created by ginko on 14.04.17.
 */
public class Asteroid extends Sprite {

    int angle;
    int speed;
    int revert;

    public Asteroid(int x, int y) {
        this.x = x;
        this.y = y;

        int center_x = Commons.WIDTH / 2;
        int center_y = Commons.HEIGHT / 2;

        Random random = new Random();
        speed = random.nextInt(3) + 2 ;

        random = new Random();
        angle = random.nextInt(3);

        hp = Commons.ASTEROID_HEALTH;

        revert = x > Commons.WIDTH || y > Commons.HEIGHT? 1 : -1;

        speed *= revert;

        ImageIcon ii = new ImageIcon(Commons.ASTEROID_IMG);

        setImage(ii.getImage());
    }

    public void fall(int dest_x, int dest_y) {
        if(x < dest_x) {
            x++;
        }
        if(x > dest_x) {
            x--;
        }
        if(y < dest_y) {
            y++;
        }
        if(y > dest_y) {
            y--;
        }
    }
}
