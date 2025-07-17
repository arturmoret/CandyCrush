#include "tauler.h"
#include <istream>
using namespace std;

Tauler::Tauler()
{
	m_nCandyCambi = 0;
	for (int i = 0; i < MAX_COLUMNES; i++) {
		for (int j = 0; j < MAX_FILES; j++) {
			m_tauler[i][j] = Candy();
		}
	}
	m_nCondicioComplides = 0;
	m_puntuacio = 0;
}

void Tauler::inicialitza(istream& fitxer)
{
	m_nCandyCambi = 0;
	m_puntuacio = 0;
	char candyAux;
	ColorCandy candyFinal;
	int i = 0;
	while (i < MAX_COLUMNES && !fitxer.eof())
	{
		int j = 0;
		while (j < MAX_FILES && !fitxer.eof())
		{
			fitxer >> candyAux;
			switch (candyAux)
			{
			case 'R': candyFinal = VERMELL; break;
			case 'O': candyFinal = TARONJA; break;
			case 'Y': candyFinal = GROC; break;
			case 'B': candyFinal = BLAU; break;
			case 'G': candyFinal = VERD; break;
			case 'P': candyFinal = LILA; break;
			default: candyFinal = NO_COLOR; break;
			}
			m_tauler[i][j].setColor(candyFinal);
			m_tauler[i][j].setTipus(NORMAL);
			j++;
		}
		i++;
	}
}

bool Tauler::movimentValid(const Posicio& pos1, const Posicio& pos2)
{
	bool juntas = false;
	// Comprobar si las posiciones son adyacentes en la misma fila
	if (pos1.getFila() == pos2.getFila() && abs(pos1.getColumna() - pos2.getColumna()) == 1)
	{
		juntas = true;
	}

	// Comprobar si las posiciones son adyacentes en la misma columna
	else if (pos1.getColumna() == pos2.getColumna() && abs(pos1.getFila() - pos2.getFila()) == 1)
	{
		juntas = true;
	}

	// Comprovar si l'intercanvi de caramels dona lloc a tres o més caramels del mateix tipus
	intercanviarCaramels(pos1, pos2);
	return (juntas && (caramelsAlineatsFiles(pos1) != -1 || (caramelsAlineatsColumnes(pos1) != -1 || caramelsAlineatsFiles(pos2) != -1 || caramelsAlineatsColumnes(pos2) != -1)));
}


int Tauler::caramelsAlineatsFiles(const Posicio& pos)
{
	int numAlineats = 1;
	int i = pos.getFila();
	int j = pos.getColumna();
	int color = m_tauler[i][j].getColor();
	bool trobat = false;

	while (j < MAX_COLUMNES - 1 && !trobat)
	{
		if (m_tauler[i][j + 1].getColor() == color)
		{
			numAlineats++;
			j++;
		}
		else
		{
			trobat = true;
		}
	}

	int k = pos.getFila();
	int l = pos.getColumna();
	trobat = false;

	while (l > 0 && !trobat)
	{
		if (m_tauler[k][l - 1].getColor() == color)
		{
			numAlineats++;
			l--;
		}
		else
		{
			trobat = true;
		}
	}

	if (numAlineats >= 3)
	{
		return numAlineats;
	}
	else
	{
		return -1;
	}
}

int Tauler::caramelsAlineatsColumnes(const Posicio& pos)
{
	int numAlineats = 1;
	int i = pos.getFila();
	int j = pos.getColumna();
	int color = m_tauler[i][j].getColor();
	bool trobat = false;

	while (i < MAX_FILES - 1 && !trobat)
	{
		if (m_tauler[i + 1][j].getColor() == color)
		{
			numAlineats++;
			i++;
		}
		else
		{
			trobat = true;
		}
	}

	int k = pos.getFila();
	int l = pos.getColumna();
	trobat = false;

	while (k > 0 && !trobat)
	{
		if (m_tauler[k - 1][l].getColor() == color)
		{
			numAlineats++;
			k--;
		}
		else
		{
			trobat = true;
		}
	}

	if (numAlineats >= 3)
	{
		return numAlineats;
	}
	else
	{
		return -1;
	}
}

