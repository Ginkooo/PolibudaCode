import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by ginko on 27.04.17.
 */
public class Ship {

    private int x, y;
    private boolean right, left, move = false;

    private int rotation = 0;

    private BufferedImage image;
    AffineTransform tx;
    AffineTransformOp op;

    public Ship(int x, int y) {
        this.x = x;
        this.y = y;
        image = loadImage("ship.png");
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void rotate(String direction) {
        if("left".equals(direction)) {
            left = true;
        }
        else {
            right = true;
        }

    }

    public void stopRotation() {
        right = left = false;
    }

    public void move() {
        move = true;
    }

    public void stop() {
        move = false;
    }

    public ArrayList<Integer> getMiddle() {
        ArrayList<Integer> ret = new ArrayList<>();

        ret.add(x + this.image.getHeight() / 2);
        ret.add(y + this.image.getWidth() / 2);

        return ret;
    }

    public Image getImage() {
        if(move)
        {
            go_some();
        }
        if(right)
            rotation += Commons.SHIP_ROT_SPEED;
        if (left)
            rotation -= Commons.SHIP_ROT_SPEED;
        tx = AffineTransform.getRotateInstance(Math.toRadians(rotation), image.getWidth() / 2, image.getHeight() / 2);
        op = new AffineTransformOp(tx, AffineTransformOp.TYPE_BILINEAR);
        return op.filter(image, null);
    }

    private BufferedImage loadImage(String filename) {
        BufferedImage img = null;
        try {
            img = ImageIO.read(new File(filename));
        } catch(IOException e) {
           System.err.println("Couldn't load ship image, current path is: " + System.getProperty("user.dir"));
           System.exit(1);
        }
        return img;
    }

    public int getRotation() {
        return rotation;
    }

    private void go_some() {
        x += (double)Commons.SHIP_SPEED * Math.cos(Math.toRadians(rotation - 90));
        y += (double)Commons.SHIP_SPEED * Math.sin(Math.toRadians(rotation - 90));
    }

}
