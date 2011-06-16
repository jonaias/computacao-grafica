//      ropepiece.cpp
//      
//      Copyright 2011 jonas <jonaias@jonaias-MX6453>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "plane.h"

Plane::Plane(string name,GLUquadricObj *quadratic, GLfloat length, GLfloat width):Object(name,quadratic){
	this->length = length;
	this->width = width;	
}

void Plane::DrawModel(){
	TRACE("Drawing cylinder:%s, length:%f, width:%f\n",name.c_str(),length,width);
	glBegin(GL_QUADS);						// Draw A Quad
		glNormal3f( 0.0f, 1.0f, 0.0f); 
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-length/2, 0, -width/2);				// Bottom Left
		glTexCoord2f(1.0f, 0.0f);glVertex3f(length/2, 0, -width/2);				// Bottom Right
		glTexCoord2f(1.0f, 1.0f);glVertex3f(length/2, 0,width/2);				// Top Right
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-length/2, 0,width/2);				// Top Left
	glEnd();
}
