#include "pgm.hpp"
#include "freq.hpp"
#include "huffman.hpp"
#include <bits/stdc++.h>
using namespace std;
void compress(s &read_img, string imageName)
{
    string encodedData = "";
    read_img = readpgm("Read.pgm");
    vector<int> frequencyTable;
    frequencyTable = frequency(read_img);
    unordered_map<int, string> Codes;
    Encode(frequencyTable, Codes);
    for (int i = 0; i < read_img.greyvalues.size(); ++i)
        encodedData += Codes[read_img.greyvalues[i]];
    serializePic(encodedData, read_img, "Result.enc");
    serializeFrq(frequencyTable, "Result.frq");
}
void decompress(s &write_img, string filename)
{
    string deserializedData = "";
    int padding_bits = 0;
    vector<int> deserializedFrequencyTable(256);

    deserializePic(deserializedData, write_img, "Result.enc");

    deserializeFrq(deserializedFrequencyTable, "Result.frq");
    unordered_map<int, string> decodedCodes;
    Encode(deserializedFrequencyTable, decodedCodes);

    write_img.greyvalues = Decodeing(deserializedData, decodedCodes);

   int n = writepgm(write_img, "test.pgm");
}

int main()
{
    s write_img;
    string imageName;
    s read_img;
    string filename;
     compress(read_img, imageName);
     decompress(write_img,filename);

    return 0;
}