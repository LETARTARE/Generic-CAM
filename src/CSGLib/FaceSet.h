
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef FACESET_H
#define FACESET_H

class Face;

class FaceSet
{
public:
	FaceSet();
	FaceSet(int nMaxSize);
	virtual ~FaceSet();

	int GetMaxSize();
	int GetSize();
	Face * GetFace(int i);

//@@	void SetFace(int i, Face & vFace);
	Face * AddFace(Face & vFace);
	Face * InsertFace(int i, Face & vFace);
	void RemoveFace(int i);

	Face * get(int i) { return GetFace(i); }
	void remove(int i);

	Face & operator[](int index);

	int length;

private:

	Face** m_pFaces;
//	Face * m_pFaces;
	int m_nMaxSize;
	int m_nSize;
};

#endif // FACESET_H

