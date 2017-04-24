import javax.swing.*;
import java.io.File;

/**
 * Created by ginko on 14.04.17.
 */
public class Planet extends Sprite {

    public Planet(int x, int y) {
        this.x = x;
        this.y = y;

        hp = Commons.PLANET_INITIAL_HEALTH;
        File f = new File(Commons.PLANET_IMG);
        if(f.exists()) {
            System.out.println("File exists!");
        }
        else {
            System.out.println("File doent exist. working dir is: " + System.getProperty("user.dir"));
        }
        ImageIcon ii = new ImageIcon(Commons.PLANET_IMG);
        setImage(ii.getImage());
    }
}
