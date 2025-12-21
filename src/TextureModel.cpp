#include "TextureModel.h"

TextureModel::TextureModel(QObject *parent)
   : QAbstractTableModel{parent}
{}

int TextureModel::rowCount(const QModelIndex& parent) const
{
   return textureData.size();
}

int TextureModel::columnCount(const QModelIndex& parent) const
{
   return 2;
}

QVariant TextureModel::data(const QModelIndex& index, int role) const
{
   if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

   const GlTexture &texture = textureData.at(index.row());

   switch (index.column())
   {
      case 0: return texture.textureId;
      case 1: return QString::fromUtf8(texture.GetName());
      default: return QVariant();
   }
}

QVariant TextureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
      return QVariant();

   if (orientation == Qt::Horizontal)
   {
      switch (section)
      {
         case 0: return QStringLiteral("Id");
         case 1: return QStringLiteral("Name");
      }
   }
   return section + 1;
}

void TextureModel::Reset(const std::vector<GlTexture>& _textureData)
{
   beginResetModel();
   textureData = _textureData;
   endResetModel();
}
