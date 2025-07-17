#include "partida.h"

void Partida::inicialitza(const string& nomFitxer)
{
	puntuacio = 0;
	m_nMoviments = 0;
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		char condCandy;
		fitxer >> condCandy;
		switch (condCandy)
		{
		case 'R': m_condicio = VERMELL; break;
		case 'O': m_condicio = TARONJA; break;
		case 'Y': m_condicio = GROC; break;
		case 'B': m_condicio = BLAU; break;
		case 'G': m_condicio = VERD; break;
		case 'P': m_condicio = LILA; break;
		default: m_condicio = NO_COLOR; break;
		}
		m_tauler.setCondicio(m_condicio);
		fitxer >> m_nCondicio;
		m_tauler.setnCondicio(m_nCondicio);
		fitxer >> m_movimentsLimit;
		m_tauler.inicialitza(fitxer);
		fitxer.close();
	}
}

void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2)
{
	bool condicio = true;
	//Comprovar que l'intercanvi de caramels és vàlid
	if (!m_tauler.movimentValid(pos1, pos2))
	{
		m_tauler.intercanviarCaramels(pos1, pos2);
		condicio = false;
	}
	if (condicio)
	{
		// Eliminar del tauler tots els caramels alineats
		bool Al1 = m_tauler.eliminarCaramelsAlineats(pos1, pos2), Al2 = m_tauler.eliminarCaramelsAlineats(pos2, pos1);
		if (Al1 || Al2)
		{
			// Desplaçar i fer aparèixer els caramels necessaris per omplir les posicions eliminades
			m_tauler.desplacarICrearCaramels();
		}
		m_nMoviments++;
		puntuacio = m_tauler.getPuntuacio();
	}
}

Final Partida::finalPartida()
{
	if (m_nMoviments == m_movimentsLimit && m_tauler.getNCondicioComplides() < m_nCondicio)
	{
		return PERDUT;
	}
	else if (m_tauler.getNCondicioComplides() >= m_nCondicio)
	{
		m_tauler.setNCondicioComplides(m_nCondicio);
		return GUANYAT;
	}
	return NO_ACABAT;
}

bool Partida::continuaMoviment()
{
	bool condicio = false;
	while (m_tauler.comprovaTauler())
	{
		m_tauler.desplacarICrearCaramels();
		condicio = true;
	}
	return condicio;
}

void Partida::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	for (int i = 0; i < MAX_COLUMNES; i++)
	{
		for (int j = 0; j < MAX_FILES; j++)
		{
			if (m_tauler.getCandy(i, j).getTipus() == NORMAL)
			{
				switch (m_tauler.getCandy(i, j).getColor())
				{
				case VERMELL: fitxer << 'R'; break;
				case TARONJA: fitxer << 'O'; break;
				case GROC: fitxer << 'Y'; break;
				case BLAU: fitxer << 'B'; break;
				case VERD: fitxer << 'G'; break;
				case LILA: fitxer << 'P'; break;
				}
			}
			else
			{
				switch (m_tauler.getCandy(i, j).getColor())
				{
				case VERMELL: fitxer << 'r'; break;
				case TARONJA: fitxer << 'o'; break;
				case GROC: fitxer << 'y'; break;
				case BLAU: fitxer << 'b'; break;
				case VERD: fitxer << 'g'; break;
				case LILA: fitxer << 'p'; break;
				}
			}
		}
	}
	fitxer.close();
}

void Partida::dibuixa(Final final, Posicio pos, int x, int y)
{
	m_tauler.dibuixaTauler(pos, x, y);

	string msg = "";
	if (final == GUANYAT)
	{
		msg = "Has Guanyat!";
	}
	else if (final == PERDUT)
	{
		msg = "Has Perdut!";
	}
	string punt = "Puntuacio: " + to_string(getPuntuacio());
	string mov = "Moviments: " + to_string(getMovimentsR());
	string cond = "Falten: " + to_string(getCondicioRestants());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, PUNTS_INIT_X, PUNTS_INIT_Y, 1.0, punt);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, MOVIMENTS_INIT_X, MOVIMENTS_INIT_Y, 1.0, mov);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, OBJECTIU_INIT_X - 100, OBJECTIU_INIT_Y, 1.0, cond);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, FINAL_INIT_X, FINAL_INIT_Y, 1.0, msg);
	GraphicManager::getInstance()->drawSprite(transformaIm(getCondicio()), 540, 50, false);
}

IMAGE_NAME Partida::transformaIm(ColorCandy color)
{
	IMAGE_NAME Im;
	switch (color)
	{
	case BLAU:
		Im = IMAGE_PIECE_BLUE;
		break;
	case TARONJA:
		Im = IMAGE_PIECE_ORANGE;
		break;
	case VERMELL:
		Im = IMAGE_PIECE_RED;
		break;
	case VERD:
		Im = IMAGE_PIECE_GREEN;
		break;
	case GROC:
		Im = IMAGE_PIECE_YELLOW;
		break;
	case LILA:
		Im = IMAGE_PIECE_PURPLE;
		break;
	}
	return Im;
}