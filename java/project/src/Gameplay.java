import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.Random;

/**
 * Created by ginko on 27.04.17.
 */
public class Gameplay extends JPanel implements KeyListener, ActionListener {

    private Ship ship;

    private Timer timer;
    private int delay = 4;

    private int counter = 0;

    private ArrayList<Bullet> bullets = new ArrayList<>();
    private ArrayList<Asteroid> asteroids = new ArrayList<>();

    public Gameplay() {
        addKeyListener(this);
        setFocusable(true);
        setFocusTraversalKeysEnabled(true);
        timer = new Timer(delay, this);
        timer.start();

        this.ship = new Ship(Commons.WIDTH / 2, Commons.HEIGHT / 2);
    }

    @Override
    public void paint(Graphics g) {
        // background
        g.setColor(Color.black);
        g.fillRect(0,0,Commons.WIDTH, Commons.HEIGHT);

        //ship
        g.drawImage(ship.getImage(), ship.getX(), ship.getY(), this);

        //bullets
        for(Bullet bullet: bullets) {
            g.drawImage(bullet.getImage(), bullet.getX(), bullet.getY(), this);
        }

        g.dispose();
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        bulletActions();
        asteriodActions();
        timer.start();
        addAsteroidIfReady();
        repaint();
    }

    private void addAsteroidIfReady() {
        if(counter > Commons.ASTEROID_DELAY) {
            int x = randX();
            int y = randY();
            int angle = randAngle(x, y);
            asteroids.add(new Asteroid(x, y, angle, "big"));
            counter = 0;
        }
        else
            counter++;
    }

    private void asteriodActions() {
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        if(e.getKeyCode() == KeyEvent.VK_RIGHT) {
            ship.rotate("right");
        }

        if(e.getKeyCode() == KeyEvent.VK_LEFT) {
            ship.rotate("left");
        }
        if(e.getKeyCode() == KeyEvent.VK_UP)
            ship.move();
        if(e.getKeyCode() == KeyEvent.VK_SPACE) {

            bullets.add(new Bullet(ship.getX(), ship.getY(), ship.getRotation()));
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        if(e.getKeyCode() == KeyEvent.VK_RIGHT || e.getKeyCode() == KeyEvent.VK_LEFT) {
            ship.stopRotation();
        }
        if(e.getKeyCode() == KeyEvent.VK_UP)
            ship.stop();
    }

    private void bulletActions() {
        ArrayList<Bullet> bulletsToRemove = new ArrayList<>();
        for(Bullet bullet: bullets) {
            bullet.move();
            if (bullet.getX() > Commons.WIDTH || bullet.getX() < 0)
                bulletsToRemove.add(bullet);
            if (bullet.getY() > Commons.HEIGHT|| bullet.getY() < 0)
                bulletsToRemove.add(bullet);
        }
        bullets.removeAll(bulletsToRemove);
    }

    private int randX()
    {
        Random random = new Random();
        int side = random.nextInt(2);
        if(side == 1) {
            random.n
        }
    }
}
