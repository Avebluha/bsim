#ifndef BATTERYMODEL_H
#define BATTERYMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QPointF>
#include <QObject>

class BatteryModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    BatteryModel(QObject *parent = nullptr);

    QList<QPointF> getData() const;

    void setData(const QList<QPointF> &data);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


private:
    QList<QPointF> m_data;
};

#endif // BATTERYMODEL_H
