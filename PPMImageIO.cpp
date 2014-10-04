#include "PPMImageIO.h"

bool PPMReader(char* filename, int& height, int& width, GLubyte*& pixels)
{
    
    ifstream image(filename, ios::in | ios::binary);
    
    //if(image.good())
        //cout << "Successfully read image\n";
    
    char dummy;
	string sdummy;
	string magic_number;
	int maxcolor;
    image >> magic_number;
    
    if (magic_number != "P6")
        return false;
	
    dummy = image.get();
	int pos = static_cast<int>(image.tellg());
	dummy = image.get();
	if (dummy == '#')
        getline(image,sdummy);
	else
        image.seekg(pos);
	image >> height >> width >> maxcolor;
	if (maxcolor != 255)
        return false;
    image.get(dummy);
	pixels = new GLubyte[height*width*3];
    image.read((char*) pixels,height*width*3);
    image.close();
	return true;
}
