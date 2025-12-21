#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "GlTexture.h"

class TextureModel : public QAbstractTableModel
{
   Q_OBJECT

public:
   explicit TextureModel(QObject *parent = nullptr);

   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role) const override;
   QVariant headerData(int section, Qt::Orientation orientation,
                       int role) const override;

   void Reset(const std::vector<GlTexture> &_textureData);

private:
   std::vector<GlTexture> textureData;
};

#endif // TEXTUREMODEL_H
