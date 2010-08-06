
// Author:        Greg Santucci
// Email:         thecodewitch@gmail.com
// Project page:  http://code.google.com/p/csgtestworld/
// Website:       http://createuniverses.blogspot.com/

#ifndef COLORSET_H
#define COLORSET_H

class gxColor;

class ColorSet
{
public:
	ColorSet();
	ColorSet(int nMaxSize);
	virtual ~ColorSet();

	int GetMaxSize();
	int GetSize();
	gxColor * GetColor(int i);

	void SetColor(int i, const gxColor & vColor);
	void AddColor(const gxColor & vColor);

	gxColor & operator[](int index);

	int length;

private:

	gxColor** m_pColors;
//@@	gxColor * m_pColors;
	int m_nMaxSize;
	int m_nSize;
};

#endif // COLORSET_H

