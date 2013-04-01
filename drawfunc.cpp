///////////////////////////////////////////////////////////////////////////////
// TWILIGHT (Port of old IRIX twilight backdrop from Iris GL to old school OpenGL)
///////////////////////////////////////////////////////////////////////////////
		
#include <math.h>
#include <vector>
#include <assert.h>
#include <stdio.h>

#include "gl.h"

struct color4{ float r, g, b, a; };

// prototypes
void draw_background(float x, float y);
color4 star_color(float y, float max_y);

// point in y where color transition occurs
#define TRANSITION 0.3f
#define NUM_SMALL_STARS 2500
#define NUM_BIG_STARS 200

static float orange[3] = {1.0f,0.3f,0};
static float blueish[3] = {0.0f,0.5f,0.7f};
static float black[3] = {0.0f,0.0f,0.0f};

extern GLsizei	gw, gh;


////////////////////////////////////////////////////////////////////////////////////
// draw particles
////////////////////////////////////////////////////////////////////////////////////

void drawfunc( void )
{	
	glClearColor( 0.1, 0.0, 0.0, 1.0 );
	glClearDepth( 0.0f );
	glViewport( 0, 0, gw, gh );
	glClear( GL_COLOR_BUFFER_BIT );
	assert(glGetError()==0);
	
	//////////////////////

	glDisable( GL_BLEND );
	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_STENCIL_TEST );
	glDisable( GL_SCISSOR_TEST );
	glDisable( GL_ALPHA_TEST );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_CULL_FACE );
	assert(glGetError()==0);
	glDisable( GL_FOG );
	assert(glGetError()==0);

	glColorMask(true,true,true,true);
	glShadeModel( GL_SMOOTH );
	//////////////////////
	assert(glGetError()==0);

	srand48(0);
	draw_background((float)gw, (float)gh);

	assert(glGetError()==0);
	//////////////////////
	glFlush();
	glutSwapBuffers();
	
}

void draw_background(float x, float y)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	gluOrtho2D(-.5, (float)gw-.5, -.5, (float)gh-.5);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	

	//////////////////////

    int i,j;
	float v1[2],v2[2],v3[2],v4[2];

	v1[0] = v4[0] = 0.0;
	v2[0] = v3[0] = x;
	
	v1[1] = v2[1] = 0.0;
	v3[1] = v4[1] = y*TRANSITION;

	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		//glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(gw,gh,0.0f);
		//glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	//printf( "yo\n" );

	glBegin(GL_QUADS);
		glColor3f(orange[0],orange[1],orange[2]);
		glVertex2fv(v1);
		glVertex2fv(v2);
		glColor3f(blueish[0],blueish[1],blueish[2]);
		glVertex2fv(v3);
		glVertex2fv(v4);
	glEnd();

	v1[1] = v2[1] = y;
	glBegin(GL_QUADS);
		glColor3f(blueish[0],blueish[1],blueish[2]);
		glVertex2fv(v4);
		glVertex2fv(v3);
		glColor3f(black[0],black[1],black[2]);
		glVertex2fv(v2);
		glVertex2fv(v1);
	glEnd();

	srand48(0); 

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < NUM_SMALL_STARS; i++)
		{	
			float frx = drand48();				
			float fry = drand48();				
			float fx = x*frx;
			float fy = y*fry;

			auto c = star_color(fy, y);
			glColor4f(c.r,c.g,c.b,logf(fry*3.0f));
							
				glVertex2f(fx,fy);
	    }
	}
	glEnd();


	glEnable( GL_POINT_SMOOTH );
	for( float fsize=1.0f; fsize<=2.0f; fsize += (drand48()*0.2f) )
	{
		glPointSize(fsize);
		glBegin(GL_POINTS);
		{
			int inump = drand48()*25.0f;
			for (int i = 0; i < inump; i++)
			{	
				float frx = drand48();				
				float fry = drand48();				
				float fx = x*frx;
				float fy = y*fry;

				auto c = star_color(fy, y);
				glColor4f(c.r,c.g,c.b,fry);							
				glVertex2f(fx,fy);
		    }
		}
		glEnd();
	}
}


color4 star_color(float y, float max_y)
{
    int r,g,b;
	float a;
	float ratio;
	color4 rval;

	if (y > max_y/2)
	{
		rval.r=1.0f;
		rval.g=1.0f;
		rval.b=1.0f;
		rval.a=0.5f;
		return rval;
	}


    if (y < TRANSITION*max_y)
	{
		ratio = y / (max_y * TRANSITION);
		
		r = orange[0]*(1.0 - ratio) + blueish[0]*ratio;
		g = orange[1]*(1.0 - ratio) + blueish[1]*ratio;
		b = orange[2]*(1.0 - ratio) + blueish[2]*ratio;
		a = 0.5f;
    }
	else
	{
		ratio = (y - max_y*TRANSITION)/(max_y - max_y*TRANSITION);
		
		r = blueish[0]*(1.0 - ratio) + black[0]*ratio;
		g = blueish[1]*(1.0 - ratio) + black[1]*ratio;
		b = blueish[2]*(1.0 - ratio) + black[2]*ratio;
		a = 0.5f;
    }

	/* r,g and b are now the sky color at y, now blend with white */

	a = (y/(max_y/2.0));

	rval.r = r*(1.0-a) + a;
	rval.g = g*(1.0-a) + a;
	rval.b = b*(1.0-a) + a;
	rval.a = a;
	return rval;
}
