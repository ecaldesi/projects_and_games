// Elisabetta Caldesi and Anthony DiFalco
// fractals.cpp

#include "gfxnew.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <math.h>
using namespace std;

// prototypes of functions
void sierpinski(int, int, int, int, int, int); // function for case 1
void shrinkingsquares(int, int, double, double); // function for case 2
void spiralofsquares(double, double, double); // function for case 3
void circularLace(int, int, double); // function for case 4
void snowflake(int, int, double); // function for case 5
void drawtree(double, double, int, int); // function for case 6
void drawfern(double, double, double, double); // function for case 7
void drawcurls(double, double, double, double); // function for case 8
void drawTriangle(int, int, int, int, int, int); // function that draws a triangle

int main() {
	char c= ' ';
	int width= 800;
	int height= 800;
	int x,y,x1, y1, x2, y2, x3, y3;
	bool quit=false;
	int n;
	gfx_open(width, height, "Fractals");
	while(!quit){
		n= gfx_event_waiting();
		if (n!=0) {
			c = gfx_wait();
		}
		if (n==1){ // if keyboard is pressed
			gfx_clear();
			x= width/2;
			y= height/2;
			// user's choice
			if (c== '1'){
				// Sierpinski Triangle
				x1= x-300; 
				y1= y-300;
				x2= x+300;
				y2= y-300;
				x3= x;
				y3= y+300;
				sierpinski(x1,y1,x2,y2,x3,y3);
				gfx_flush();
			}else if (c=='2'){
				// Shrinking Squares
				double h= 400;
				double w= 400;
				x1= x-200;
				y1= y-200;
				shrinkingsquares(x1,y1,w,h);
				gfx_flush();
			}else if (c=='3'){
				// Spiral Squares
				double length= 70;
				double theta= 0;
				double radius= 400;
				spiralofsquares(length, theta, radius);
				gfx_flush();
			}else if (c=='4'){
				// Circular Lace
				double length= 250;
				circularLace(x,y,250);
				gfx_flush();
			}else if (c=='5'){
				// Snowflake
				double r=300;
				snowflake(x,y,r);
				gfx_flush();
			}else if (c=='6'){
				// Tree
				double theta= M_PI/2;
				double length= 200;
				int x=300;
				int y= 580;
				drawtree(theta, length, x, y);
				gfx_flush();
			}else if (c=='7'){
				// Fern
				double theta= M_PI/2;
				double length= 500;
				double X= 400;
				double Y= 780;
				drawfern(theta,length,X,Y);
				gfx_flush();
			}else if (c=='8'){
				// Spiral of Spirals	
				double theta= 0;
				double radius= 400;
				double X= 400;
				double Y= 400;
				drawcurls(theta, radius, X, Y);
				gfx_flush();
			}else if (c=='q'){
				quit = true;
			}
		}
	}
	return 0;
}

// function that draws sierpinski's triangle
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	// Base case. 
	if (abs(x2-x1) < 5) return;
	
	// Draw the triangle
	drawTriangle( x1, y1, x2, y2, x3, y3 );
	
	// Recursive calls
	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

// function that draws shrinking squares
void shrinkingsquares(int x1, int y1, double w, double h) { 

	// Base case.
	if (abs(w)< 2) return;

	// Draw square
	gfx_rectangle(x1,y1,w,h);

	// Recursive calls
	shrinkingsquares(x1-(w/5), y1-(h/5), w/2.5, h/2.5);
	shrinkingsquares((x1+w)-(w/5), y1-(h/5), w/2.5, h/2.5);
	shrinkingsquares(x1-(w/5), (y1+h)-(h/5), w/2.5, h/2.5);
	shrinkingsquares((x1+w)-(w/5), (y1+h)-(h/5), w/2.5, h/2.5);

}

