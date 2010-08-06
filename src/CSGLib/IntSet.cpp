
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "IntSet.h"

// Complete

IntSet::IntSet()
{
	m_nMaxSize = 10000;
	m_nSize = 0;
	m_pInts = new int[m_nMaxSize];

	length = m_nSize;
}

IntSet::IntSet(int nMaxSize)
{
	m_nMaxSize = nMaxSize;
	m_nSize = 0;
	m_pInts = new int[m_nMaxSize];

	length = m_nSize;
}

IntSet::~IntSet()
{
	delete [] m_pInts;
}

int IntSet::GetMaxSize()
{
	return m_nMaxSize;
}

int IntSet::GetSize()
{
	return m_nSize;
}

int * IntSet::GetInt(int i)
{
	if(i < 0) return 0;
	if(i >= m_nSize) return 0;

	return &m_pInts[i];
}

void IntSet::SetInt(int i, int nInt)
{
	if(i < 0) return;
	if(i >= m_nSize) return;

	m_pInts[i] = nInt;
}

void IntSet::AddInt(const int nInt)
{
	if(m_nSize >= m_nMaxSize) return;

	m_pInts[m_nSize] = nInt;
	m_nSize++;

	length = m_nSize;
}

int & IntSet::operator[](int index)
{
	int * pInt = GetInt(index);

	// If its null, we're in trouble...

	return *pInt;
}
