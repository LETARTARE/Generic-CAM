
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef INTSET_H
#define INTSET_H

class IntSet
{
public:
	IntSet();
	IntSet(int nMaxSize);
	virtual ~IntSet();

	int GetMaxSize();
	int GetSize();
	int * GetInt(int i);

	void SetInt(int i, int nInt);
	void AddInt(int nInt);

	int & operator[](int index);

	int length;

private:

	int * m_pInts;
	int m_nMaxSize;
	int m_nSize;
};

#endif // INTSET_H

