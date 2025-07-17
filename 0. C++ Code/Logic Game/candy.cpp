#include "candy.h"

void Candy::dibuixaCandy(int posX, int posY) {
    IMAGE_NAME Im;
    Im = transformaIm(m_color);
    GraphicManager::getInstance()->drawSprite(Im, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2),
        CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
}
void Candy::dibuixaCandyL(int posX, int posY, int pX, int pY) {
    IMAGE_NAME Im;
    Im = transformaIm(m_color);
    if ((posX >= CELL_INIT_X) && (posX <= (CELL_INIT_X + (CELL_W * N_COLS))) &&
        (posY >= CELL_INIT_Y) && (posY <= (CELL_INIT_Y + (CELL_H * N_ROWS))))
    {
        GraphicManager::getInstance()->drawSprite(Im, posX, posY, true);
    }
    else
    {
        GraphicManager::getInstance()->drawSprite(Im, CELL_INIT_X + (pX * CELL_W) + (CELL_W / 2),
            CELL_INIT_Y + (pY * CELL_H) + (CELL_H / 2), true);
    }
}

IMAGE_NAME Candy::transformaIm(ColorCandy color)
{
    IMAGE_NAME Im;
    switch (color)
    {
    case BLAU:
        Im = IMAGE_PIECE_BLUE;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_BLUE_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_BLUE_VERTICAL;
        break;
    case TARONJA:
        Im = IMAGE_PIECE_ORANGE;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_ORANGE_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_ORANGE_VERTICAL;
        break;
    case VERMELL:
        Im = IMAGE_PIECE_RED;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_RED_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_RED_VERTICAL;
        break;
    case VERD:
        Im = IMAGE_PIECE_GREEN;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_GREEN_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_GREEN_VERTICAL;
        break;
    case GROC:
        Im = IMAGE_PIECE_YELLOW;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_YELLOW_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_YELLOW_VERTICAL;
        break;
    case LILA:
        Im = IMAGE_PIECE_PURPLE;
        if (m_tipus == RATLLAT_HORIZONTAL)
            Im = IMAGE_PIECE_PURPLE_HORIZONTAL;
        if (m_tipus == RATLLAT_VERTICAL)
            Im = IMAGE_PIECE_PURPLE_VERTICAL;
        break;
    }
    return Im;
}