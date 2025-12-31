#ifndef INSTANCEMODEL_H
#define INSTANCEMODEL_H

#include "AbstractDataModel.h"

#include "objects/GlRenderedInstance.h"

class InstanceModel : public AbstractDataModel<GlRenderedInstance*>
{
   Q_OBJECT

public:
   explicit InstanceModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(GlRenderedInstance* const& data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // INSTANCEMODEL_H
