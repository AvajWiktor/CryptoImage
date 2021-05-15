#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <conio.h>
#include <bitset>
using namespace std;
using namespace cv;
class MatrixRGB
{
public:
	MatrixRGB(string originalone) 
    {
        _OriginalImagePath = originalone;
        makeMatrix();
	}
    string decodeMessage(string imagePath) 
    {
        _NewImagePath = imagePath;
        Mat NewImage = imread(_NewImagePath, IMREAD_COLOR); 

        if (NewImage.empty())
        {
            return "Could not read the image: "+ _NewImagePath;
        }

        for (int i = 0; i < _y; i++)
        {
            for (int j = 0; j < _x; j++)
            {
                Vec3b buf = NewImage.at<Vec3b>(i, j);
                _NewMatrix[i][j] = buf;
            }
        }

        string s;
        int k = 0;

        for (int i = 0; i < _y; i++)
        {
            for (int j = 0; j < _x; j++)
            {
                if (_OriginalMatrix[i][j].val[0] != _NewMatrix[i][j].val[0])
                {
                    s += to_string(abs(_OriginalMatrix[i][j].val[0] - _NewMatrix[i][j].val[0]) - 1);
                    k++;
                }
                else if (_OriginalMatrix[i][j].val[1] != _NewMatrix[i][j].val[1])
                {
                    s += to_string(abs(_OriginalMatrix[i][j].val[1] - _NewMatrix[i][j].val[1])-1);
                    k++;
                }
                else if (_OriginalMatrix[i][j].val[2] != _NewMatrix[i][j].val[2])
                {
                    s += to_string(abs(_OriginalMatrix[i][j].val[2] - _NewMatrix[i][j].val[2])-1);
                    k++;
                }
                if (k == 8)
                {
                    k = 0;       
                    _DecodedMessage += stoi(s, 0, 2);
                    s.clear();
                }
            }
        }
        return _DecodedMessage;
    }
    void encodeMessage(string msg, string messagePath) 
    {
        _MessageImagePath = messagePath;
        srand(time(NULL));
        Mat img(_y, _x, CV_8UC3, Scalar(0, 0, 0));

        uint16_t randomYPosition = 0;// rand() % uint16_t(_y - _y/2.0) +0;
        uint16_t randomXPosition = 0;//rand() % _x + 0;
        uint16_t messageSize = msg.length();
        uint16_t k = 0;
        string s;

        for (int i = 0; i < messageSize; i++)
        {
             s += bitset<8>(msg[i]).to_string();
        }

        for (int i = randomYPosition; (i < img.rows)&&(k<s.length()); i++)
        {
            for (int j = randomXPosition; (j < img.cols) && (k < s.length()); j++)
            {
                string temp;
                temp += s[k];
                uint8_t x = (1+stoi(temp));
                uint8_t v = _MessageMatrix[i][j][0];
                v -= x;
                _MessageMatrix[i][j].val[0] = v;
                k++;
            } 
        }

        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                img.at<Vec3b>(i, j).val[0] = _MessageMatrix[i][j].val[0];
                img.at<Vec3b>(i, j).val[1] = _MessageMatrix[i][j].val[1];
                img.at<Vec3b>(i, j).val[2] = _MessageMatrix[i][j].val[2];
            }
        }

        imwrite(_MessageImagePath,img);
    }
    void showMatrixes() {
        for (int i = 0; i < _y; i++)
        {
            for (int j = 0; j < _x; j++)
            {
               // cout << "X1: " << j << ", Y1: " << i <<",R:"<<int(_OriginalMatrix[i][j][0])<<",G:"<< int(_OriginalMatrix[i][j][1])<<",B:"<< int(_OriginalMatrix[i][j][2])<< endl;
              //  cout << "X2: " << j << ", Y2: " << i <<",R:"<< int(_MessageMatrix[i][j][0]) << ",G:" << int(_MessageMatrix[i][j][1]) << ",B:" << int(_MessageMatrix[i][j][2]) << endl;
              //  cout << "X3: " << j << ", Y3: " << i << ",B:" << int(_NewMatrix[i][j][0]) << ",G:" << int(_NewMatrix[i][j][1]) << ",R:" << int(_NewMatrix[i][j][2]) << endl;
            }
        }
    }
private:
    //functions
	void makeMatrix() 
    {
        Mat OriginalImage = imread(_OriginalImagePath, IMREAD_COLOR);
        Vec3b buf;
        _y = OriginalImage.rows;
        _x = OriginalImage.cols;

        if (OriginalImage.empty())
        {
            std::cout << "Could not read the image: " << _OriginalImagePath << std::endl;
        }
        //creating image size matrix filled by zeros
        for (int i = 0; i < _y; i++) 
        {
            vector<Vec3b> rowBuf;
            for (int j = 0; j < _x; j++) 
            {
                Vec3b a = Vec3b(0,0,0);
                rowBuf.push_back(a);
            }
            _OriginalMatrix.push_back(rowBuf);
            _NewMatrix.push_back(rowBuf);
            _MessageMatrix.push_back(rowBuf);
        }
        //filling both matrix with BGR values
        for (int i = 0; i < _y; i++) 
        {
            for (int j = 0; j < _x; j++)
            {
                Vec3b Obuf = OriginalImage.at<Vec3b>(i, j);
                _OriginalMatrix[i][j] = Obuf;
                _MessageMatrix[i][j] = Obuf;
            }
        }
	}
    //fields
	vector <vector<Vec3b>> _OriginalMatrix,_NewMatrix,_MessageMatrix; //original matrix and new matrix storage
	int _x, _y; //size of our images
    string _OriginalImagePath, _NewImagePath, _MessageImagePath; //images paths
    string _DecodedMessage="";
};

