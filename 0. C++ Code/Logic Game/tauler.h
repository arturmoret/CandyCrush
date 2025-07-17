#include "candy.h"
#include "posicio.h"

class Tauler
{
public:
	Tauler();
	void setCandy(int fila, int columna, const Candy& candy) { m_tauler[fila][columna] = candy; }
	void inicialitza(istream& fitxer);
	Candy getCandy(int fila, int columna) { return m_tauler[fila][columna]; }
	void desplacarICrearCaramels();
	void intercanviarCaramels(const Posicio& pos1, const Posicio& pos2);
	bool movimentValid(const Posicio& pos1, const Posicio& pos2);
	int caramelsAlineatsFiles(const Posicio& pos);
	int caramelsAlineatsColumnes(const Posicio& pos);
	bool eliminarCaramelsAlineats(const Posicio& pos1, const Posicio& pos2);
	void eliminaFila(const int& i);
	void eliminaColumna(const int& j);
	bool comprovaTauler();
	Direccio comprovaDireccio(const Posicio& pos1, const Posicio& pos2);
	void eliminaCaramel(const int& i, const int& j);
	void dibuixaTauler(Posicio pos, int x, int y);
	int getNCondicioComplides() { return m_nCondicioComplides; }
	void setNCondicioComplides(int m) { m_nCondicioComplides = m; }
	void setCondicio(ColorCandy color) { m_condicio = color; }
	int getPuntuacio() { return m_puntuacio;  }
	void setnCondicio(int m) { m_nCondicio = m; }
	int getnCondicio() { return m_nCondicio; }

private:
	int m_nCondicioComplides;
	int m_nCondicio;
	Candy m_tauler[MAX_COLUMNES][MAX_FILES];
	int m_nCandyCambi;
	ColorCandy m_condicio;
	int m_puntuacio;
};

