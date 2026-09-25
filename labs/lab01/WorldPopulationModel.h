#ifndef WORLDPOPULATIONMODEL_H
#define WORLDPOPULATIONMODEL_H

#include <QObject>
#include <QDate>
#include <stdexcept>

class WorldPopulationModel : public QObject {
    Q_OBJECT

public:
    explicit WorldPopulationModel(QObject *parent = nullptr) : QObject(parent), m_population(0) {}

    void calculatePopulation(int day, int month, int year) {
        QDate date(year, month, day);
        if (!date.isValid()) {
            throw std::invalid_argument("Введена некорректная дата.");
        }

        m_selectedDate = date;

        QDate baseDate(2023, 1, 1);
        double yearsDiff = baseDate.daysTo(m_selectedDate) / 365.25;

        long long basePopulation = 8000000000LL;
        long long growthRatePerYear = 70000000LL;

        m_population = basePopulation + static_cast<long long>(yearsDiff * growthRatePerYear);
        if (m_population < 0) m_population = 0;

        // Активная модель: уведомляем всех подписчиков (View) об изменении состояния
        emit modelChanged(m_population, m_selectedDate);
    }

signals:
    void modelChanged(long long population, const QDate &date);

private:
    QDate m_selectedDate;
    long long m_population;
};

#endif // WORLDPOPULATIONMODEL_H