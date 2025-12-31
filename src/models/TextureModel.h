#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include <QObject>

#include "AbstractDataModel.h"
#include "GlTexture.h"

class TextureModel : public AbstractDataModel<GlTexture>
{
   Q_OBJECT

public:
   explicit TextureModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(const GlTexture& data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // TEXTUREMODEL_H
