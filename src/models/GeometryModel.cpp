#include "GeometryModel.h"

#include "scene/resources/geometries/Box.h"
#include "scene/resources/geometries/Cylinder.h"
#include "scene/resources/geometries/Mesh.h"
#include "scene/resources/geometries/Plane.h"
#include "scene/resources/geometries/Sphere.h"

GeometryModel::GeometryModel(QObject *parent)
   : AbstractReferenceModel(parent)
{
}

int GeometryModel::columnCount(const QModelIndex& parent) const
{
   return 3;
}

QVariant GeometryModel::GetDataAtColumn(Geometry* data, const int column) const
{
   switch (column)
   {
      case 0: return data->GetId();
      case 1: return QString::fromUtf8(data->GetName());
      case 2: return GetGeometryTypeName(data);
      default: return QVariant();
   }
}

QString GeometryModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Id");
      case 1: return QStringLiteral("Name");
      case 2: return QStringLiteral("Type");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode GeometryModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::Stretch;
      case 2: return QHeaderView::ResizeToContents;
   }
   return QHeaderView::ResizeToContents;
}

QString GeometryModel::GetGeometryTypeName(Geometry* data) const
{
   if (dynamic_cast<Box*>(data))
   {
      return "Box";
   }
   else if (dynamic_cast<Cylinder*>(data))
   {
      return "Cylinder";
   }
   else if (dynamic_cast<Mesh*>(data))
   {
      return "Mesh";
   }
   else if (dynamic_cast<Plane*>(data))
   {
      return "Plane";
   }
   else if (dynamic_cast<Sphere*>(data))
   {
      return "Sphere";
   }
   else
   {
      return "Unknown";
   }
}
