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
    
    Object *o,*plano_inicial, *plano_final, *degrau, *skybox, *box1,*box2,*box3, *box4;
	
	o=NULL;
    
    Model *tree1,*tree2,*tree3,*tree4;
    
    Object *buffer_left,*last_left,*buffer_right;
    for(int i=0;i<30;i++){
		ostringstream stm;
		stm << i;
		last_left = buffer_left;
		buffer_left= new Cylinder("ropepiece_left"+stm.str(),quadratic,0.025f,0.2f);
		buffer_left->LoadTexture(&texture[0]);
		buffer_right= new Cylinder("ropepiece_right"+stm.str(),quadratic,0.025f,0.2f);
		buffer_right->LoadTexture(&texture[0]);
		if (o!=NULL){
			buffer_left->LoadRotatef(-2.0f,1.0f,0.0f,0.0f);
			buffer_left->LoadTranslatef(0.0f,0.0f,0.2f);
			buffer_right->LoadTranslatef(1.0f,0.0f,0.0f);
			buffer_left->add(buffer_right);
			if (!(i%5)){
				ostringstream stm;
				stm << i/5;
				degrau = new Plane("step"+stm.str(),quadratic,1,.2f);
				degrau->LoadTranslatef(0.5f,0.0f,0.0f);
				degrau->LoadTexture(&texture[1]);
				buffer_left->add(degrau);
			}
			last_left->add(buffer_left);
		}
		else{
			plano_inicial = new Cube("inicial_cube",quadratic,50);
			plano_inicial->LoadTranslatef(0,-25.0f,0);
			plano_inicial->LoadTexture(&texture[4]);
			o = plano_inicial;
			
			o->add(buffer_left);
			
			buffer_left->LoadRotatef(30.0f,1.0f,0.0f,0.0f);
			buffer_left->LoadTranslatef(0.0f,25.0f,25.0f);
			
			buffer_right->LoadTranslatef(1.0f,0.0f,0.0f);
			buffer_left->add(buffer_right);
		}
	}
		
	
	plano_final = new Cube("final_cube",quadratic,50);
	plano_final->LoadTexture(&texture[4]);
	plano_final->LoadTranslatef(1.0f,-25.0f,55.5f);
	o->add(plano_final);
	
	skybox = new Skybox("skybox",quadratic,25.0f);
	skybox->LoadTexture(&texture[3]);
	skybox->LoadTranslatef(0,5.0f,37.5);	
	o->add(skybox);
	
	tree1 = new Model("tree1",quadratic,2.0f);
	tree1->LoadTranslatef(-0.3,2,23);
	tree1->LoadTexture(&texture[2]);
	tree1->LoadModel("data/tree1.obj");
	o->add(tree1);
	
	tree2 = new Model("tree2",quadratic,1.5f);
	tree2->LoadTranslatef(1,1.5,20);
	tree2->LoadTexture(&texture[2]);
	tree2->LoadModel("data/tree2.obj");
	o->add(tree2);
	
	tree3 = new Model("tree3",quadratic,4.0f);
	tree3->LoadTranslatef(-3.5,4,20);
	tree3->LoadTexture(&texture[2]);
	tree3->LoadModel("data/tree3.obj");
	o->add(tree3);
	
	tree4 = new Model("tree4",quadratic,3.0f);
	tree4->LoadTranslatef(5.5,2,20);
	tree4->LoadTexture(&texture[2]);
	tree4->LoadModel("data/tree4.obj");
	o->add(tree4);
	
	
	float box_scale=0.5f;
	box1 = new Cube("box1",quadratic,box_scale);
	box1->LoadTexture(&texture[2]);
	box1->LoadTranslatef(1.5,box_scale,23);
	box1->LoadRotatef(30,0,-1,0);
	o->add(box1);
	
	box2 = new Cube("box2",quadratic,box_scale);
	box2->LoadTexture(&texture[2]);
	box2->LoadTranslatef(box_scale/2,box_scale,0);
	box1->add(box2);
	
	box3 = new Cube("box3",quadratic,box_scale);
	box3->LoadTexture(&texture[2]);
	box3->LoadTranslatef(box_scale,0,0);
	box3->LoadRotatef(30,0,1,0);
	box1->add(box3);
	
	box4 = new Cube("box4",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(-1.5,box_scale,18);
	box4->LoadRotatef(30,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	
	
	
	tree2 = new Model("tree5",quadratic,2.0f);
	tree2->LoadTranslatef(3,2,0);
	tree2->LoadTexture(&texture[2]);
	tree2->LoadModel("data/tree2.obj");
	
	tree3 = new Model("tree6",quadratic,2.0f);
	tree3->LoadTranslatef(-3,2,0);
	tree3->LoadTexture(&texture[2]);
	tree3->LoadModel("data/tree3.obj");
	
	//lots of boxes
	box4 = new Cube("box5",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(-8,box_scale/2,18);
	box4->LoadRotatef(30,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	box4->add(tree2);
	
	box4 = new Cube("box6",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(8,box_scale/2,20);
	box4->LoadRotatef(30,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	box4->add(tree2);
	
	box4 = new Cube("box7",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(8,box_scale/2,35);
	box4->LoadRotatef(30,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	box4->add(tree3);
	
	box4 = new Cube("box8",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(-5,box_scale/2,35);
	box4->LoadRotatef(60,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	box4->add(tree3);
	box4->add(tree2);
	
	box4 = new Cube("box8",quadratic,box_scale);
	box4->LoadTexture(&texture[2]);
	box4->LoadTranslatef(-12,box_scale/2,33);
	box4->LoadRotatef(35,0,-1,0);
	o->add(box4);
	box4->add(box2);
	box4->add(box3);
	box4->add(tree3);
	box4->add(tree2);
	
	
	//trees
	
	tree2 = new Model("tree7",quadratic,2.0f);
	tree2->LoadTranslatef(12,2,33);
	tree2->LoadTexture(&texture[2]);
	tree2->LoadModel("data/tree2.obj");
	
	tree3 = new Model("tree8",quadratic,2.0f);
	tree3->LoadTranslatef(-3,0,0);
	tree3->LoadTexture(&texture[2]);
	tree3->LoadModel("data/tree3.obj");
	
	tree4 = new Model("tree9",quadratic,2.5f);
	tree4->LoadTranslatef(2,0,2);
	tree4->LoadTexture(&texture[2]);
	tree4->LoadModel("data/tree4.obj");
	
	tree2->add(tree3);
	tree2->add(tree4);
	o->add(tree2);
	
	
	return o;
}
