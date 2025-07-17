#ifndef Joc_hpp
#define Joc_hpp

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "partida.h"

using namespace std;

typedef enum
{
    ESTAT_JOC_ESPERA,
    ESTAT_JOC_INTERCANVI,
    ESTAT_JOC_MOVIMENTS,
    ESTAT_FINAL
} EstatJoc;


class Joc 
{
public:
    Joc() : m_tempsEspera (0) {};
    void inicialitza(const string& nomFitxerInicial);
    void actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime);
private:
    Partida m_partida;
    EstatJoc m_estat;
    Posicio m_posicioIntercanvi;
    Posicio m_posicioDesti;
    int m_mouseIntercanviX, m_mouseIntercanviY;
    int m_despIntercanviX, m_despIntercanviY;
    double m_tempsEspera;
    bool m_click;
    Final final;
};

#endif /* Joc_hpp */
