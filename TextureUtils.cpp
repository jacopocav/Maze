//
// Created by Admin on 26/05/2016.
//

#include <fstream>
#include "TextureUtils.h"

GLubyte *TextureUtils::ReadFromBMP(std::string path) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned dataPos;     // Position in the file where the actual data begins
    unsigned width, height;
    unsigned imageSize;   // = width*height*3
// Actual RGB data
    GLubyte * data;

    // Open the file
    FILE * file = fopen(path.c_str(),"rb");
    if (!file){printf("Image could not be opened\n"); return nullptr;}

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return nullptr;
    }

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return nullptr;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way

    // Create a buffer
    data = new GLubyte [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    for(int i = 0; i < imageSize; i += 3){
        auto tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }

    return data;

}