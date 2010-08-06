
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef VECTORSET_H
#define VECTORSET_H

class mlVector3D;

class VectorSet
{
public:
	VectorSet();
	VectorSet(int nMaxSize);
	virtual ~VectorSet();

	int GetMaxSize();
	int GetSize();
	mlVector3D * GetVector(int i);

	void SetVector(int i, const mlVector3D & vVector);
	void AddVector(const mlVector3D & vVector);

//@@	void RemoveVector(int i);

	mlVector3D & operator[](int index);

	int length;

private:
	mlVector3D** m_pVectors;
//@@	mlVector3D*	m_pVectors;
	int m_nMaxSize;
	int m_nSize;
};

#endif // VECTORSET_H

