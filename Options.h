#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <iostream>
#include <string>

using namespace std;

class Options
{
private:
	int m_iMaxScore;
	int m_iSeed;
	string m_sFileName;
public:
	Options();
	Options(int iScore, int iSeed, string sFileName);

	void setMaxScore(int i);
	int getMaxScore();

	void setSeed(int i);
	int getSeed();

	void setFileName(string s);
	string getFileName();
};

#endif