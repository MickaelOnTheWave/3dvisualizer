#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "AbstractDataModel.h"

#include "objects/GlRenderObject.h"

class ObjectModel : public AbstractDataModel<GlRenderObject*>
{
   Q_OBJECT

public:
   explicit ObjectModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(GlRenderObject* const& data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;
};

#endif // OBJECTMODEL_H
