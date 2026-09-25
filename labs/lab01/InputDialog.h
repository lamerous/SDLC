#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class InputDialog : public QDialog {
    Q_OBJECT

public:
    InputDialog(const QString &day = "", const QString &month = "", const QString &year = "", QWidget *parent = nullptr) 
        : QDialog(parent) 
    {
        setWindowTitle("Ввод даты");

        m_dayEdit = new QLineEdit(day, this);
        m_monthEdit = new QLineEdit(month, this);
        m_yearEdit = new QLineEdit(year, this);

        auto *layout = new QVBoxLayout(this);
        layout->addWidget(new QLabel("День:"));
        layout->addWidget(m_dayEdit);
        layout->addWidget(new QLabel("Месяц:"));
        layout->addWidget(m_monthEdit);
        layout->addWidget(new QLabel("Год:"));
        layout->addWidget(m_yearEdit);

        auto *btnSubmit = new QPushButton("Рассчитать", this);
        layout->addWidget(btnSubmit);

        connect(btnSubmit, &QPushButton::clicked, this, &QDialog::accept);
    }

    QString getDay() const { return m_dayEdit->text(); }
    QString getMonth() const { return m_monthEdit->text(); }
    QString getYear() const { return m_yearEdit->text(); }

private:
    QLineEdit *m_dayEdit;
    QLineEdit *m_monthEdit;
    QLineEdit *m_yearEdit;
};

#endif // INPUTDIALOG_H