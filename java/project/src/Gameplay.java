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

    private boolean inGame = true;

    private Timer timer;
    private int delay = 20;

    private int counter = 0;

    private int score = 0;

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

        for(Asteroid asteroid: asteroids) {
            g.drawImage(asteroid.getImage(), asteroid.getX(), asteroid.getY(), this);
        }

        g.setColor(Color.green);
        g.drawString("Score: " + score, 0, 20);

        g.dispose();
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        bulletActions();
        asteriodActions();
        timer.start();
        addAsteroidIfReady();
        repaint();
        if(!inGame){
            gameOver();
        }
    }

    private void gameOver() {
        System.exit(0);
    }

    private void addAsteroidIfReady() {
        if(counter > Commons.ASTEROID_DELAY) {
            int[] point = randPoint();
            int x = point[0];
            int y = point[1];
            double angle = randAngle(x, y);
            asteroids.add(new Asteroid(x, y, angle, "big"));
            counter = 0;
        }
        else
            counter++;
    }

    private void asteriodActions() {
        ArrayList<Asteroid> asteroidsToRemove = new ArrayList<>();
        for(Asteroid asteroid : asteroids) {
            asteroid.move();
            if (asteroid.getX() > Commons.WIDTH + 40 || asteroid.getX() < 0 - 40)
                asteroidsToRemove.add(asteroid);
            if (asteroid.getY() > Commons.HEIGHT + 40|| asteroid.getY() < 0 - 40)
                asteroidsToRemove.add(asteroid);
            if(!asteroid.isAlive()) {
                asteroidsToRemove.add(asteroid);
            }
            if(detectHit(ship, asteroid)) {
                inGame = false;
            }
        }
        asteroids.removeAll(asteroidsToRemove);
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
        ArrayList<Asteroid> asteroidsToRemove = new ArrayList<>();
        ArrayList<Asteroid> asteroidsToAdd = new ArrayList<>();
        for(Bullet bullet: bullets) {
            bullet.move();
            if (bullet.getX() > Commons.WIDTH || bullet.getX() < 0)
                bulletsToRemove.add(bullet);
            if (bullet.getY() > Commons.HEIGHT|| bullet.getY() < 0)
                bulletsToRemove.add(bullet);
            for(Asteroid asteroid: asteroids) {
                if(detectHit(bullet, asteroid)) {
                    score++;
                    bulletsToRemove.add(bullet);
                    asteroidsToRemove.add(asteroid);
                    asteroidsToAdd.addAll(asteroid.hit());
                }
            }
        }
        asteroids.removeAll(asteroidsToRemove);
        asteroids.addAll(asteroidsToAdd);
        bullets.removeAll(bulletsToRemove);
    }

    private int[] randPoint() {
        int[] ret = new int[2];
        Random random = new Random();
        int a = random.nextInt(2);
        if(a == 0) {
            ret[0] = random.nextInt(Commons.WIDTH) + 1;
            ret[1] = random.nextInt(2) == 0 ? -20 : Commons.HEIGHT + 20;
        }
        else {
            ret[1] = random.nextInt(Commons.HEIGHT) + 1;
            ret[0] = random.nextInt(2) == 0 ? -20 : Commons.WIDTH + 20;
        }
        return ret;
    }

    private double randAngle(int x, int y) {
        double angle = Math.atan2(ship.getY() - (double)y , ship.getX() - (double)x) - Math.toRadians(90);
        return angle;
    }

    private boolean detectHit(Bullet bullet, Asteroid asteroid) {
        int a = asteroid.getSize() / 2;
        ArrayList<Integer> middle = asteroid.getMiddle();
        if(isNear(bullet.getX(), middle.get(0), a) &&
                isNear(bullet.getY(), middle.get(1), a)) {
            return true;
        }
        else
            return false;
    }

    private boolean detectHit(Ship ship, Asteroid asteroid) {
        int a = asteroid.getSize() / 2;
        ArrayList<Integer> middle = asteroid.getMiddle();
        if(isNear(ship.getMiddle().get(0), middle.get(0), a) &&
                isNear(ship.getMiddle().get(1), middle.get(1), a)) {
            return true;
        }
        else
            return false;
    }

    private boolean isNear(int a, int b, int tolerance) {
        if(Math.abs(a - b) < tolerance) {
            return true;
        }
        else
            return false;
    }
}
