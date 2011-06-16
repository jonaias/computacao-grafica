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
    LoadTexture("data/old_wood.jpg",1);
    
    Object *o,*plano;
	
	o=NULL;
    
    Object *buffer_left,*last_left,*buffer_right,*last_right;
    int a=0;
    for(int i=0;i<31;i++){
		last_left = buffer_left;
		last_right = buffer_right;
		buffer_left= new Cylinder("pedaco left",quadratic,0.025f,0.2f);
		buffer_left->LoadTexture(&texture[0]);
		buffer_right= new Cylinder("pedaco right",quadratic,0.025f,0.2f);
		buffer_right->LoadTexture(&texture[0]);
		if (o!=NULL){
			buffer_left->LoadRotatef(-2,1,0,0);
			buffer_left->LoadTranslatef(0,0,0.2f);
			buffer_right->LoadRotatef(-2,1,0,0);
			buffer_right->LoadTranslatef(0,0,0.2f);
			if (!(i%5)){
				plano = new Plane("degrau",quadratic,1,.2f);
				plano->LoadTranslatef(0.5,0,0);
				plano->LoadTexture(&texture[1]);
				buffer_left->add(plano);
			}
			last_right->add(buffer_right);
			last_left->add(buffer_left);
			a++;
		}
		else{
			plano = new Plane("plano",quadratic,8,2);
			plano->LoadTexture(&texture[1]);
			o = plano;
			o->add(buffer_left);
			o->add(buffer_right);
			buffer_left->LoadRotatef(30,1,0,0);
			buffer_right->LoadRotatef(30,1,0,0);
			buffer_right->LoadTranslatef(1,0,0);
		}
				
	}
	printf("o valor de a e %d\n",a);
	return o;
}
