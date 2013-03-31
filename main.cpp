///////////////////////////////////////////////////////////////////////////////
// RTPS
// Copyright 1996-2013, Michael T. Mayers
// Provided under the MIT License (see LICENSE.txt)
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void iterate( void );
void windowreshape( GLsizei w, GLsizei h );
void menuhandler( int value );
void mousehandler( int button, int state, int x, int y );
void keyboardhandler( unsigned char key, int x, int y );
void motionhandler(int x, int y);
void drawfunc( void );


GLsizei	gw, gh;

int mainwinid;

///////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{   	
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 640, 480 );	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
    mainwinid = glutCreateWindow("Twilight 2013, courtesy of TweakoZ");
   
    glutDisplayFunc(drawfunc);
    glutReshapeFunc(windowreshape);
    glutIdleFunc( iterate );
   
    glutCreateMenu(menuhandler);
    glutAddMenuEntry("FullScreen", 1);
    glutAddMenuEntry("Windowed", 2);
    glutAddMenuEntry("ResetPosition", 3);
    glutAddMenuEntry("Quit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMouseFunc( mousehandler );
    glutKeyboardFunc( keyboardhandler );
    glutMotionFunc( motionhandler );
   
    glutMainLoop(); //glutMainLoopEvent();

}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void iterate( void )
{	
	drawfunc();
	usleep(500000);
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void windowreshape( GLsizei w,  GLsizei h )

{
	gw = w;
	gh = h;
	
	glViewport( 0, 0, gw, gh );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
//	gluPerspective( 40.0f, ((F32)gw/(F32)gh), 0.1f, 100.0f );
//	gluLookAt( eyex, eyey, eyez, 
//		   cenx, ceny, cenz,
//		   0.0f, 1.0f, 0.0f );
//	
//	glTranslatef( 0.0f, 0.0f, 0.0f );
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void menuhandler( int value )

{   
    switch (value)

    {	case 1:	// Go Full Screen
	
		{   glutFullScreen();
	    	break;
		}
	
		case 2:	// Go Windowed
	
		{	glutSetWindow( mainwinid );
			glutReshapeWindow( 640, 480 );
			glutPositionWindow( 0, 0 );
			break;
		}
    
		case 4:	// Quit
		
		{   exit(0);
		    break;
		}
    
		default:
		    break;
    }
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void mousehandler(int button, int state, int x, int y)

{   /*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

    {	movingxz = 1;
		movingy = 0;
		beginx = x;
		beginy = y;		//if(glutGetModifiers() & GLUT_ACTIVE_SHIFT)
    }

//int glutGetModifiers(void)  

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  
    {	movingxz = 0;
    }
    
    if ( (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) || ((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)&&glutGetModifiers()==GLUT_ACTIVE_SHIFT) )

    {	movingy = 1;
		movingxz = 0;
		beginx = x;
		beginy = y;
    }
  
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
  
    {	movingy = 0;
    }*/
}

///////////////////////////////////////////////////////////////

void motionhandler(int x, int y)

{   /*extern int movingxz;
    extern int movingy;
    extern int beginx;
    extern int beginy;
    extern F32 eyex;
    extern F32 eyey;
    extern F32 eyez;
    extern F32 h, p, zoom;
    extern U32 gmassn;
    
    int deltax;
    int deltay;
            
    deltax = beginx - x;
    deltay = beginy - y;
      
    if( movingxz == 1 )
    
    {	h += (F32) (deltax/4800.0f);
		p += (F32) (deltay/4800.0f);
    }

	else if( movingy == 1 )
    
    {	zoom += (F32) (deltay/2400.0f);
    }
    
    eyex = zoom * sinf( h * PI2 * DEG2RAD );
    eyey = zoom * sinf( p * PI2 * DEG2RAD );
    eyez = zoom * cosf( h * PI2 * DEG2RAD );*/
    
}

///////////////////////////////////////////////////////////////

void keyboardhandler( unsigned char key, int x, int y )

{	/*static F32 saveval;
	int dx, dy;
	
	
	
	dx = x;
	dy = y;
		
	switch( key )
	{	
		case ' ':
			re_init();
			break;
		case '/':
			gvmass[gmassn] /= 10.0f;
			break;
		case '*':
			gvmass[gmassn] *= 10.0f;
			break;
		case ']':
			gpointsize *= 1.25f;
			break;
		case '[':
			gpointsize /= 1.25f;
			break;
		case '}':
			NPAR *= 2;
			re_init();
			break;
		case '{':
			NPAR /= 2;
			re_init();
			break;
		case '-':
			gvmass[gmassn] /= 1.1f;
			break;
		case '+':
			gvmass[gmassn] *= 1.1f;
			break;
		case 's':
			saveval = gvmass[gmassn];
			break;
		case 'l':
			gvmass[gmassn] = saveval;
			break;
		case '0':
			gvmass[gmassn] = 1.0f;
			break;
		case 'a':
			attreptoggle[gmassn] = 1.0f;
			break;
		case 'r':
			attreptoggle[gmassn] = -1.0f;
			break;
		case 'd':
			attached[gmassn] = false;
			break;
		case 'D':
			for( U32 di=0; di<4; di++ )	// detach others
			{	if( di != gmassn ) attached[di] = false;
			}
			attached[gmassn] = true;			
			break;
		case '1':
			gmassn = 0;
			break;
		case '2':
			gmassn = 1;
			break;
		case '3':
			gmassn = 2;
			break;
		case '4':
			gmassn = 3;
			break;
		case 'i':
			if( showtext==FALSE ) showtext=TRUE;
			else( showtext = FALSE );
			break;		
		case 'h':
			if( showhelp==FALSE ) showhelp = TRUE;
			else showhelp = FALSE;
			break;
		case '.':		
			if( showparticles==FALSE ) showparticles = TRUE;
			else showparticles = FALSE;
			break;
		case '>':
			if( dots==FALSE ) dots = TRUE;
			else dots = FALSE;
			break;
		case 'g':
			if( nmgrav==FALSE ) nmgrav = TRUE;
			else nmgrav = FALSE;
			break;
	}
	
	updatetexts();	*/

}

///////////////////////////////////////////////////////////////
