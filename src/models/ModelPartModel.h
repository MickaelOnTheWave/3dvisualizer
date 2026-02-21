#ifndef MODELPARTMODEL_H
#define MODELPARTMODEL_H

#include "AbstractReferenceModel.h"
#include "scene/resources/Model.h"

class ModelPartModel : public AbstractReferenceModel<Model>
{
   Q_OBJECT

public:
   explicit ModelPartModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(Model* data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // MODELPARTMODEL_H
