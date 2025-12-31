#include "InstanceModel.h"

InstanceModel::InstanceModel(QObject *parent)
   : AbstractDataModel{parent}
{
}

int InstanceModel::columnCount(const QModelIndex& parent) const
{
   return 2;
}

QVariant InstanceModel::GetDataAtColumn(GlRenderedInstance* const& data, const int column) const
{
   switch (column)
   {
      case 0: return QString::fromUtf8(data->GetName());
      case 1: return QString::fromUtf8(data->GetRenderObject()->GetName());
      default: return QVariant();
   }
}

QString InstanceModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Name");
      case 1: return QStringLiteral("Object");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode InstanceModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::Stretch;
   }
   return QHeaderView::ResizeToContents;
}

