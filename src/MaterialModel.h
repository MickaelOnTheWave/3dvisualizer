#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "Material.h"

class MaterialModel : public QAbstractTableModel
{
public:
   explicit MaterialModel(QObject *parent = nullptr);

   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role) const override;
   QVariant headerData(int section, Qt::Orientation orientation,
                       int role) const override;

   void Reset(const std::vector<Material*> &_data);

private:
   std::vector<Material*> rawData;
};

#endif // MATERIALMODEL_H
