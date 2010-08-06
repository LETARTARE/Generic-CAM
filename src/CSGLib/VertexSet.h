
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef VERTEXSET_H
#define VERTEXSET_H

class Vertex;

class VertexPointerSet
{
public:
	VertexPointerSet();
	VertexPointerSet(int nMaxSize);
	virtual ~VertexPointerSet();

	Vertex * GetVertexPtr(int nIndex);
	int GetNumVertexPointers();
	int GetMaxVertexPointers();

	void AddVertexPointer(Vertex * pPointer);

	void add(Vertex * pPointer);
	Vertex * get(int nIndex);

	Vertex* operator[](int index);

	int length;

private:

	Vertex ** m_pPointers;
	int m_nMaxPointers;
	int m_nNumPointers;
};

class VertexSet
{
public:
	VertexSet();
	VertexSet(int nMaxSize);
	virtual ~VertexSet();

	Vertex * GetVertex(int nIndex);
	int GetNumVertices();
	int GetMaxVertices();

	Vertex * AddVertex(const Vertex & vertex);

	Vertex & operator[](int index);

	bool contains(Vertex * pVertex);
	int indexOf(Vertex * pVertex);

	int length;

private:
	Vertex** m_pVertices;
//@@	Vertex * m_pVertices;
	int m_nMaxVertices;
	int m_nNumVertices;
};

#endif // VERTEXSET_H
