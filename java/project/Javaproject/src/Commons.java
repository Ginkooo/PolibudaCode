/**
 * Created by ginko on 14.04.17.
 */
public interface Commons {
    public static final String TITLE = "Super Ultimate Planet Defender 2!";
    public static final String PLANET_IMG = "src/resources/planet.png";
    public static final String ASTEROID_IMG = "src/resources/asteroid.png";
    public static final String TANK_IMG = "src/resources/tank.png";
    public static final String BULLET_IMG = "src/resources/bullet.png";
    public static final int DELAY = 30;
    public static final int STEP_NEW_ASTEROID = DELAY * 2;
    public static final double TANK_ANGLE_SPEED = 0.1;
    public static final int SCALE = 2;
    public static final int SCORE_TO_WIN = 20;
    public static final int TANK_OFFSET = 10 * SCALE;
    public static final int WIDTH = 300 * SCALE;
    public static final int HEIGHT = 400 * SCALE;
    public static final int PLANET_RADIUS = 135 / 2;
    public static final int ASTEROID_RADIUS = 10;
    public static final int TANK_WIDTH = 10 * SCALE;
    public static final int TANK_HEIGHT = 10 * SCALE;
    public static final int PLANET_INITIAL_HEALTH = 100;
    public static final int ASTEROID_HEALTH = 1;
    public static final int TANK_SPEED = 1 * SCALE;
    public static final int ASTEROID_SPEED = 1 * SCALE;
    public static final int BULLET_SPEED = 1 * SCALE;
}
