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
		
	Object *o = new Cylinder("objeto1",quadratic);
	o->LoadTexture(&texture[0]);
	
	Object *a = new Cylinder("pedaco2",quadratic);
	Object *b = new Cylinder("pedaco3",quadratic);
	Object *c = new Cylinder("pedaco4",quadratic);
	
	a->LoadTexture(&texture[0]);
	b->LoadTexture(&texture[1]);
	c->LoadTexture(&texture[1]);
	
	o->add(a);
	o->add(c);
	
	a->add(b);
	
	c->LoadTranslatef(0,0,0.5f);
	
	a->LoadTranslatef(0,0,0.5f);
	a->LoadRotatef(30,0,1,0);
	
	b->LoadTranslatef(0,0,0.5f);
	
	o->LoadRotatef(30,0,1,0);
	
	return o;
}
