import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class Asteroid {
    private int x, y;
    private double angle;

    private int speed;

    private String size;

    private boolean isAlive = true;

    private Image image;

    public Asteroid(int x, int y, double angle, String size) {
        this.x = x;
        this.y = y;
        this.angle = angle;
        Random random = new Random();
        this.speed = random.nextInt(Commons.MAX_ASTEROID_SPEED) + 2;
        image = resolveImage(size);
        if(image == null) {
            System.out.println("Could not load asteroid image");
        }
    }

    public boolean isAlive() {
        return isAlive;
    }


    public void destroy() {
        isAlive = false;
    }

    private Image resolveImage(String size) {
        this.size = size;
        if("small".equals(size))
            return new ImageIcon("small.png").getImage();
        if("medium".equals(size))
            return new ImageIcon("medium.png").getImage();
        return new ImageIcon("big.png").getImage();
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public ArrayList<Integer> getMiddle() {
        ArrayList<Integer> ret = new ArrayList<>();
        ret.add(x + image.getWidth(null) / 2);
        ret.add(y + image.getHeight(null) / 2);
        return ret;
    }

    public Image getImage() {
        return image;
    }

    public int getSize() {
        return image.getHeight(null);
    }

    public void move() {
        x += speed * Math.cos(angle + Math.toRadians(90));
        y += speed * Math.sin(angle + Math.toRadians(90));
    }

    public ArrayList<Asteroid> hit() {
        ArrayList<Asteroid> ret = new ArrayList<>();
        switch(size) {
            case "big":
                ret.add(new Asteroid(x, y, angle + Math.toRadians(45), "medium"));
                ret.add(new Asteroid(x, y, angle + Math.toRadians(-45), "medium"));
                this.isAlive = false;
                break;
            case "medium":
                ret.add(new Asteroid(x, y, angle + Math.toRadians(45), "small"));
                ret.add(new Asteroid(x, y, angle + Math.toRadians(-45), "small"));
                this.isAlive = false;
        }
        return ret;
    }
}
