#ifndef ABSTRACTVALUEMODEL_H
#define ABSTRACTVALUEMODEL_H

#include "AbstractDataModel.h"

template <class T>
class AbstractValueModel : public IDataModel
{
public:
   explicit AbstractValueModel(QObject *parent = nullptr);

   int rowCount(const QModelIndex &parent = QModelIndex()) const final;
   QVariant data(const QModelIndex &index, int role) const final;
   QVariant headerData(int section, Qt::Orientation orientation,
                       int role) const final;

   void Reset(const std::vector<T> &_data);

private:
   virtual QVariant GetDataAtColumn(const T& data, const int column) const = 0;
   virtual QString GetHeaderAtColumn(const int column) const = 0;

   std::vector<T> rawData;
};

template<class T>
inline AbstractValueModel<T>::AbstractValueModel(QObject* parent)
   : IDataModel(parent)
{
}

template<class T>
inline int AbstractValueModel<T>::rowCount(const QModelIndex& parent) const
{
   return rawData.size();
}

template<class T>
inline QVariant AbstractValueModel<T>::data(const QModelIndex& index, int role) const
{
   if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

   const T dataAtIndex = rawData.at(index.row());
   return GetDataAtColumn(dataAtIndex, index.column());
}

template<class T>
inline QVariant AbstractValueModel<T>::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
      return QVariant();

   if (orientation == Qt::Horizontal)
      return GetHeaderAtColumn(section);
   return section + 1;
}

template<class T>
inline void AbstractValueModel<T>::Reset(const std::vector<T>& _data)
{
   beginResetModel();
   rawData = _data;
   endResetModel();
}

#endif // ABSTRACTVALUEMODEL_H
