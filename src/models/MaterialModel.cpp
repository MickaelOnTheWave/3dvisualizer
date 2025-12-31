#include "MaterialModel.h"

MaterialModel::MaterialModel(QObject *parent)
   : AbstractDataModel{parent}
{}

int MaterialModel::columnCount(const QModelIndex& parent) const
{
   return 4;
}

QVariant MaterialModel::GetDataAtColumn(Material* const& data, const int column) const
{
   switch (column)
   {
      case 0: return QString::fromUtf8(data->GetName());
      case 1: return QString::number(data->diffuseTextureId);
      case 2: return QString::number(data->specularTextureId);
      case 3: return QString::number(data->shininess);
      default: return QVariant();
   }
}

QString MaterialModel::GetHeaderAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QStringLiteral("Name");
      case 1: return QStringLiteral("Diffuse Id");
      case 2: return QStringLiteral("Specular Id");
      case 3: return QStringLiteral("Shininess");
   }
   return QStringLiteral("");
}

QHeaderView::ResizeMode MaterialModel::GetSizingAtColumn(const int column) const
{
   switch (column)
   {
      case 0: return QHeaderView::Stretch;
   }
   return QHeaderView::ResizeToContents;
}
