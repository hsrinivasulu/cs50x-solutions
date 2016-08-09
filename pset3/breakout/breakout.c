//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 7

// lives
#define LIVES 3

// paddle properties
#define PADH 5
#define PADL 50

// brick properties & spacing
#define BRICKH 7
#define BRICKL 35
#define GAPH 5
#define GAPL 5
#define INITH 40
#define INITL 2

// velocity constant
#define VC 4

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // define x and y velocities of balls (bottom-right positive)
    double vx = drand48() * VC, vy = drand48() * VC;
    
    // initialise score and wait for click before starting
    updateScoreboard(window, label, COLS*ROWS - bricks);
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle)/2;
                setLocation(paddle, x, getY(paddle));
            }
        }
        
        if (getX(ball) <= 0 || (getX(ball) + getWidth(ball)) >= getWidth(window))
        {
            vx *= -1;
        }
        
        if (getY(ball) <= 0)
        {
            vy *= -1;
        }
        else if ((getY(ball) + getHeight(ball)) >= getHeight(window))
        {
            while(true)
            {
                GEvent event = getNextEvent(MOUSE_EVENT);
                if (event != NULL)
                {
                    if (getEventType(event) == MOUSE_CLICKED)
                    {
                        lives--;
                        setLocation(ball, getWidth(window)/2 - RADIUS, getHeight(window)/2 - RADIUS);
                        break;
                    }
                }
            } 
        }
        
        move(ball, vx, vy);
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle && vy > 0)
            {
                vy *= -1;
                vx = drand48() * VC;
                
            }
            else if (strcmp(getType(object), "GRect") == 0 && object != paddle)
            {
                vy *= -1;
                bricks--;
                removeGWindow(window, object);
            }
        }
        
        updateScoreboard(window, label, COLS*ROWS - bricks);
        
        pause(10);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    GRect bricks[ROWS][COLS];
    
    for (int i = 0, y = INITH; i < ROWS; i++, y += GAPH + BRICKH)
    {
        int x = INITL;
        for (int j = 0; j < COLS; j++, x += GAPL + BRICKL)
        {
            bricks[i][j] = newGRect(x,y, BRICKL, BRICKH);
            
            switch (i%5)
            {
                case 0:
                    setColor(bricks[i][j], "RED");
                    break;
                case 1:
                    setColor(bricks[i][j], "BLUE");
                    break;
                case 2:
                    setColor(bricks[i][j], "YELLOW");
                    break;
                case 3:
                    setColor(bricks[i][j], "GREEN");
                    break;
                case 4:
                    setColor(bricks[i][j], "ORANGE");
                    break;
            
            }
            
            setFilled(bricks[i][j], true);
            add(window, bricks[i][j]);
        }
    }
   
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // lets initialise the ball
    GOval ball = newGOval(getWidth(window)/2 - RADIUS, getHeight(window)/2 - RADIUS, RADIUS*2, RADIUS*2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // let's get this party started
    GRect paddle = newGRect((getWidth(window)-PADL)/2, getHeight(window)-100, PADL, PADH);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
