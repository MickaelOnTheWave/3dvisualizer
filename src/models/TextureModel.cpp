#include "TextureModel.h"

TextureModel::TextureModel(QObject *parent)
   : AbstractDataModel{parent}
{
}

int TextureModel::columnCount(const QModelIndex& parent) const
{
   return 2;
}

QVariant TextureModel::GetDataAtColumn(const GlTexture& data, const int column) const
{
   switch (column)
   {
      case 0: return data.textureId;
      case 1: return QString::fromUtf8(data.GetName());
      default: return QVariant();
   }
}

QString TextureModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Id");
      case 1: return QStringLiteral("Name");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode TextureModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::ResizeToContents;
      case 1: return QHeaderView::Stretch;
   }
   return QHeaderView::ResizeToContents;
}
