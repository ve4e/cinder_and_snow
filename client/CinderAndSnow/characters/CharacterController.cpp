#include "Area.h"
#include "CharacterController.h"

void CharacterController::setView(shared_ptr<CharacterView> view)
{
    view_ = view;
    view_->setCurrentPixel(Area::hexToPixels(model_->position()));
}

void CharacterController::tick()
{
    if(movement_){
        makeStep();
    }

    view_->tick();
}

void CharacterController::processTarget(int x, int y)
{
    // TODO: обработка условия движения (м.б.  установлен запрет и т.д.)
    if(movement_ == true){
        return;
    }

    way_ = Gm_->trace(model_->position().first, model_->position().second, x, y);

    if(!way_.empty()){
        movement_ = true;
    }

    wayIndex_ = 0;
}

void CharacterController::makeStep()
{
    auto orientation = [](const pair<int, int>& currentPixel, const pair<int, int>& targetPixel)->CharacterView::Orientation {
        CharacterView::Orientation orientation;

        if(currentPixel.first == targetPixel.first) {
            orientation = currentPixel.second < targetPixel.second ? CharacterView::Orientation::Down : CharacterView::Orientation::Top;
        }
        else if(currentPixel.first < targetPixel.first) {
            orientation = currentPixel.second < targetPixel.second ? CharacterView::Orientation::RightDown : CharacterView::Orientation::RightTop;
        }
        else {
            orientation = currentPixel.second < targetPixel.second ? CharacterView::Orientation::LeftDown : CharacterView::Orientation::LeftTop;
        }

        return orientation;
    };


    if(view_->stepCount() == 0) {
        auto hex = way_[wayIndex_];
        auto targetPixel = Area::hexToPixels(hex);
        auto currentPixel = Area::hexToPixels(model_->position());

        view_->setTargetPixel(targetPixel);
        view_->setAnimation(CharacterView::Animation::Walk);
        view_->setOrientation(orientation(currentPixel, targetPixel));
    }
    else if(view_->stepCount() == view_->pathLength() / 2) {
        if(Gm_->isFreeCell(way_[wayIndex_])) {
            Gm_->moveHero(model_->position(), way_[wayIndex_]);
        }
    }
    else if(view_->stepCount() == view_->pathLength()) {
        if(wayIndex_ == way_.size() - 1) {
            movement_ = false;
            way_.clear();

            const auto& currentPixel = Area::hexToPixels(model_->position());
            view_->setCurrentPixel(currentPixel);
            view_->setTargetPixel(currentPixel);
            view_->setAnimation(CharacterView::Animation::Idle);
            view_->setOrientation(CharacterView::Orientation::Down);
            return;
        }
        else {
            ++wayIndex_;
            const auto& currentPixel = Area::hexToPixels(model_->position());
            const auto& targetPixel = Area::hexToPixels(way_[wayIndex_]);
            view_->setTargetPixel(targetPixel);
            view_->setOrientation(orientation(currentPixel, targetPixel));
        }
    }

    view_->takeStep();
}












