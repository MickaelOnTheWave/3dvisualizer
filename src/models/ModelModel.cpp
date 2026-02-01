#include "ModelModel.h"

ModelModel::ModelModel(QObject *parent)
   : AbstractReferenceModel(parent)
{
}

int ModelModel::columnCount(const QModelIndex& parent) const
{
   return 3;
}

QVariant ModelModel::GetDataAtColumn(Model* data, const int column) const
{
   switch (column)
   {
      case 0: return data->GetId();
      case 1: return QString::fromUtf8(data->GetName());
      case 2: return QString::number(data->parts.size());
      default: return QVariant();
   }
}

QString ModelModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Id");
      case 1: return QStringLiteral("Name");
      case 2: return QStringLiteral("Parts Count");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode ModelModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::Stretch;
      case 2: return QHeaderView::ResizeToContents;
   }
   return QHeaderView::ResizeToContents;
}
