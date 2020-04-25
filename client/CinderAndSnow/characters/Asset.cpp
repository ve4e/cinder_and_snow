#include "Asset.h"
#include <iostream>

#include <QDebug>


const QString WALK_PREFIX   = "/Walk/walk_";
const QString ATTACK_PREFIX = "/Attack/attack_";



Asset::Asset(const QString &prefix, CharacterView::Orientation orientation, CharacterView::Animation animation)
{
    prefix_ = prefix;
    orientation_ = orientation;
    animation_ = animation;

    if(animation_ == CharacterView::Animation::Idle) {
        QString res = prefix_ + WALK_PREFIX + QString::number((int) orientation_) + QString("00");
        sprites_.push_back(QPixmap(res));
    }
    else {
        QString fullPrefix = prefix_;

        if(animation_ == CharacterView::Animation::Walk){
            fullPrefix += WALK_PREFIX;
        }
        else if(animation_ == CharacterView::Animation::Attack){
            fullPrefix += ATTACK_PREFIX;
        }

        int i = 0;
        while(1) {
            QString res = fullPrefix + QString::number((int) orientation_) + QString("%1").arg(i, 2, 10, QLatin1Char('0'));
            ++i;

            QPixmap sprite(res);
            if(sprite.isNull()) {
                break;
            }

            sprites_.push_back(sprite);
        }
    }
}

QPixmap Asset::nextPixmap()
{
    if(ind_ >= sprites_.size() - 1) {
        ind_ = 0;
    }
    else {
        ++ind_;
    }
    return sprites_[ind_];
}

shared_ptr<Asset> Asset::getAsset(const QString& prefix, CharacterView::Orientation orientation, CharacterView::Animation animation)
{
    static map<QString, UnitAssets> allAssets;

    if(!allAssets.count(prefix))
    {
        UnitAssets assets = vector<vector<shared_ptr<Asset> > >(6, vector<shared_ptr<Asset> >(3) );

        using UView = CharacterView;

        assets[(int) UView::Orientation::RightTop][(int) UView::Animation::Idle] =    shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightTop, UView::Animation::Idle));
        assets[(int) UView::Orientation::RightTop][(int) UView::Animation::Attack] =  shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightTop, UView::Animation::Attack));
        assets[(int) UView::Orientation::RightTop][(int) UView::Animation::Walk] =    shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightTop, UView::Animation::Walk));

        assets[(int) UView::Orientation::RightDown][(int) UView::Animation::Idle] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightDown, UView::Animation::Idle));
        assets[(int) UView::Orientation::RightDown][(int) UView::Animation::Attack] = shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightDown, UView::Animation::Attack));
        assets[(int) UView::Orientation::RightDown][(int) UView::Animation::Walk] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::RightDown, UView::Animation::Walk));

        assets[(int) UView::Orientation::Down][(int) UView::Animation::Idle] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Down, UView::Animation::Idle));
        assets[(int) UView::Orientation::Down][(int) UView::Animation::Attack] = shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Down, UView::Animation::Attack));
        assets[(int) UView::Orientation::Down][(int) UView::Animation::Walk] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Down, UView::Animation::Walk));

        assets[(int) UView::Orientation::LeftDown][(int) UView::Animation::Idle] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftDown, UView::Animation::Idle));
        assets[(int) UView::Orientation::LeftDown][(int) UView::Animation::Attack] = shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftDown, UView::Animation::Attack));
        assets[(int) UView::Orientation::LeftDown][(int) UView::Animation::Walk] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftDown, UView::Animation::Walk));

        assets[(int) UView::Orientation::LeftTop][(int) UView::Animation::Idle] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftTop, UView::Animation::Idle));
        assets[(int) UView::Orientation::LeftTop][(int) UView::Animation::Attack] = shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftTop, UView::Animation::Attack));
        assets[(int) UView::Orientation::LeftTop][(int) UView::Animation::Walk] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::LeftTop, UView::Animation::Walk));

        assets[(int) UView::Orientation::Top][(int) UView::Animation::Idle] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Top, UView::Animation::Idle));
        assets[(int) UView::Orientation::Top][(int) UView::Animation::Attack] = shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Top, UView::Animation::Attack));
        assets[(int) UView::Orientation::Top][(int) UView::Animation::Walk] =   shared_ptr<Asset>(new Asset(prefix, UView::Orientation::Top, UView::Animation::Walk));

        allAssets[prefix] = assets;
    }

    return allAssets[prefix][(int)orientation][(int)animation];
}





