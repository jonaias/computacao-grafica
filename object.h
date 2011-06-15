//      object.h
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

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <list>
#include <iostream>
#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

//Uncomment to stop debugging
#define NDEBUG

#ifndef NDEBUG
#define TRACE printf
#else
#define TRACE(...)
#endif


using namespace std;

class Object
{
	public:
		Object(string name,GLUquadricObj *quadratic);
		virtual ~Object();
		virtual void Draw();
		virtual void DrawModel();
		void SetTexture();
		void add(Object *object);
		void LoadTexture(GLuint *texture);
		void SetMatrix();
		void LoadTranslatef(GLfloat translate_x,GLfloat translate_y,GLfloat translate_z);
		void LoadRotatef(GLfloat rotate_a,GLfloat rotate_x,GLfloat rotate_y,GLfloat rotate_z);
		void LoadScalef(GLfloat scale_x,GLfloat scale_y,GLfloat scale_z);
	
	protected:
		list<Object*> childs;
		string name;
		GLUquadricObj *quadratic;
		GLuint *texture;
		GLfloat rotate_a,rotate_x,rotate_y,rotate_z;
		GLfloat scale_x,scale_y,scale_z;
		GLfloat translate_x,translate_y,translate_z;
		/* add your private declarations */
};

#endif /* OBJECT_H */ 
