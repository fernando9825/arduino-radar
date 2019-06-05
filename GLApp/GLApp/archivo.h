#include <string>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;
#pragma once
inline string getCurrentDateTime(string s) {
	time_t now = time(0);
	struct tm  tstruct;
	char  buf[80];
	tstruct = *localtime(&now);
	if (s == "now")
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	else if (s == "date")
		strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
	return string(buf);
};
inline void Logger(int dis, int angulo, string ruta) {

	string filePath = ruta +"/DATOS.txt";
	string now = getCurrentDateTime("now");
	ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
	ofs << "OBJETO ENCONTRADO!  " << now << "  DISTANCIA = " << dis  << "  ANGULO = "<< angulo << endl;
	ofs.close();
}