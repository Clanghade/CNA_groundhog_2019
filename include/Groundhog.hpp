/*
** EPITECH PROJECT, 2020
** Groundhog
** File description:
** Groundhog
*/

#ifndef GROUNDHOG_HPP_
#define GROUNDHOG_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <utility>

class Groundhog {
    public:
        Groundhog();
        ~Groundhog();

        void displayData(void);
        void computeIncrease(void) const;
        void computeRelative(void);
        void computeStandard(void);
        double computeAverage(void) const;
        void finalDisplay(void);
        void setPeriod(unsigned int newPeriod);
        void addInput(const std::string &newInput);

        unsigned int getPeriod(void) const;
        std::vector<double> getInputs(void) const;

    protected:
    private:
        double _previousValue;
        double _relativeNdays;
        unsigned int _period;
        std::vector<double> _values;
        std::vector<double> _increase;
        int _lastR;
        bool _isSwitch;
        int _switch;
        std::vector<std::pair<double, double>> _weird;
};

#endif /* !GROUNDHOG_HPP_ */