#include "HexController.h"

#include <QDebug>

HexController::HexController()
{

}

void HexController::handleMousePress()
{
    Gm_->handleClick(hex_->x(), hex_->y());
}

void HexController::setHighlight(bool s)
{
    hexView_->setHighlight(s);
}




