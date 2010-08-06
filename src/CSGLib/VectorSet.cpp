
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include <memory.h>
#include "VectorSet.h"

#include "ML_Vector.h"

VectorSet::VectorSet()
{
	m_nMaxSize = 10000;
	m_nSize = 0;

	m_pVectors = new mlVector3D*[m_nMaxSize];
	for(int i=0; i<m_nMaxSize; i++)
		m_pVectors[i] = 0;
//@@	m_pVectors = new mlVector3D[m_nMaxSize];

	length = m_nSize;
}

VectorSet::VectorSet(int nMaxSize)
{
	m_nMaxSize = nMaxSize;
	m_nSize = 0;

	m_pVectors = new mlVector3D*[m_nMaxSize];
	for(int i=0; i<m_nMaxSize; i++)
		m_pVectors[i] = 0;
//@@	m_pVectors = new mlVector3D[m_nMaxSize];

	length = m_nSize;
}

VectorSet::~VectorSet()
{
	for(int i=0; i<m_nSize; i++)
		delete m_pVectors[i];
	delete[] m_pVectors;
//@@	delete [] m_pVectors;
}

int VectorSet::GetMaxSize()
{
	return m_nMaxSize;
}

int VectorSet::GetSize()
{
	return m_nSize;
}

mlVector3D * VectorSet::GetVector(int i)
{
	if(i < 0) return 0;
	if(i >= m_nSize) return 0;

	return m_pVectors[i];
//@@	return &m_pVectors[i];
}

void VectorSet::SetVector(int i, const mlVector3D & vVector)
{
	if(i < 0) return;
	if(i >= m_nSize) return;

	if(m_pVectors[i])	delete m_pVectors[i];
	m_pVectors[i] = new mlVector3D(vVector.x, vVector.y, vVector.z);
//@@	m_pVectors[i] = vVector;
}

void VectorSet::AddVector(const mlVector3D & vVector)
{
	if(m_nSize >= m_nMaxSize) return;

	if(m_pVectors[m_nSize])	delete m_pVectors[m_nSize];
	m_pVectors[m_nSize] = new mlVector3D(vVector.x, vVector.y, vVector.z);
//@@	m_pVectors[m_nSize] = vVector;
	m_nSize++;

	length = m_nSize;
}
/*@@
void VectorSet::RemoveVector(int i)
{
	// Shunt everything down over it
	if(m_nSize <= 0)
	{
		return;
	}
	delete m_pVectors[i];
	memcpy(m_pVectors[i], m_pVectors[i+1], sizeof(mlVector3D *) * (m_nSize-i));
	
//@@	for(int j = i; j < m_nSize-1; j++)
//@@	{
//@@		m_pVectors[j] = m_pVectors[j+1];
//@@	}
	
	m_nSize--;
	length = m_nSize;
}
*/
mlVector3D & VectorSet::operator[](int index)
{
	mlVector3D * pVector = GetVector(index);

	// If its null, we're in trouble...

	return *pVector;
}
