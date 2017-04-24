import java.awt.Image;

/**
 * Created by ginko on 14.04.17.
 */
public class Sprite {
    private boolean visible;
    private Image image;
    protected int x;
    protected int y;
    protected int hp;

    public Sprite() {
        visible = true;
    }

    public boolean dieIfNoHp() {
        if(hp <= 0) {
            visible = false;
            return true;
        }
        return false;
    }

    public void hit(int damage) {
        hp -= damage;
    }

    public boolean isVisible() {
        return visible;
    }

    protected void setVisible(boolean visible) {
       this.visible = visible;
    }

    public void setImage(Image image) {
        this.image = image;
    }

    public Image getImage() {
        return image;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getY() {
        return y;
    }

    public int getX() {
        return x;
    }
}
