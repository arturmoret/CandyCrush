#ifndef DEFINICIONS_H
#define DEFINICIONS_H

#include <iostream>
#include <fstream>
#include "GraphicManager.h"
#include "InfoJoc.h"
using namespace std;

typedef enum
{
    VERD,
    LILA,
    BLAU,
    TARONJA,
    VERMELL,
    GROC,
    NO_COLOR
} ColorCandy;

typedef enum
{
    NORMAL,
    RATLLAT_HORIZONTAL,
    RATLLAT_VERTICAL,
    NO_TIPUS
} TipusCandy;

typedef enum
{
    MATCHING_PRIMARI,
    MATCHING_SECUNDARI
} TipusMatch;

typedef enum
{
    HORIZONTAL,
    VERTICAL,
    DESCONEGUDA
} Direccio;

typedef enum
{
    GUANYAT,
    PERDUT,
    NO_ACABAT
} Final;

const int MAX_FILES = 10;
const int MAX_COLUMNES = 10;
const int MIN_MATCHING = 3;
const int MIN_CARAMEL_ESPECIAL = 4;


#endif

