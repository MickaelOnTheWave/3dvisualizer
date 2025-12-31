#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include <QObject>

#include "AbstractDataModel.h"
#include "Material.h"

class MaterialModel : public AbstractDataModel<Material*>
{
   Q_OBJECT

public:
   explicit MaterialModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(Material* const& data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;

};

#endif // MATERIALMODEL_H
