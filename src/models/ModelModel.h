#ifndef MODELMODEL_H
#define MODELMODEL_H

#include <QObject>

#include "AbstractReferenceModel.h"
#include "scene/resources/Model.h"

class ModelModel : public AbstractReferenceModel<Model>
{
   Q_OBJECT

public:
   explicit ModelModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(Model* data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // MODELMODEL_H
