//      createscene.cpp
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

#include "createscene.h"
#include <SDL/SDL_image.h>
#include <cmath>
#include <iostream>
#include <sstream>

#define NUM_TEXTURES 10


GLuint texture[NUM_TEXTURES]; /* Storage for 3 textures */

/* function to load in bitmap as a GL texture */
void LoadTexture(string img_path,int index )
{

    /* Create storage space for the texture */
    SDL_Surface *TextureImage; 

    /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
    if ( ( TextureImage = IMG_Load( img_path.c_str() ) ) )
        {

	    /* Load in texture 3 */
	    /* Typical Texture Generation Using Data From The Bitmap */
	    glBindTexture( GL_TEXTURE_2D, texture[index] );

	    /* Mipmapped Filtering */
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_LINEAR_MIPMAP_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_LINEAR );

	    /* Generate The MipMapped Texture ( NEW ) */
	    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, TextureImage->w,
			       TextureImage->h, GL_BGR,
			       GL_UNSIGNED_BYTE, TextureImage->pixels );
			       
		 SDL_FreeSurface(TextureImage);
		
        }
    else{
		cout<<"[Warning]Texture " << img_path << " not loaded"<<endl;
	}

}

Object* createScene(GLUquadricObj *quadratic){
	
	/* Create The Texture */
	glGenTextures( NUM_TEXTURES, &texture[0] );
	
	/* Load in the texture */
    LoadTexture("data/rope.bmp",0);
    LoadTexture("data/old_wood.bmp",1);
    LoadTexture("data/crate.bmp",2);
    
    LoadTexture("data/rays_up.bmp",3);
    LoadTexture("data/rays_down.bmp",4);
    LoadTexture("data/rays_east.bmp",5);
    LoadTexture("data/rays_west.bmp",6);
    LoadTexture("data/rays_north.bmp",7);
    LoadTexture("data/rays_south.bmp",8);
    
    Object *o,*plano, *skybox, *box1,*box2,*box3;
	
	o=NULL;
    
    Model *model;
    
    Object *buffer_left,*last_left,*buffer_right,*last_right;
    for(int i=0;i<30;i++){
		ostringstream stm;
		stm << i;
		last_left = buffer_left;
		last_right = buffer_right;
		buffer_left= new Cylinder("pedaco left"+stm.str(),quadratic,0.025f,0.2f);
		buffer_left->LoadTexture(&texture[0]);
		buffer_right= new Cylinder("pedaco right"+stm.str(),quadratic,0.025f,0.2f);
		buffer_right->LoadTexture(&texture[0]);
		if (o!=NULL){
			buffer_left->LoadRotatef(-2.0f,1.0f,0.0f,0.0f);
			buffer_left->LoadTranslatef(0.0f,0.0f,0.2f);
			buffer_right->LoadRotatef(-2.0f,1.0f,0.0f,0.0f);
			buffer_right->LoadTranslatef(0.0f,0.0f,0.2f);
			if (!(i%5)){
				plano = new Plane("degrau",quadratic,1,.2f);
				plano->LoadTranslatef(0.5f,0.0f,0.0f);
				plano->LoadTexture(&texture[1]);
				buffer_left->add(plano);
			}
			last_right->add(buffer_right);
			last_left->add(buffer_left);
		}
		else{
			plano = new Plane("plano",quadratic,100,50);
			buffer_left->LoadTranslatef(100.0f,0.0f,0.0f);
			plano->LoadTexture(&texture[4]);
			o = plano;
			o->add(buffer_right);
			o->add(buffer_left);
			buffer_left->LoadRotatef(30.0f,1.0f,0.0f,0.0f);
			buffer_left->LoadTranslatef(0.0f,0.0f,25.0f);
			buffer_right->LoadRotatef(30.0f,1.0f,0.0f,0.0f);
			buffer_right->LoadTranslatef(1.0f,0.0f,25.0f);
		}
		plano = new Plane("plano",quadratic,100,50);
		plano->LoadTexture(&texture[4]);
		plano->LoadTranslatef(1.0f,0.0f,55.5f);
		o->add(plano);
		
		skybox = new Skybox("skybox",quadratic,100.0f);
		skybox->LoadTexture(&texture[3]);
		skybox->LoadTranslatef(0,10.0f,20);	
		o->add(skybox);
		
		model = new Model("arvore",quadratic,2.0f);
		model->LoadTranslatef(-0.3,2,23);
		model->LoadTexture(&texture[0]);
		model->LoadModel("data/tree1.obj");
		o->add(model);
		
		box1 = new Cube("box1",quadratic,0.25f);
		box1->LoadTexture(&texture[2]);
		box1->LoadTranslatef(1.5,0.25f,23);
		box1->LoadRotatef(30,0,-1,0);
		o->add(box1);
		
		box2 = new Cube("box2",quadratic,1);
		box2->LoadTexture(&texture[2]);
		box2->LoadTranslatef(1,2,0);
		box1->add(box2);
		
		box3 = new Cube("box3",quadratic,1);
		box3->LoadTexture(&texture[2]);
		box3->LoadTranslatef(2,0,0);
		box3->LoadRotatef(30,0,1,0);
		box1->add(box3);
		
	}
	return o;
}
