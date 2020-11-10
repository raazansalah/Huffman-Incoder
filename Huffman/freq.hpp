
#ifndef FREQ_HPP
#define FREQ_HPP
#include <bits/stdc++.h>
#include "pgm.hpp"

using namespace std;

vector<int> frequency(s img)  // function to generate freq table of pixels
{
    vector<int> freq(256, 0);

    for (int i = 0; i < img.greyvalues.size(); i++)
    {
        freq[img.greyvalues[i]]++;
    }
    return freq;
}

void binaryToChar(string str, char &ch) //convert each 8 bits to corresponding char.
{
    int decimal = 0;
    int base = 1;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] == '1')
            decimal += base;
        base = base * 2;
    }
    ch = char(decimal);
}
void serializePic(string encodedData, s img, string filename) //function to add num of bits if the n_bits% !=0 cols>widht , rows >height
{
    ofstream output(filename, ios::binary);
    string temp_string = ""; 
    int h = img.rows;     // height
    int w = img.cols;    //width
    int r = encodedData.size() % 8; // r is a remainder
    int count = 8 - r;              //   number of bits which we need
    char maximumValue_char;      
    char temp_char;
    int temp_int;

    maximumValue_char = (char)img.maxgreyval;   // convert the max value to its corresponding char.
    output << h << " " << w;           // cout height , widht
    output.put(maximumValue_char);       // put in file  
    temp_char = (char)count;       // convert num. of aded bits to char 
    output.put(temp_char);    

    while (count--)        // loop for generate string of padding bits 
    {
        encodedData += '0';
    }

    for (int i = 0; i < encodedData.size(); i++) // loop to take first 8 bits
    {
        temp_string += encodedData[i]; 

        if ((i + 1) % 8 == 0)  // condition to check if we take set of 8 bits 
        {

            temp_int = stoi(temp_string, 0, 2);   // convert string to  decimal intger 
            output.put((char)temp_int);   // convert the decimal intger to char
            temp_string = "";            // intialize the temp string again to take next 8 bits
        }
    }
    output.close();
}


void deserializePic(string &encodedData, s &write_img, string filename)  // func to deserialize the data  which generated before 
{
    ifstream input(filename, ios::binary);        // Read from file 
    string temp_string = "";


    char temp_char;
    int temp_int;
    unsigned char uc;
    input >> temp_int;            
    write_img.rows = temp_int;      // read the value of int for heigth   
    input >> temp_int;
    write_img.cols = temp_int;     //read the value of 
    input.get(temp_char);       // Read the char of maxgreyvalue
    uc = (unsigned char)temp_char;  // convert it to unsigned char to gis us int from 0 to 255
    write_img.maxgreyval = (int)uc;   // put this value in int of maxgreyvalue in image data  
    input.get(temp_char);     // get next char 
    uc = (unsigned char)temp_char;  // convert it to unsigned char to give us int "nubmer of padding bits"
    int padding_bits=int(uc);   // convert this char to the corresponding int == added bits
    while(input.get(temp_char))       // looping on remaining char of pixles
    {
        temp_int = (int)temp_char;  // convert each char to the decimal numb
        std::bitset<8> data_bits(temp_int);   // convert each decimal 8 bits in binary 
        encodedData += data_bits.to_string(); // add this binary to string of encoded data 
    }
     while (padding_bits--)       // loop for removing the added bits for num >0  
        encodedData.pop_back(); // remove from the end 
    input.close();   // close the file
}
unordered_map<string, int> inverseCodes(const unordered_map<int, string> &Codes) // to invert the huffman code hashmap
    {
        unordered_map<string, int> invCode;
        for (auto &[value,code] :Codes)
        {
            invCode[code] = value;
        }
        return invCode;
    }


vector<int> Decodeing(string deserializedData, unordered_map <int,std::string> Codes) 
   {
        unordered_map<string, int> InvCode = inverseCodes(Codes);   
        vector<int> pic;                                             
        string Code;                                                  
        int i = 0;
        while ( i <deserializedData.size()) 
        {
            Code += deserializedData[i];
            if (InvCode.count(Code)) 
            {
                pic.push_back(InvCode[Code]);
                Code = "";
            }
            i++;
        }
        return pic;
    }




void  serializeFrq(vector<int> frequencyTable,string filename)     
   {
    ofstream output_file(filename,ios::binary); 
    for(int i=0;i<256;++i)
    {
        output_file<<frequencyTable[i]<<" ";  // out freq of index
    }
    output_file.close();  // close the file
   } 


   void  deserializeFrq(vector<int> &frequencyTable,string filename)  
   {
       ifstream input_file(filename,ios::binary);  //open file
    for(int i=0;i<256;++i)  
    {
        input_file>>frequencyTable[i]; // read from file
    }
    input_file.close();  // close the file
   }


#endif
