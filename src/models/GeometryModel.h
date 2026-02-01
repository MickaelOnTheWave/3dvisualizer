#ifndef GEOMETRYMODEL_H
#define GEOMETRYMODEL_H

#include <QObject>

#include "AbstractReferenceModel.h"
#include "scene/resources/Geometry.h"

class GeometryModel : public AbstractReferenceModel<Geometry>
{
   Q_OBJECT

public:
   explicit GeometryModel(QObject *parent = nullptr);

   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   QVariant GetDataAtColumn(Geometry* data, const int column) const override;
   QString GetHeaderAtColumn(const int column) const override;
   QHeaderView::ResizeMode GetSizingAtColumn(const int column) const override;

   QString GetGeometryTypeName(Geometry* data) const;
};
#endif // GEOMETRYMODEL_H
