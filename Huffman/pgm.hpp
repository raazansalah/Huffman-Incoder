#ifndef PGM_HPP
#define PGM_HPP
#include <bits/stdc++.h>
using namespace std;
//**************************************************************************************
struct s 
{
    unsigned int rows;
    unsigned int cols;
    unsigned int maxgreyval;
    std::string format;            // format ==P5 at first line
   //std::string message;           // second line
    std::vector<int> greyvalues; // vector to sace all grey values
};
//**************************************************************************************
// function to read the image
s readpgm(const std::string filename);
//function to write the image
int writepgm(const s image, const std::string filename);
//**************************************************************************************
// function to read the image
s readpgm(const string filename)
{
    s image;
    fstream in;
    in.open(filename, ios::in | ios::binary);
    if (!in.is_open())
    {
        cout << "Error" << endl;
        return image;
    }
    getline(in, image.format);
    if (image.format != "P5")
    {
        cout << "invalid" << endl;
        return image;
    }
    in >> image.cols; // to read the col. num
    in >> image.rows; // to read the rows. num
    int pixels;
    pixels = (image.rows * image.cols);
    cout << pixels << endl;          // num of pixels
    in >> image.maxgreyval;          // read max value of grey shades
    image.greyvalues.resize(pixels); // set the size of vector to the num of pixels
    for (int i = 0; i < pixels; i++) //loop to save the values of pixels into the vector
    {
        char c;
         in.read(&c, 1);
         unsigned char k=(unsigned char)c;
          image.greyvalues[i]=(int)k;
    }
    if (pixels != image.greyvalues.size())
        cout << "couldn't read all pixels" << endl;
    else
        cout << "Done" << endl; //  read all pixels
    return image;
}
//**************************************************************************************
//function to save the image
int writepgm(const s image, const std::string filename)
{
    fstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file.is_open())
    {
        cout << "Error" << endl;
        return -1;
    }
    file << "P5"<<endl;
    file << image.cols << " " << image.rows << endl;
    file << image.maxgreyval << endl;
    int p;                                                      // p for pixels number
    p = image.rows * image.cols;
    for (int i = 0;i < p; i++)
        file <<(unsigned char)image.greyvalues[i];
    return 0;
}
//**************************************************************************************
#endif