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
	texture = (GLuint)0;
}


Object::~Object()
{
	/*glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);*/
}

void Object::Draw(){
	TRACE("----->glPushMatrix():%s\n",name.c_str());
	glPushMatrix();
	this->SetMatrix();
	this->SetTexture();
	this->DrawModel();
	printf("Drawing child %s\n", this->getName().c_str());
	list<Object*>::iterator it;
	for( it = childs.begin(); it != childs.end(); ++it ){
		(*it)->Draw();
	}
	TRACE("<-----glPopMatrix():%s\n",name.c_str());
	glPopMatrix();
}

void Object::add(Object *object){
	childs.push_back(object);
}

void Object::LoadTexture(GLuint *texture){
	this->texture = *texture;
}

void Object::SetTexture(){
	if(texture){
		TRACE("glBindTexture(GL_TEXTURE_2D,%d):%s\n",texture,name.c_str());
		glBindTexture(GL_TEXTURE_2D,texture);
	}
}

void Object::SetMatrix(){
	TRACE("glTranslatef(%0.2f,%0.2f,%0.2f):%s\n",translate_x,translate_y,translate_z,name.c_str());
	glTranslatef(translate_x,translate_y,translate_z);
	TRACE("glRotatef(%0.2f,%0.2f,%0.2f,%0.2f):%s\n",rotate_a,rotate_x,rotate_y,rotate_z,name.c_str());
	glRotatef(rotate_a,rotate_x,rotate_y,rotate_z);
	TRACE("glScalef(%0.2f,%0.2f,%0.2f):%s\n",scale_x,scale_y,scale_z,name.c_str());
	glScalef(scale_x,scale_y,scale_z);
}

void Object::DrawModel(){
	TRACE("Drawing model:%s\n",name.c_str());
}

void Object::LoadTranslatef(GLfloat translate_x,GLfloat translate_y,GLfloat translate_z){
	this->translate_x = translate_x;
	this->translate_y = translate_y;
	this->translate_z = translate_z;
}

void Object::LoadRotatef(GLfloat rotate_a,GLfloat rotate_x,GLfloat rotate_y,GLfloat rotate_z){
	this->rotate_a = rotate_a;
	this->rotate_x = rotate_x;
	this->rotate_y = rotate_y;
	this->rotate_z = rotate_z;
}

void Object::LoadScalef(GLfloat scale_x,GLfloat scale_y,GLfloat scale_z){
	this->scale_x = scale_x;
	this->scale_y = scale_y;
	this->scale_z = scale_z;
}

string Object::getName(void){
	return name;
}
