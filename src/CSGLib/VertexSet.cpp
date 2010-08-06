
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#include "VertexSet.h"

#include "VertexSet.h"
#include "Vertex.h"

#include <stdio.h>

// TODO: Find out what the typical maximum size is for the vertex pointer set.

VertexPointerSet::VertexPointerSet()
{
	m_nMaxPointers = 10000;
	m_nNumPointers = 0;
	length = m_nNumPointers;

	m_pPointers = new Vertex*[m_nMaxPointers];
}

VertexPointerSet::VertexPointerSet(int nMaxSize)
{
	m_nMaxPointers = nMaxSize;
	m_nNumPointers = 0;
	length = m_nNumPointers;

	m_pPointers = new Vertex*[m_nMaxPointers];
}

VertexPointerSet::~VertexPointerSet()
{
	delete [] m_pPointers;
}

Vertex * VertexPointerSet::GetVertexPtr(int nIndex)
{
	if(nIndex < 0) return 0;
	if(nIndex >= m_nNumPointers) return 0;

	Vertex * pVertex = m_pPointers[nIndex];
	return pVertex;
}

int VertexPointerSet::GetNumVertexPointers()
{
	return m_nNumPointers;
}

int VertexPointerSet::GetMaxVertexPointers()
{
	return m_nMaxPointers;
}

void VertexPointerSet::AddVertexPointer(Vertex * pPointer)
{
	if(m_nNumPointers >= m_nMaxPointers) return;

	m_pPointers[m_nNumPointers] = pPointer;
	m_nNumPointers++;
	length = m_nNumPointers;
}

void VertexPointerSet::add(Vertex * pPointer)
{
	AddVertexPointer(pPointer);
}

Vertex * VertexPointerSet::operator[](int index)
{
	Vertex * pVertex = GetVertexPtr(index);

	// Do something if its null....

	return pVertex;
}

//////////////////////////////////////////////////////////////////////

VertexSet::VertexSet()
{
	m_nMaxVertices = 10000;
	m_nNumVertices = 0;
	length = m_nNumVertices;

	m_pVertices = new Vertex*[m_nMaxVertices];
	for(int i=0; i<m_nMaxVertices; i++)
		m_pVertices[i] = 0;
//@@	m_pVertices = new Vertex[m_nMaxVertices];
}

VertexSet::VertexSet(int nMaxSize)
{
	m_nMaxVertices = nMaxSize;
	m_nNumVertices = 0;
	length = m_nNumVertices;

	m_pVertices = new Vertex*[m_nMaxVertices];
	for(int i=0; i<m_nMaxVertices; i++)
		m_pVertices[i] = 0;
//@@	m_pVertices = new Vertex[m_nMaxVertices];
}

VertexSet::~VertexSet()
{
//@@	printf("Deleting vertex array\n");
//@@	delete [] m_pVertices;
	for(int i=0; i<m_nMaxVertices; i++)
	{
		if(m_pVertices[i])
			delete m_pVertices[i];
	}
	delete[] m_pVertices;
}

Vertex * VertexSet::GetVertex(int nIndex)
{
	if(nIndex < 0) return 0;
	if(nIndex >= m_nNumVertices) return 0;

	return m_pVertices[nIndex];
//@@	return &m_pVertices[nIndex];
}

int VertexSet::GetNumVertices()
{
	return m_nNumVertices;
}

int VertexSet::GetMaxVertices()
{
	return m_nMaxVertices;
}

Vertex * VertexSet::AddVertex(const Vertex & vertex)
{
	if(m_nNumVertices >= m_nMaxVertices) return 0;

	m_pVertices[m_nNumVertices] = new Vertex;
	*m_pVertices[m_nNumVertices] = vertex;
//@@	m_pVertices[m_nNumVertices] = vertex;
	m_nNumVertices++;
	length = m_nNumVertices;

	return m_pVertices[m_nNumVertices - 1];
//@@	return &m_pVertices[m_nNumVertices - 1];
}

Vertex & VertexSet::operator[](int index)
{
	Vertex * pVertex = GetVertex(index);

	// Do something if its null....

	return *pVertex;
}

bool VertexSet::contains(Vertex * pVertex)
{
	// Match pointers or content??
	// Match pointers.

	for(int i = 0; i < length; i++)
	{
		Vertex * pOurVertex = GetVertex(i);

		if(pOurVertex == pVertex)
		{
			return true;
		}
	}

	return false;
}

int VertexSet::indexOf(Vertex * pVertex)
{
	for(int i = 0; i < length; i++)
	{
		Vertex * pOurVertex = GetVertex(i);

		if(pOurVertex == pVertex)
		{
			return i;
		}
	}

	return -1;
}
