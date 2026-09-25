#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLocale>
#include "WorldPopulationModel.h"
#include "WorldPopulationController.h"
#include "InputDialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        m_model = new WorldPopulationModel(this);
        m_controller = new WorldPopulationController(m_model);

        // Подписка на сигнал активной модели
        connect(m_model, &WorldPopulationModel::modelChanged, this, &MainWindow::onModelChanged);

        auto *centralWidget = new QWidget(this);
        auto *layout = new QVBoxLayout(centralWidget);

        m_btnOpenInput = new QPushButton("Ввести данные", this);
        m_lblResultDate = new QLabel("Дата: не задана", this);
        m_lblResultPopulation = new QLabel("Расчетное население мира: -", this);

        layout->addWidget(m_btnOpenInput);
        layout->addWidget(m_lblResultDate);
        layout->addWidget(m_lblResultPopulation);

        setCentralWidget(centralWidget);
        resize(350, 150);

        connect(m_btnOpenInput, &QPushButton::clicked, this, &MainWindow::onOpenInputClicked);
    }

private slots:
    void onOpenInputClicked() {
        InputDialog dialog(m_lastDay, m_lastMonth, m_lastYear, this);
        if (dialog.exec() == QDialog::Accepted) {
            try {
                m_controller->processDateInput(
                    dialog.getDay(),
                    dialog.getMonth(),
                    dialog.getYear()
                );

                // Сохраняем последние введенные данные при успешном расчете
                m_lastDay = dialog.getDay();
                m_lastMonth = dialog.getMonth();
                m_lastYear = dialog.getYear();
            } 
            catch (const std::exception &e) {
                QMessageBox::critical(this, "Ошибка ввода", e.what());
            }
        }
    }

    // Слот-обработчик активной модели
    void onModelChanged(long long population, const QDate &date) {
        m_lblResultDate->setText(QString("Дата: %1").arg(date.toString("dd.MM.yyyy")));
        
        QLocale locale(QLocale::Russian);
        m_lblResultPopulation->setText(QString("Расчетное население мира: %1 чел.")
            .arg(locale.toString(population)));
    }

private:
    WorldPopulationModel *m_model;
    WorldPopulationController *m_controller;

    QPushButton *m_btnOpenInput;
    QLabel *m_lblResultDate;
    QLabel *m_lblResultPopulation;

    // Переменные для запоминания последних введенных данных
    QString m_lastDay;
    QString m_lastMonth;
    QString m_lastYear;
};

#endif // MAINWINDOW_H