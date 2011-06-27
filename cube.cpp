//      cube.cpp
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


#include "cube.h"

Cube::Cube(string name,GLUquadricObj *quadratic, GLfloat size):Object(name,quadratic){
	this->size = size;
}

void Cube::DrawModel(){
	TRACE("Drawing cube:%s, size:%f\n",name.c_str(), size);
	// djoubert187 _at_ hotmail.com


    glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_QUADS);		
		// Front Face (note that the texture's corners have to match the quad's corners)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2, -size/2,  size/2);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(size, 0.0f); glVertex3f( size/2, -size/2,  size/2);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(size, size); glVertex3f( size/2,  size/2,  size/2);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, size); glVertex3f(-size/2,  size/2,  size/2);	// Top Left Of The Texture and Quad
   
		// Back Face
		glTexCoord2f(size, 0.0f); glVertex3f(-size/2, -size/2, -size/2);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(size, size); glVertex3f(-size/2,  size/2, -size/2);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, size); glVertex3f( size/2,  size/2, -size/2);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size/2, -size/2, -size/2);	// Bottom Left Of The Texture and Quad

		// Top Face
		glTexCoord2f(0.0f, size); glVertex3f(-size/2,  size/2, -size/2);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2,  size/2,  size/2);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(size, 0.0f); glVertex3f( size/2,  size/2,  size/2);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(size, size); glVertex3f( size/2,  size/2, -size/2);	// Top Right Of The Texture and Quad

		// Bottom Face       
		glTexCoord2f(size, size); glVertex3f(-size/2, -size/2, -size/2);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, size); glVertex3f( size/2, -size/2, -size/2);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size/2, -size/2,  size/2);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(size, 0.0f); glVertex3f(-size/2, -size/2,  size/2);	// Bottom Right Of The Texture and Quad

		// Right face
		glTexCoord2f(size, 0.0f); glVertex3f( size/2, -size/2, -size/2);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(size, size); glVertex3f( size/2,  size/2, -size/2);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, size); glVertex3f( size/2,  size/2,  size/2);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size/2, -size/2,  size/2);	// Bottom Left Of The Texture and Quad

		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2, -size/2, -size/2);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(size, 0.0f); glVertex3f(-size/2, -size/2,  size/2);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(size, size); glVertex3f(-size/2,  size/2,  size/2);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, size); glVertex3f(-size/2,  size/2, -size/2);	// Top Left Of The Texture and Quad
    glEnd();                                    
}
