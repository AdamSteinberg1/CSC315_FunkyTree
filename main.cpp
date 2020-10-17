#include <GL/glut.h>
#include <math.h>
#include "Circle.h"
//global variables
enum Mode {OUTLINE, TESSELATION, FILL};
Mode currMode = OUTLINE;
Polygon baseTree;
Mat3 trans;
double angle = 0.0;
double angularVelocity = 0.0;
double scale = 1.0;
bool isReflected  = false;

// Specify how large the window is
const int WINDOW_SIDE_LENGTH = 1000;

//Specify values for viewport
const int VIEWPORT_MIN_X = 100;
const int VIEWPORT_MIN_Y = 100;
const int VIEWPORT_MAX_X = 900;
const int VIEWPORT_MAX_Y = 900;

void myglutInit( int argc, char** argv )
{
  const int WINDOW_POSITION_X = 100;
  const int WINDOW_POSITION_Y = 100;
  const int WINDOW_MAX_X = WINDOW_SIDE_LENGTH;
  const int WINDOW_MAX_Y = WINDOW_SIDE_LENGTH;

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y); // set pixel window
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y); // place window top left on display
  glutCreateWindow("Tree"); // window title
}


void myInit(void)
{
  // standard OpenGL attributes
  glClearColor(0.0, 0.0, 0.0, 0.0); // black background

  // set up viewing window with origin lower left
  // Specify the coordinate ranges for the world coordinates in the 2D Frame
  const float WORLD_COORDINATE_MIN_X = 0.0;
  const float WORLD_COORDINATE_MAX_X = WINDOW_SIDE_LENGTH;
  const float WORLD_COORDINATE_MIN_Y = 0.0;
  const float WORLD_COORDINATE_MAX_Y = WINDOW_SIDE_LENGTH;


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,
             WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);
  glMatrixMode(GL_MODELVIEW);
}

void buildTree()
{
  //first build a section of a circle for the canopy
  Vec2 center(690,500);
  double threshold = 2 * M_PI / 3; //120 degrees
  Circle canopy(200, center, threshold); //excludes any points that have an angle larger than threshold

  //make the canopy
  baseTree = Polygon(canopy.getPoints());

  //make the trunk
  baseTree.addPoint(800, 525);
  baseTree.addPoint(110, 600);
  baseTree.addPoint(110, 400);
  baseTree.addPoint(800, 475);
}

void updateTransformation()
{
    Vec2 center(WINDOW_SIDE_LENGTH/2, WINDOW_SIDE_LENGTH/2);
    if(!isReflected)
      angle += angularVelocity;
    else
      angle -= angularVelocity;

    trans = Mat3::createScale(scale, center);
    trans = Mat3::createRotation(angle, center) * trans;
    if(isReflected)
    {
      trans = Mat3::createReflectionY(center) * trans;
    }

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
    glVertex2f(points[i].X, points[i].Y);
    glVertex2f(points[(i+1)%n].X, points[(i+1)%n].Y);
  }
  glEnd();
}

//draws polygon p filled in
void drawFill(Polygon p)
{
  for(Triangle t : p.tessellate())
  {
    glBegin(GL_POLYGON);
      glVertex2f(t[0].X, t[0].Y);
      glVertex2f(t[1].X, t[1].Y);
      glVertex2f(t[2].X, t[2].Y);
    glEnd();
  }
}

//draws a tesselation of polygon p
void drawTesselation(Polygon p)
{
  for(Triangle t : p.tessellate())
  {
    glBegin(GL_LINES);
      glVertex2f(t[0].X, t[0].Y);
      glVertex2f(t[1].X, t[1].Y);

      glVertex2f(t[1].X, t[1].Y);
      glVertex2f(t[2].X, t[2].Y);

      glVertex2f(t[2].X, t[2].Y);
      glVertex2f(t[0].X, t[0].Y);
    glEnd();
  }
}

void display( void )
{
    //clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    //draw viewport
    glColor3f(1.0f, 1.0f, 1.0f);
    glRecti(VIEWPORT_MIN_X,VIEWPORT_MIN_Y,VIEWPORT_MAX_X,VIEWPORT_MAX_Y);

    //make the tree green
    glColor3f(0.0f, 1.0f, 0.0f);

    //transform the base tree for the current frame
    Polygon tree = baseTree.transform(trans);

    //clip the tree against the viewport
    tree = tree.clip(VIEWPORT_MIN_X,VIEWPORT_MAX_X,VIEWPORT_MIN_Y,VIEWPORT_MAX_Y);

    switch (currMode)
    {
      case OUTLINE:
        drawOutline(tree);
        break;
      case FILL:
        drawFill(tree);
        break;
      case TESSELATION:
        drawTesselation(tree);
        break;
    }
    glutSwapBuffers();
}

bool withinViewport(int x, int y)
{
  return x < 900 && x > 100 && y < 900 && y > 100;
}

void mouse( int button, int state, int x, int y )
{
  const double delta = M_PI/180; //how much a click changes the angular velocity
  const double limit = 10 * M_PI/180; //the maximum angular speed
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
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

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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
  else if(key == 'r' || key == 'R')
  {
    isReflected = !isReflected;
  }
  else if(key == 's' || key == 'S')
  {
    angularVelocity = 0.0;
  }
  else if (key == 'i' || key == 'I')
  {
    currMode = OUTLINE;
    isReflected = false;
    angle = 0.0;
    angularVelocity = 0.0;
    scale = 1.0;
  }
}


int main(int argc, char** argv)
{
    myglutInit(argc,argv); //Set up Window
    myInit(); //set attributes
    buildTree();

    glutMouseFunc(mouse);  // Define Mouse Handler
    glutKeyboardFunc(keyboard); // Define Keyboard Handler
    glutDisplayFunc(display); // Display callback invoked when window opened
    glutIdleFunc(updateTransformation); //Idle callback that will adjust the tree for the next frame
    glutMainLoop(); // enter event loop
}
