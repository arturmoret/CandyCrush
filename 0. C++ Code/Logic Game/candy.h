#include "definicions.h"


class Candy
{
public:
	Candy(): m_tipus(NO_TIPUS), m_color(NO_COLOR) { }

	TipusCandy getTipus() const { return m_tipus; }
	ColorCandy getColor() const { return m_color; }
	void setTipus(TipusCandy tipus) { m_tipus = tipus; }
	void setColor(ColorCandy color) { m_color = color; }
	void dibuixaCandy(int posX, int posY);
	void dibuixaCandyL(int posX, int posY, int pX, int pY);
	IMAGE_NAME transformaIm(ColorCandy color);

private:
	TipusCandy m_tipus;
	ColorCandy m_color;
};
	