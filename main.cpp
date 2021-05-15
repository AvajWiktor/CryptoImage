#include "MatrixRGB.h"

using namespace std;
using namespace cv;

int main() {
	MatrixRGB m("Grafika/original.png");
	uint8_t x = 99;
	do 
	{
		cout << "---------------W3LC0M3 1N MY CRYPT0 1M4G3---------------" << endl;
		cout << "----------01001101 01000101 01001110 01010101-----------" << endl;
		cout << "1 - 3NC0D3 M3554G3 " << endl;
		cout << "2 - D3C0D3 M3554G3 " << endl;
		cout << "3 - 3X1T " << endl;
		cout << "Y0UR CH01C3: "; cin >> x; cout << endl;

		switch (x) {
			case '1': 
			{
				string message;
				cout << "3NT3R Y0UR M3554G3: "; 
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
				std::getline(std::cin, message); 
				m.encodeMessage(message, "Grafika/encoded.png");
				break;
			}
			case '2': 
			{
				string path;
				cout << "3NT3R P4TH T0 D3C0D3: "; 
				std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
				getline(std::cin, path);
				cout << m.decodeMessage(path);
				break;
			}
			case '3':
			{
				break;
			}
			default: 
			{
				cout << "WR0NG 1NPUT"; 
				
				break; 
			}
		}
		std::system("pause");
		std::cin.clear();
		std::system("cls");
	} while (x != '3');
	return 0;
}