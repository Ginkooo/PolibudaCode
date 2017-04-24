import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Random;

/**
 * Created by ginko on 14.04.17.
 */
    public class GameWindow extends JPanel implements Runnable {

        private Dimension d;
        private ArrayList<Asteroid> asteroids;
        private ArrayList<Bullet> bullets;
        private Planet planet;
        private Tank tank;
        private String message;
        private boolean ingame = true;
        private int score = 0;
        private int step = 0;

        private Thread animator;
        public GameWindow() {
            setFocusable(true);
            d = new Dimension(Commons.WIDTH, Commons.HEIGHT);
            gameInit();
            setDoubleBuffered(true);
        }

        @Override
        public void addNotify() {
            super.addNotify();
            gameInit();
        }

        public void gameInit() {
            addKeyListener(new TAdapter());
            asteroids = new ArrayList<Asteroid>();
            bullets = new ArrayList<Bullet>();

            planet = new Planet(Commons.WIDTH / 2 - Commons.PLANET_RADIUS, Commons.HEIGHT / 2 - Commons.PLANET_RADIUS);
            tank = new Tank(planet.getX() + Commons.PLANET_RADIUS, planet.getY() + Commons.PLANET_RADIUS);

            if (animator == null || !ingame) {
                animator = new Thread(this);
                animator.start();
            }
        }

        public void drawPlanetHp(Graphics g) {
            g.drawString("Left planet hp: " + planet.hp, 20, 20);
        }

        public void drawScore(Graphics g) {
            g.drawString("Score: " + score + "/" + Commons.SCORE_TO_WIN, Commons.WIDTH - 80, 20);
        }

        public void drawTank(Graphics g) {
            if(tank.isVisible()) {
               g.drawImage(tank.getImage(), tank.getX(), tank.getY(), this);
            }
        }

        public void drawPlanet(Graphics g) {
            if (planet.isVisible()) {
                g.drawImage(planet.getImage(), planet.getX(), planet.getY(), this);
            }

            if (planet.dieIfNoHp()) {
                message = "You loose, you get nothing";
                ingame = false;
            }
        }

        public void drawBullets (Graphics g) {
            for(Bullet bullet : bullets) {
                if(bullet.isVisible()) {
                    g.drawImage(bullet.getImage(), bullet.getX(), bullet.getY(), this);
                }
            }
        }

        public void drawAsteroids (Graphics g) {
            for(Asteroid asteroid : asteroids) {
                if (asteroid.isVisible()) {
                    g.drawImage(asteroid.getImage(), asteroid.getX(), asteroid.getY(), this);
                }
            }
        }

        @Override
        public void paintComponent(Graphics g) {
            super.paintComponent(g);

            g.setColor(Color.WHITE);
            g.fillRect(0, 0, d.width, d.height);
            g.setColor(Color.BLACK);

            if (ingame) {
                drawPlanet(g);
                drawTank(g);
                drawAsteroids(g);
                drawBullets(g);
                drawPlanetHp(g);
                drawScore(g);
            }

            Toolkit.getDefaultToolkit().sync();
            g.dispose();
        }


    public void gameOver() {
        Main.main.setVisible(false);
        Menu.menu.setText(message);
        Menu.menu.setVisible(true);
    }

    public void animationCycle() {
            if(step >= Commons.STEP_NEW_ASTEROID) {
                step = 0;
                Random randside = new Random();
                Random randx = new Random();
                Random randy = new Random();
                int temp_x, temp_y;
                int side = randside.nextInt(4);
                if (side == 0) {
                    temp_x = Commons.WIDTH + 20;
                    temp_y = randy.nextInt(Commons.HEIGHT);
                }
                else if (side == 1) {
                    temp_y = Commons.HEIGHT + 20;
                    temp_x = randx.nextInt(Commons.WIDTH);
                }
                else if (side == 2) {
                    temp_y = randy.nextInt(Commons.HEIGHT);
                    temp_x = -20;
                }
                else {
                    temp_y = -20;
                    temp_x = randx.nextInt(Commons.WIDTH);
                }
                Asteroid asteroid = new Asteroid(temp_x, temp_y);
                asteroids.add(asteroid);
            }
        ArrayList<Asteroid> toRemove = new ArrayList<Asteroid>();
        ArrayList<Bullet> bulletsToRemove = new ArrayList<Bullet>();

            for(Asteroid asteroid : asteroids) {
                asteroid.fall(planet.getX() + Commons.PLANET_RADIUS, planet.getY() + Commons.PLANET_RADIUS);
                if((asteroid.getX() > planet.getX() && asteroid.getX() < planet.getX() + 2 * Commons.PLANET_RADIUS)
                    && (asteroid.getY() > planet.getY() && asteroid.getY() < planet.getY() + 2 * Commons.PLANET_RADIUS)) {
                    planet.hit(10);
                    toRemove.add(asteroid);
                }

                    for(Bullet bullet : bullets) {
                        bullet.move();
                        if((bullet.getX() > asteroid.getX() && bullet.getX() < asteroid.getX() + 2 * Commons.ASTEROID_RADIUS)
                                && (bullet.getY() > asteroid.getY() && bullet.getY() < asteroid.getY() + 2 * Commons.ASTEROID_RADIUS)
                                ) {
                            score++;
                            System.out.println("Score " + score + "from thread " + Thread.currentThread());
                            toRemove.add(asteroid);
                            bulletsToRemove.add(bullet);
                            break;
                        }
                        }
                }

            asteroids.removeAll(toRemove);
            bullets.removeAll(bulletsToRemove);

            if(planet.dieIfNoHp()) {
                message = "You loose, you get nothing";
                ingame = false;
            }

            if (score >= Commons.SCORE_TO_WIN) {
                ingame = false;
                message = "You won!";
            }
    }

    @Override
    public void run() {
            long beforeTime, timeDiff, sleep;

            beforeTime = System.currentTimeMillis();

            while(ingame) {
                step++;
                repaint();
                animationCycle();

                timeDiff = System.currentTimeMillis() - beforeTime;
                sleep = Commons.DELAY - timeDiff;

                if (sleep < 0) {
                    sleep = 2;
                }

                try {
                    Thread.sleep(sleep);
                } catch (InterruptedException e) {
                    System.out.println("interrupted");
                }

                beforeTime = System.currentTimeMillis();
            }

            gameOver();
    }

    private class TAdapter extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            tank.keyPressed(e);
            if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                Bullet bullet = new Bullet(tank.getX(), tank.getY());
                bullets.add(bullet);
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            tank.keyReleased();
        }
    }
}
