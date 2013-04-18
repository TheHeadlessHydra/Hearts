// std includes
#include <assert.h>
#include <iostream>
#include <stdlib.h>
// local includes
#include "Options.h"

Options::Options() : m_iMaxScore(40), m_iSeed(37), m_sFileName(""){}

Options::Options(int iScore, int iSeed, string sFileName) : m_iMaxScore(iScore), m_iSeed(iSeed), m_sFileName(sFileName){}

void Options::setMaxScore(int i)
{
	// Do not allow for negative or strinng maxScores
	if( i < 1 )
	{
		std::cerr << "Error, maxScore must be positive." << endl;
		exit(1);
	}
	m_iMaxScore = i;
}

int Options::getMaxScore(){ return m_iMaxScore; }


void Options::setSeed(int i)
{
	assert(i != 0); // Invalid seed!
	m_iSeed = i;
}
int Options::getSeed() { return m_iSeed; }

void Options::setFileName(string s)
{
	m_sFileName = s;
}

string Options::getFileName() { return m_sFileName; }