#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include <QObject>

#include "AbstractDataModel.h"
#include "scene/resources/Texture.h"

class TextureModel : public AbstractDataModel<Texture>
{
   Q_OBJECT

public:
   explicit TextureModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(const Texture& data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // TEXTUREMODEL_H
