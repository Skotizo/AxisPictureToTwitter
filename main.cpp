#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>         
#include <chrono>   
using namespace std;


void weather();
void download();
void post();

string arr[5];



int main()
{
	download();
        weather();
        post();
	while(0==0)
	{
		for (int i=3600; i>0; --i) {
			//hour timer
			std::this_thread::sleep_for (std::chrono::seconds(1));
		}
		download();
		weather();
		post();
	}
	return 0;
}



void download()
{
	system("curl https://HOSTNAME/jpg/image.jpg -o /root/AxisPictureToTwitter/images/photo.jpg"); //YOU MAY HAVE TO CHANGE THE IMAGES FOLDER LOCATION. LEAVE photo.jpg AT THE END BUT PWD IN /images DIR
}
void weather()
{

	system("weather -q ##### --imperial > weather.txt"); //ADD LOCAL ZIP CODE WHERE ##### IS
	string line;
	ifstream myfile ("weather.txt");
	if (myfile.is_open())
	{
	int i = 0;

		while ( getline (myfile,line) )
		{
      			arr[i] = line;
			//cout << arr[i] << endl;
			i++;
    		}
    	myfile.close();
	}
	system("touch weather.js");
	ofstream out ("weather.js");
	out << "var weather = [" << endl;
	out << "'";
	out << arr[0] << ". ";
        out << arr[1] << ". ";
        out << arr[2] << ". ";
        out << arr[3] << ". ";
        out << arr[4] << ". ";
	out << "'" << endl;
	out << "];" << endl;
	out << "module.exports = weather;" << endl;
	out.close();
}

void post()
{
	system("node server.js");
}


