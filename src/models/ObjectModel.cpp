#include "ObjectModel.h"

ObjectModel::ObjectModel(QObject *parent)
   : AbstractDataModel{parent}
{
}

int ObjectModel::columnCount(const QModelIndex& parent) const
{
   return 2;
}

QVariant ObjectModel::GetDataAtColumn(GlRenderObject* const& data, const int column) const
{
   switch (column)
   {
      case 0: return QString::fromUtf8(data->GetName());
      case 1: return QString::fromUtf8(data->GetMaterial()->GetName());
      default: return QVariant();
   }
}

QString ObjectModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Name");
      case 1: return QStringLiteral("Material");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode ObjectModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::Stretch;
   }
   return QHeaderView::ResizeToContents;
}
