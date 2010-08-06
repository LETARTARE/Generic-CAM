
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "ColorSet.h"

#include "GX_Color.h"

// Complete

ColorSet::ColorSet()
{
	m_nMaxSize = 10000;
	m_nSize = 0;

	m_pColors = new gxColor*[m_nMaxSize];
	for(int i=0; i<m_nMaxSize; i++)
		m_pColors[i] = 0;
//@@	m_pColors = new gxColor[m_nMaxSize];

	length = m_nSize;
}

ColorSet::ColorSet(int nMaxSize)
{
	m_nMaxSize = nMaxSize;
	m_nSize = 0;

	m_pColors = new gxColor*[m_nMaxSize];
	for(int i=0; i<m_nMaxSize; i++)
		m_pColors[i] = 0;
//@@	m_pColors = new gxColor[m_nMaxSize];

	length = m_nSize;
}

ColorSet::~ColorSet()
{
	for(int i=0; i<m_nMaxSize; i++)
	{
		if(m_pColors[i])
			delete m_pColors[i];
	}
	delete [] m_pColors;
}

int ColorSet::GetMaxSize()
{
	return m_nMaxSize;
}

int ColorSet::GetSize()
{
	return m_nSize;
}

gxColor * ColorSet::GetColor(int i)
{
	if(i < 0) return 0;
	if(i >= m_nSize) return 0;

	return m_pColors[i];
//@@	return &m_pColors[i];
}

void ColorSet::SetColor(int i, const gxColor & vColor)
{
	if(i < 0) return;
	if(i >= m_nSize) return;

	if(m_pColors[i]) delete m_pColors[i];
	m_pColors[i] = new gxColor;
	*m_pColors[i] = vColor;
//@@	m_pColors[i] = vColor;
}

void ColorSet::AddColor(const gxColor & vColor)
{
	if(m_nSize >= m_nMaxSize) return;

	m_pColors[m_nSize] = new gxColor;
	*m_pColors[m_nSize] = vColor;
//@@	m_pColors[m_nSize] = vColor;
	m_nSize++;
	length = m_nSize;
}

gxColor & ColorSet::operator[](int index)
{
	gxColor * pColor = GetColor(index);

	// If its null, we're in trouble...

	return *pColor;
}
