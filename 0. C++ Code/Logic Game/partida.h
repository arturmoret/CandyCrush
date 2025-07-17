#include "tauler.h"

class Partida
{
public:
	Partida() : m_posicio(-1, -1), m_nCondicio(0), m_movimentsLimit(0), m_tauler(), m_condicio(NO_COLOR) {}
	void inicialitza(const string& nomFitxer);
	void fesMoviment(const Posicio& pos1, const Posicio& pos2);
	void escriuTauler(const string& nomFitxer);
	void dibuixa(Final final, Posicio pos, int x, int y);
	int getPuntuacio() { return puntuacio; }
	int getMovimentsLimit() { return m_movimentsLimit; }
	int getMovimentsR() { return (m_movimentsLimit - m_nMoviments); }
	int getnCondicio() { return m_nCondicio; }
	ColorCandy getCondicio() { return m_condicio; }
	IMAGE_NAME transformaIm(ColorCandy color);
	int getCondicioRestants() { return (m_nCondicio - m_tauler.getNCondicioComplides()); }
	Final finalPartida();
	bool continuaMoviment();

private:

	Tauler m_tauler;
	int m_movimentsLimit;
	int m_nMoviments;
	ColorCandy m_condicio;
	int m_nCondicio;
	int puntuacio;
	Posicio m_posicio;
};