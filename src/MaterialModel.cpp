#include "MaterialModel.h"

MaterialModel::MaterialModel(QObject *parent)
   : QAbstractTableModel{parent}
{}

int MaterialModel::rowCount(const QModelIndex& parent) const
{
   return rawData.size();
}

int MaterialModel::columnCount(const QModelIndex& parent) const
{
   return 4;
}

QVariant MaterialModel::data(const QModelIndex& index, int role) const
{
   if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

   const Material *material = rawData.at(index.row());

   switch (index.column())
   {
      case 0: return QString::fromUtf8(material->GetName());
      case 1: return QString::number(material->diffuseTextureId);
      case 2: return QString::number(material->specularTextureId);
      case 3: return QString::number(material->shininess);
      default: return QVariant();
   }
}

QVariant MaterialModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
      return QVariant();

   if (orientation == Qt::Horizontal)
   {
      switch (section)
      {
         case 0: return QStringLiteral("Name");
         case 1: return QStringLiteral("DiffuseTexture");
         case 2: return QStringLiteral("SpecularTexture");
         case 3: return QStringLiteral("Shininess");
      }
   }
   return section + 1;
}

void MaterialModel::Reset(const std::vector<Material*>& _data)
{
   beginResetModel();
   rawData = _data;
   endResetModel();
}
