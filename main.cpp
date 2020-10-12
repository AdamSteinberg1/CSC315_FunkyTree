#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "Mat3.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Polygon.h"
#include "Circle.h"
#include "Triangle.h"

//global variables
enum Mode {OUTLINE, TESSELATION, FILL};
Mode currMode = OUTLINE;
Polygon tree;
Mat3 trans;
double angle = 0.0;
double angularVelocity = 0.0;
double scale = 1.0;

// Specity the values to place and size the window on the screen
const int WINDOW_SIDE_LENGTH = 1000;

const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = WINDOW_SIDE_LENGTH;
const int WINDOW_MAX_Y = WINDOW_SIDE_LENGTH;

// Specify the coordinate ranges for the world coordinates in the 2D Frame

const float WORLD_COORDINATE_MIN_X = 0.0;
const float WORLD_COORDINATE_MAX_X = WINDOW_SIDE_LENGTH;
const float WORLD_COORDINATE_MIN_Y = 0.0;
const float WORLD_COORDINATE_MAX_Y = WINDOW_SIDE_LENGTH;

double dummy_angle = 0; //TODO remove

void myglutInit( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); /* set pixel window */
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); /* place window top left on display */
    glutCreateWindow("Polygon Tesselation"); /* window title */
}


void myInit(void)
{

/* standard OpenGL attributes */

      glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */

/* set up viewing window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
                 WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
      glMatrixMode(GL_MODELVIEW);
}

void randomizeColor()
{
  //sin^2 returns a value between 0 and 1
  //we need to offset each color by a third of a revolution around a circle, so it's not just grays
  float r = 2 * M_PI * rand() / RAND_MAX; //random float between 0 and 2 pi
  float offset = 2 * M_PI / 3;
  float red = sin(r) * sin(r);
  float green = sin(r + offset) * sin(r + offset);
  float blue = sin(r + 2 * offset) * sin(r + 2 * offset);
  glColor3f(red, green, blue);
}

void buildTree()
{
  //first build a section of a circle for the canopy
  Vec2 center(690,500);
  double threshold = 2 * M_PI /3;
  Circle canopy(200, center, threshold);

  tree = Polygon(canopy.getPoints());

  tree.addPoint(800, 525);
  tree.addPoint(110, 600);
  tree.addPoint(110, 400);
  tree.addPoint(800, 475);
}

void updateTransformation()
{
    Vec2 center(WINDOW_SIDE_LENGTH/2, WINDOW_SIDE_LENGTH/2);
    angle += angularVelocity;
    trans = Mat3::createRotation(angle, center);
    trans = Mat3::createScale(scale, center) * trans;

    glutPostRedisplay();
}

//draws an outline of polygon p
void drawOutline(Polygon p)
{
  std::vector<Vec2> points = p.getPoints();
  int n = points.size();
  glBegin(GL_LINES);
  for(int i =0; i < n; i++)
  {
    glVertex2i(points[i].X, points[i].Y);
    glVertex2i(points[(i+1)%n].X, points[(i+1)%n].Y);
  }
  glEnd();

}

//draws polygon p filled in
void drawFill(Polygon p)
{
  for(Triangle t : p.tesselate())
  {
    glBegin(GL_POLYGON);
      glVertex2i(t[0].X, t[0].Y);
      glVertex2i(t[1].X, t[1].Y);
      glVertex2i(t[2].X, t[2].Y);
    glEnd();
  }
}

//draws a tesselation of polygon p
void drawTesselation(Polygon p)
{
  for(Triangle t : p.tesselate())
  {
    glBegin(GL_LINES);
      glVertex2i(t[0].X, t[0].Y);
      glVertex2i(t[1].X, t[1].Y);

      glVertex2i(t[1].X, t[1].Y);
      glVertex2i(t[2].X, t[2].Y);

      glVertex2i(t[2].X, t[2].Y);
      glVertex2i(t[0].X, t[0].Y);
    glEnd();
  }
}

void display( void )
{
    //clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    //draw viewport
    glColor3f(1.0f, 1.0f, 1.0f);
    glRecti(100,100,900,900);

    glColor3f(0.0f, 1.0f, 0.0f);

    Polygon transformedTree = tree.transform(trans);

    switch (currMode)
    {
      case OUTLINE:
        drawOutline(transformedTree);
        break;
      case FILL:
        drawFill(transformedTree);
        break;
      case TESSELATION:
        drawTesselation(transformedTree);
        break;
    }

    glFlush();
    glutSwapBuffers();

}

bool withinViewport(int x, int y)
{
  return x < 900 && x > 100 && y < 900 && y > 100;
}

void mouse( int button, int state, int x, int y )
{
  const double delta = M_PI/180; //how much a click changes the angular velocity
  double limit = 10 * M_PI/180; //10 degrees in radians
  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
     {
       if(withinViewport(x, y))
       {
        angularVelocity -= delta;

        //-10 degree limit
        if(angularVelocity < -limit)
          angularVelocity = -limit;
       }
       else
       {
         scale *= .95;
       }
     }

  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
     {
       if(withinViewport(x, y))
       {
        angularVelocity += delta;

        //10 degree limit
        if(angularVelocity > limit)
          angularVelocity = limit;
       }
       else
       {
         scale *= 1.05;
       }
     }

}


void keyboard( unsigned char key, int x, int y )
{
  if ( key == 'q' || key == 'Q')
    exit(0);
  else if ( key == 'f' || key == 'F')
  {
    currMode = FILL;
  }
  else if ( key == 't' || key == 'T')
  {
    currMode = TESSELATION;
  }
  else if ( key == 'l' || key == 'L')
  {
    currMode = OUTLINE;
  }
}


int main(int argc, char** argv)
{
    myglutInit(argc,argv); /* Set up Window */
    myInit(); /* set attributes */
    buildTree();

    // Now start the standard OpenGL glut callbacks //

    glutMouseFunc(mouse);  /* Define Mouse Handler */
    glutKeyboardFunc(keyboard); /* Define Keyboard Handler */
    glutDisplayFunc(display); /* Display callback invoked when window opened */
    glutIdleFunc(updateTransformation);
    glutMainLoop(); /* enter event loop */
}