bool Tauler::eliminarCaramelsAlineats(const Posicio& pos1, const Posicio& pos2)
{
	bool trobat = false, eliminat = false, especialHoritzontal = false, especialVertical = false;
	Direccio dir = comprovaDireccio(pos1, pos2);
	int i = pos1.getFila();
	int j = pos1.getColumna();
	int color = m_tauler[i][j].getColor();
	int numEliminacions = -1;
	//comprovem si s'ha d'eliminar de les files i/o columnes de pos1
	if (caramelsAlineatsFiles(pos1) != -1)
	{
		int numEliminacions = caramelsAlineatsFiles(pos1);
		if (numEliminacions >= 4)
		{
			if (dir == HORIZONTAL)
			{
				especialHoritzontal = true;
			}
			else if (dir == VERTICAL)
			{
				especialVertical = true;
			}
			else
			{
				especialHoritzontal = true;
			}
		}
		while (numEliminacions > 1 && !trobat && j >= 0)
		{
			if (m_tauler[i][j - 1].getColor() == color)
			{
				numEliminacions--;
				eliminaCaramel(i, j - 1);
				j--;
				eliminat = true;
			}
			else
			{
				trobat = true;
			}
		}
		if (numEliminacions > 1)
		{
			bool trobat = false;
			j = pos1.getColumna();
			while (numEliminacions > 1 && !trobat && j < MAX_COLUMNES - 1)
			{
				if (m_tauler[i][j + 1].getColor() == color)
				{
					numEliminacions--;
					eliminaCaramel(i, j + 1);
					j++;
					eliminat = true;
				}
				else
				{
					trobat = true;
				}
			}
		}
	}
	if (caramelsAlineatsColumnes(pos1) != -1)
	{
		int numEliminacions = caramelsAlineatsColumnes(pos1);
		if (numEliminacions >= 4)
		{
			if (dir == HORIZONTAL)
			{
				especialHoritzontal = true;
			}
			else if (dir == VERTICAL)
			{
				especialVertical = true;
			}
			else
			{
				especialVertical = true;
			}
		}
		while (numEliminacions > 1 && !trobat && i < MAX_FILES)
		{
			if (m_tauler[i - 1][j].getColor() == color)
			{
				numEliminacions--;
				eliminaCaramel(i - 1, j);
				i--;
				eliminat = true;
			}
			else
			{
				trobat = true;
			}
		}
		if (numEliminacions > 1)
		{
			bool trobat = false;
			i = pos1.getFila();
			while (numEliminacions > 1 && !trobat && i < MAX_FILES - 1)
			{
				if (m_tauler[i + 1][j].getColor() == color)
				{
					numEliminacions--;
					eliminaCaramel(i + 1, j);
					i++;
					eliminat = true;
				}
				else
				{
					trobat = true;
				}
			}
		}
	}
	if (especialHoritzontal)
	{
		if (m_tauler[pos1.getFila()][pos1.getColumna()].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
		{
			m_nCondicioComplides++;
		}
		m_tauler[pos1.getFila()][pos1.getColumna()].setTipus(RATLLAT_HORIZONTAL);
		m_puntuacio += 10;
	}
	else if (especialVertical)
	{
		if (m_tauler[pos1.getFila()][pos1.getColumna()].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
		{
			m_nCondicioComplides++;
		}
		m_tauler[pos1.getFila()][pos1.getColumna()].setTipus(RATLLAT_VERTICAL);
		m_puntuacio += 10;
	}
	else if (eliminat)
	{
		if (m_tauler[pos1.getFila()][pos1.getColumna()].getTipus() == RATLLAT_HORIZONTAL)
		{
			eliminaFila(pos1.getFila());
		}
		else if (m_tauler[pos1.getFila()][pos1.getColumna()].getTipus() == RATLLAT_VERTICAL)
		{
			eliminaColumna(pos1.getColumna());
		}
		else
		{
			if (m_tauler[pos1.getFila()][pos1.getColumna()].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
			{
				m_nCondicioComplides++;
			}
			m_tauler[pos1.getFila()][pos1.getColumna()] = Candy();
			m_puntuacio += 10;
		}
	}
	return eliminat;
}

void Tauler::desplacarICrearCaramels()
{
	ColorCandy array[6] = { VERMELL, TARONJA, GROC, BLAU, VERD, LILA };
	bool noCanvis = false;
	while (!noCanvis)
	{
		noCanvis = true;
		for (int i = MAX_FILES - 1; i >= 0; i--)
		{
			for (int j = MAX_COLUMNES - 1; j >= 0; j--)
			{
				if (m_tauler[i][j].getColor() == NO_COLOR && m_tauler[i - 1][j].getColor() != NO_COLOR && i > 0)
				{
					Posicio p1(i, j), p2(i - 1, j);
					intercanviarCaramels(p1, p2);
					noCanvis = false;
				}
			}
		}
	}
	for (int i = MAX_FILES; i >= 0; i--)
	{
		for (int j = 0; j < MAX_COLUMNES; j++)
		{
			if (m_tauler[i][j].getColor() == NO_COLOR)
			{
				m_tauler[i][j].setColor(array[m_nCandyCambi]);
				m_tauler[i][j].setTipus(NORMAL);
				m_nCandyCambi = (m_nCandyCambi + 1) % 6;
			}
		}
	}
}

void Tauler::eliminaCaramel(const int& i, const int& j)
{
	if (m_tauler[i][j].getTipus() == RATLLAT_HORIZONTAL)
	{
		eliminaFila(i);
	}
	else if (m_tauler[i][j].getTipus() == RATLLAT_VERTICAL)
	{
		eliminaColumna(j);
	}
	else
	{
		if (m_tauler[i][j].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
		{
			m_nCondicioComplides++;
		}
		m_tauler[i][j] = Candy();
		m_puntuacio += 10;
	}
}

void Tauler::dibuixaTauler(Posicio pos, int x, int y)
{
	for (int i = 0; i < MAX_FILES; i++)
	{
		for (int j = 0; j < MAX_COLUMNES; j++)
		{
			if (!(j == pos.getColumna() && i == pos.getFila()))
			{
				m_tauler[i][j].dibuixaCandy(j, i);
			}	
		}
	}
	if(pos.getColumna() != -1 && pos.getFila() != -1)
		m_tauler[pos.getFila()][pos.getColumna()].dibuixaCandyL(x, y, pos.getColumna(), pos.getFila());
}

void Tauler::intercanviarCaramels(const Posicio& pos1, const Posicio& pos2)
{
	Candy aux = m_tauler[pos1.getFila()][pos1.getColumna()];
	m_tauler[pos1.getFila()][pos1.getColumna()] = m_tauler[pos2.getFila()][pos2.getColumna()];
	m_tauler[pos2.getFila()][pos2.getColumna()] = aux;
}

void Tauler::eliminaFila(const int& i)
{

	// Elimina los candy de la Fila
	for (int j = 0; j < MAX_COLUMNES; j++)
	{
		if (m_tauler[i][j].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
		{
			m_nCondicioComplides++;
		}
		m_tauler[i][j] = Candy();
		m_puntuacio += 10;
	}
}


void Tauler::eliminaColumna(const int& j)
{
	// Elimina los candy de la Columna
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (m_tauler[i][j].getColor() == m_condicio && m_nCondicioComplides != m_nCondicio)
		{
			m_nCondicioComplides++;
		}
		m_tauler[i][j] = Candy();
		m_puntuacio += 10;
	}
}

bool Tauler::comprovaTauler()
{
	bool eliminat = false;
	for (int i = 0; i < MAX_FILES; i++)
	{
		for (int j = 0; j < MAX_COLUMNES; j++)
		{
			Posicio p(i, j);
			Posicio aux(-1, -1);
			if (caramelsAlineatsFiles(p) != -1)
			{
				eliminarCaramelsAlineats(p, aux);
				eliminat = true;
			}
			else if (caramelsAlineatsColumnes(p) != -1)
			{
				eliminarCaramelsAlineats(p, aux);
				eliminat = true;

			}
		}
	}
	return eliminat;
}

Direccio Tauler::comprovaDireccio(const Posicio& pos1, const Posicio& pos2)
{
	Direccio d = DESCONEGUDA;
	if (pos2.getFila() != -1)
	{
		if (pos1.getFila() == pos2.getFila() && abs(pos1.getColumna() - pos2.getColumna()) == 1)
		{
			d = HORIZONTAL;
		}
		else if (pos1.getColumna() == pos2.getColumna() && abs(pos1.getFila() - pos2.getFila()) == 1)
		{
			d = VERTICAL;
		}
	}
	return d;
}