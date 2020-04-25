#ifndef ASSET_H
#define ASSET_H

#include "characters/CharacterView.h"
#include <memory>
#include <vector>
#include <map>
#include <QString>

using namespace std;

class Asset
{
public:
    static shared_ptr<Asset> getAsset(const QString &prefix, CharacterView::Orientation orientation, CharacterView::Animation animation);
    QPixmap nextPixmap();

private:
    Asset(const QString &prefix, CharacterView::Orientation orientation, CharacterView::Animation animation);

    QString prefix_;
    CharacterView::Orientation orientation_;
    CharacterView::Animation animation_;

    int ind_ = 0;
    vector<QPixmap> sprites_;

    using UnitAssets = vector<vector<shared_ptr<Asset> > >;
};


#endif // ASSET_H