// function that draws a spiral of squares
void spiralofsquares(double length, double theta, double radius) {
	
	// Base case
	if (radius < 2) return;

	// Draw squares
  	int center = 300;
     	double xcenter = radius*cos(theta) + center;
     	double ycenter = radius*sin(theta) + center;

     	gfx_line(xcenter - length,ycenter - length, 
		xcenter + length, ycenter - length);
     	gfx_line(xcenter + length,ycenter - length, 
		xcenter + length, ycenter + length);
        gfx_line(xcenter + length,ycenter + length, 
		xcenter - length, ycenter + length);
     	gfx_line(xcenter - length,ycenter + length, 
		xcenter - length, ycenter - length);

	// Recursive calls
     	theta = theta + M_PI/5;
     	length = length*.88;
     	radius = radius*.90;
    	spiralofsquares(length,theta,radius);	
}

// function that draws a circular lace
void circularLace (int x, int y, double length) {

	// Base case
	if (length < .05) return;
	double theta = 0;
	
	// Draw Circle
	gfx_circle(x,y,length);              

	// Recursive calls	
	circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

	theta = theta + M_PI/3;
        circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

        theta = theta + M_PI/3;
        circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

        theta = theta + M_PI/3; 
	circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

        theta = theta + M_PI/3; 
	circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

        theta = theta + M_PI/3; 
	circularLace(length*cos(theta)+x,length*sin(theta)+y,length/3);

        length = length/3;
}

// Function that draws a snowflake
void snowflake(int x, int y, double r){

	double theta= (2*M_PI)/5;

	// Base case 
	if (r<.5) return;

	// Draw lines
	for (int k=1; k<=5; k++){
		gfx_line(x,y, x+r*cos(theta*k), y+r*sin(theta*k));
		// Recursive calls
		snowflake(x+(r)*cos(theta*k), y+(r)*sin(theta*k), (r*.38));
	}
}

// function that draws a tree
void drawtree(double theta, double length, int x, int y){

	// Base case
	if (length < 1) return;
	
	// Draw lines
    	int x2 = x + length*cos(theta);
    	int y2 = y - length*sin(theta);
    	gfx_line(x,y,x2,y2);

	// Recursive calls
    	double theta2 = theta + M_PI/6;
    	theta = theta - M_PI/6;
    	length = length*.66;

    	drawtree(theta,length,x2,y2);
    	drawtree(theta2,length,x2,y2);
}

// function that draws a fern
void drawfern(double theta, double length, double X, double Y){

	// Base case
	if (length < 2) return;
    	
	// Draw lines
	double y2 = Y - length*sin(theta)/4;
	double x2 = X + length*cos(theta)/4;

	double y3 = Y - length*sin(theta)/2;
	double x3 = X + length*cos(theta)/2;

	double y4 = Y - length*sin(theta)*3/4;
	double x4 = X + length*cos(theta)*3/4;

	double y5 = Y - length*sin(theta);
	double x5 = X + length*cos(theta);
	
	gfx_line(X,Y,x5,y5);

	// Recursive calls
	double theta2 = theta + M_PI/6;
	theta = theta - M_PI/6;
	length = length*.3;

    	drawfern(theta,length,x2,y2);
    	drawfern(theta2,length,x2,y2);

 	drawfern(theta,length,x3,y3);
    	drawfern(theta2,length,x3,y3);

    	drawfern(theta,length,x4,y4);
    	drawfern(theta2,length,x4,y4);

    	drawfern(theta,length,x5,y5);
    	drawfern(theta2,length,x5,y5);
}

// function that draws a spiral of spirals 
void drawcurls(double theta, double radius, double X, double Y) {
	
	// Base case
	if (radius < 1) return;
   
	// Draw points
   	double newx = X + radius*cos(theta);
   	double newy = Y + radius*sin(theta);
   	gfx_point(newx,newy);

	// Recursive calls
   	radius = radius*.9;  
   	theta = theta + M_PI/6;
   	drawcurls(theta,radius,X,Y);
   	drawcurls(theta,radius/2.7,newx,newy); 

}

// function that draws a triangle
void drawTriangle (int x1, int y1, int x2, int y2, int x3, int y3){
	gfx_color(255,255,255);
	gfx_line(x1,y1,x2,y2);
	gfx_line(x1,y1,x3,y3);
	gfx_line(x2,y2,x3,y3);
}

