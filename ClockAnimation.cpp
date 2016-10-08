/*Author: Xiaojie Li*/
#include <stdio.h> 
#include <time.h> 
#include <math.h>
#include "fssimplewindow.h"

void DrawClock(int hour, int minute, int second) {
	const double PI = 3.1415927;
	double r = 250.0;
	double cx = 400.0;
	double cy = 300.0;
	double short_mark_begin = 250 - 20;
	double short_mark_end = 250 - 10;
	double long_mark_begin = 250 - 50;
	double long_mark_end = 250 - 10;
	double hour_pin_length = 180;
	double minute_pin_length = 220;
	double second_pin_length = 230;

	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(8);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 64; i++) {
		double angle = (double)i*PI / 32.0;
		double x = cx + cos(angle)*r;
		double y = cy + sin(angle)*r;
		glVertex2d(x, y);
	}
	glEnd();

	// get the short mark
	glLineWidth(1);
	for (int j = 0; j < 60; j++) {
		glBegin(GL_LINES);
		double begin_x = cx + cos(2 * PI / 60 * j)*short_mark_begin;
		double begin_y = cy + sin(2 * PI / 60 * j)*short_mark_begin;
		double end_x = cx + cos(2 * PI / 60 * j)*short_mark_end;
		double end_y = cy + sin(2 * PI / 60 * j)*short_mark_end;
		glVertex2d(begin_x, begin_y);
		glVertex2d(end_x, end_y);
		glEnd();
	}

	// get the long mark
	glLineWidth(3);
	for (int k = 0; k < 12; k++) {
		glBegin(GL_LINES);
		double begin_x = cx + cos(2 * PI / 12 * k)*long_mark_begin;
		double begin_y = cy + sin(2 * PI / 12 * k)*long_mark_begin;
		double end_x = cx + cos(2 * PI / 12 * k)*long_mark_end;
		double end_y = cy + sin(2 * PI / 12 * k)*long_mark_end;
		glVertex2d(begin_x, begin_y);
		glVertex2d(end_x, end_y);
		glEnd();
	}

	// get the hour pin
	glLineWidth(6);
	double h_angle = (double)(hour * 5 + double(minute) / 12 - 15);

	glBegin(GL_LINES);
	glVertex2d(cx, cy);
	glVertex2d(cx + hour_pin_length*cos(h_angle*PI / 30), cy + hour_pin_length*sin(h_angle*PI / 30));
	glEnd();

	// get the minute pin
	glLineWidth(4);
	double m_angle = (double)minute - (double)15;

	glBegin(GL_LINES);
	glVertex2d(cx, cy);
	glVertex2d(cx + minute_pin_length*cos(m_angle*PI / 30), cy + minute_pin_length*sin(m_angle*PI / 30));
	glEnd();

	// get the second pin 
	glLineWidth(2);
	double s_angle = (double)second - (double)15;

	glBegin(GL_LINES);
	glVertex2d(cx, cy);
	glVertex2d(cx + second_pin_length*cos(s_angle*PI / 30), cy + second_pin_length*sin(s_angle*PI / 30));
	glEnd();
}


void GetLocalTimeHourMinSec(int &hour,int &min,int &sec) { 
	struct tm *localTime; 
	time_t t=time(NULL); 
	localTime=localtime(&t); 
	hour=localTime->tm_hour; 
	min=localTime->tm_min; 
	sec=localTime->tm_sec; 
} 

int main() { 
	FsOpenWindow(16, 16, 800, 600, 1);
	int terminate = 0;
	int hour = 0, minute = 0, second = 0;
	while (terminate == 0) {
		FsPollDevice();
		int key = FsInkey();
		if (key == FSKEY_ESC) {
			terminate = 1;
		}
		GetLocalTimeHourMinSec(hour, minute, second);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		DrawClock(hour, minute, second);
		FsSwapBuffers();
		FsSleep(25);
	}
}

