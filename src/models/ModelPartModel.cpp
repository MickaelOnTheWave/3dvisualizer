#include "ModelPartModel.h"

ModelPartModel::ModelPartModel(QObject *parent)
   : AbstractReferenceModel(parent)
{
}

int ModelPartModel::columnCount(const QModelIndex& parent) const
{
   return 3;
}

QVariant ModelPartModel::GetDataAtColumn(Model* data, const int column) const
{
   switch (column)
   {
      case 0: return data->GetId();
      case 1: return QString::fromUtf8(data->GetName());
      case 2: return QString::number(data->parts.size());
      default: return QVariant();
   }
}

QString ModelPartModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Model Id");
      case 1: return QStringLiteral("Geometry Id");
      case 2: return QStringLiteral("Material Id");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode ModelPartModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::ResizeToContents;
      case 2: return QHeaderView::ResizeToContents;
   }
   return QHeaderView::ResizeToContents;
}
