//      object.cpp
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


#include "object.h"


Object::Object(string name, GLUquadricObj *quadratic)
{
	this->name = name;
	this->quadratic = quadratic;
	rotate_a=0.0f;rotate_x=0.0f;rotate_y=0.0f;rotate_z=0.0f;
	scale_x=1.0f;scale_y=1.0f;scale_z=1.0f;
	translate_x=0.0f;translate_y=0.0f;translate_z=0.0f;
	texture = NULL;
}


Object::~Object()
{
	/*glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);*/
}

void Object::Draw(){
	cout << "--->Starting drawing:"<< name << endl;
	this->SetMatrix();
	this->SetTexture();
	this->DrawModel();
	cout << "<---Ending drawing:"<< name << endl;
}

void Object::add(Object *object){
	childs.push_back(object);
}

void Object::LoadTexture(GLuint *texture){
	this->texture = texture;
}

void Object::SetTexture(){
	if(*texture)
		glBindTexture( GL_TEXTURE_2D,*texture);
}

void Object::SetMatrix(){
	cout << "Translating model:"<< name << endl;
	glTranslatef(translate_x,translate_y,translate_z);
	cout << "Rotating model:"<< name << endl;
	glRotatef(rotate_a,rotate_x,rotate_y,rotate_z);
	cout << "Scaling model:"<< name << endl;
	glScalef(scale_x,scale_y,scale_z);
}

void Object::DrawModel(){
	cout << "Drawing model:"<< name << endl;
}


