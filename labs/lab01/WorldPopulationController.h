#ifndef WORLDPOPULATIONCONTROLLER_H
#define WORLDPOPULATIONCONTROLLER_H

#include "WorldPopulationModel.h"
#include <QString>
#include <stdexcept>

class WorldPopulationController {
public:
    explicit WorldPopulationController(WorldPopulationModel *model) : m_model(model) {}

    void processDateInput(const QString &dayStr, const QString &monthStr, const QString &yearStr) {
        bool okDay, okMonth, okYear;
        int day = dayStr.toInt(&okDay);
        int month = monthStr.toInt(&okMonth);
        int year = yearStr.toInt(&okYear);

        if (!okDay || !okMonth || !okYear) {
            throw std::invalid_argument("Все поля даты должны быть целыми числами.");
        }

        if (year < 1910 || year > 2100) {
            throw std::invalid_argument("Год должен быть в диапазоне от 1910 до 2100.");
        }

        m_model->calculatePopulation(day, month, year);
    }

private:
    WorldPopulationModel *m_model;
};

#endif // WORLDPOPULATIONCONTROLLER_H