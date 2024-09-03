#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QDoubleSpinBox>
#include <QObject>
#include <QStyledItemDelegate>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DoubleSpinBoxDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        Q_UNUSED(option);
        Q_UNUSED(index);
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setDecimals(4);  // Установка количества знаков после запятой
        editor->setMinimum(-1000000);  // Минимальное значение
        editor->setMaximum(1000000);  // Максимальное значение
        return editor;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        Q_UNUSED(index);
        editor->setGeometry(option.rect);
    }

signals:
};

#endif // DOUBLESPINBOXDELEGATE_H
