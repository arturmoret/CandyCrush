#include "Joc.hpp"
#include "InfoJoc.h"
#include "GraphicManager.h"

void Joc::inicialitza(const string& nomFitxer)
{
    m_partida.inicialitza(nomFitxer);
    m_estat = ESTAT_JOC_ESPERA;
    m_posicioIntercanvi.set(-1, -1);
    m_mouseIntercanviX = 0;
    m_mouseIntercanviY = 0;
    m_despIntercanviX = -1;
    m_despIntercanviY = -1;
    m_click = false;
    final = NO_ACABAT;
}

void Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime)
{
    switch (m_estat)
    {
    case ESTAT_JOC_ESPERA:
        if (!mouseStatus)
        {
            m_click = true;
        }
        else if (mouseStatus && m_click)
        {
            int posX = (mousePosX - CELL_INIT_X) / CELL_W;
            int posY = (mousePosY - CELL_INIT_Y) / CELL_H;
            if ((mousePosX >= CELL_INIT_X) && (mousePosX <= (CELL_INIT_X + (CELL_W * N_COLS))) &&
                (mousePosY >= CELL_INIT_Y) && (mousePosY <= (CELL_INIT_Y + (CELL_H * N_ROWS))))
            {
                m_posicioIntercanvi.set(posY, posX);
                m_estat = ESTAT_JOC_INTERCANVI;
                cout << "Pos1" << endl;
                m_mouseIntercanviX = mousePosX;
                m_mouseIntercanviY = mousePosY;
            }
            m_click = false;
        }
        break;
    case ESTAT_JOC_INTERCANVI:
        m_despIntercanviX = mousePosX;
        m_despIntercanviY = mousePosY;
        if (!mouseStatus)
        {
            m_click = true;
        }
        else if (mouseStatus && m_click)
        {
            int destX = (mousePosX - CELL_INIT_X) / CELL_W;
            int destY = (mousePosY - CELL_INIT_Y) / CELL_H;
            if ((mousePosX >= CELL_INIT_X) && (mousePosX <= (CELL_INIT_X + (CELL_W * N_COLS))) &&
                (mousePosY >= CELL_INIT_Y) && (mousePosY <= (CELL_INIT_Y + (CELL_H * N_ROWS))))
            {
                m_posicioDesti.set(destY, destX);
                m_partida.fesMoviment(m_posicioIntercanvi, m_posicioDesti);
                m_estat = ESTAT_JOC_MOVIMENTS;
                cout << "Pos2" << endl;
                m_posicioIntercanvi.set(-1, -1);
            }
            m_click = false;
        }
        break;
    case ESTAT_JOC_MOVIMENTS:
        m_tempsEspera += deltaTime;
        if (m_tempsEspera > TEMPS_PAUSA)
        {
            m_tempsEspera = 0.0;
            bool continua = m_partida.continuaMoviment();
            if (!continua)
            {
                final = m_partida.finalPartida();
                switch (final)
                {
                case GUANYAT:
                    m_estat = ESTAT_FINAL;
                    break;
                case PERDUT:
                    m_estat = ESTAT_FINAL;
                    break;
                case NO_ACABAT:
                    m_estat = ESTAT_JOC_ESPERA;
                    break;
                }
            }
        }
        break;
    case ESTAT_FINAL:
        break;
    }
    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);
    m_partida.dibuixa(final, m_posicioIntercanvi, m_despIntercanviX, m_despIntercanviY);
}
