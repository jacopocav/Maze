#include <GL/glut.h>
#include <iostream>

#include "GlutUtils.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutUtils::Init();
    return 0;
}

/*int main(){

    unsigned char img[512*512*3];
    int colorR = 127,
    colorG = 0,
    colorB = 0;

    for(int i=0; i<512; ++i){
        for(int j=0; j<512; ++j){

        }
    }
}*/