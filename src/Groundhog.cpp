/*
** EPITECH PROJECT, 2020
** Groundhog
** File description:
** Groundhog
*/

#include "../include/Groundhog.hpp"
#include <cmath>
#include <iomanip>
#include <algorithm>

Groundhog::Groundhog()
{
    _previousValue = 0;
    _relativeNdays = 0;
    _period = 0;
    _lastR = 9999;
    _switch = 0;
    _isSwitch = false;
}

bool sorting(std::pair<double, double>f, std::pair<double, double>s)
{
    return (f.first > s.first);
}

Groundhog::~Groundhog()
{
}

void Groundhog::finalDisplay(void)
{
    if (_switch != 0)
        std::cout << "Global tendency switched "<< _switch << " times" << std::endl;
    if (_weird.size() != 0) {
        std::cout << _weird.size() << " weirdest values are [";
        std::sort(_weird.begin(), _weird.end(), sorting);
        std::cout << std::setprecision(1);
        if (_weird.size() != 0) {
            for (size_t i = 0; i < _weird.size() - 1; i++)
                std::cout << _weird[i].second << ", ";
            std::cout << _weird[_weird.size() - 1].second;
        }
        std::cout << "]" << std::endl;
    }
}

bool Groundhog::enoughValues(void)
{
    if (_period != _values.size())
        return (false);
    return (true);
}

void Groundhog::setPeriod(unsigned int newPeriod)
{
    _period = newPeriod;
}

void Groundhog::addInput(const std::string &newInput)
{
    double nInput = std::stod(newInput);
    size_t size = _values.size();

    if (_values.size() == 0)
        _relativeNdays = nInput;
    if (_values.size() == _period)
        _values.erase(_values.begin());
    _values.push_back(nInput);
    if (size == 0)
    {
        _previousValue = nInput;
        return;
    }
    if (_increase.size() == _period)
        _increase.erase(_increase.begin());
    _increase.push_back(nInput - _previousValue);
    _previousValue = nInput;
}

unsigned int Groundhog::getPeriod(void) const
{
    return (_period);
}

std::vector<double> Groundhog::getInputs(void) const
{
    return (_values);
}

void Groundhog::displayData(void)
{
    std::cout << "g=";
    computeIncrease();
    std::cout << "       r=";
    computeRelative();
    std::cout << "%       s=";
    computeStandard();
    if (_isSwitch == true) {
        std::cout << "       a switch occurs";
        _isSwitch = false;
        _switch += 1;
    }
    std::cout << std::endl;
}

void Groundhog::computeIncrease(void) const
{
    double inc = 0;

    if (_increase.size() != _period) {
        std::cout << "nan";
        return;
    }
    for (size_t i = 0; i < _increase.size(); i++) {
        inc += (_increase[i] > 0 ? _increase[i] : 0);
    }
    inc /= _increase.size();
    if (inc < 0)
        inc = 0.00;
    std::cout << std::fixed << std::setprecision(2) << inc;
}

void Groundhog::computeRelative(void)
{
    double res = 0;
    int r = 0;

    if (_increase.size() != _period) {
        std::cout << "nan";
        return;
    }
    res = (_values[_values.size() - 1] * 100) / _relativeNdays;
    r = res;
    if ((res - r) > 0.5)
        r += 1;
    else if ((res - r) < -0.5)
        r -= 1;
    r -= 100;
    if (_values[_values.size() - 1] > _relativeNdays)
        r = abs(r);
    std::cout << r;
    if (_lastR == 9999)
        _lastR = r;
    else if ((r < 0 && _lastR >= 0) || (r >= 0 && _lastR < 0))
        _isSwitch = true;
    _lastR = r;
    _relativeNdays = _values[0];
}

double Groundhog::computeAverage(void) const
{
    double t = 0;

    for (size_t i = 0; i < _values.size(); i++)
        t += _values[i];
    return (t / _values.size());
}

void Groundhog::bollinger(double s)
{
    double currentValue = _values[_values.size() - 1];
    double bollingerA = computeAverage() + 1.88 * s;
    double bollingerB = computeAverage() - 1.88 * s;
    if (bollingerB < bollingerA)
    {
        if (currentValue < bollingerB)
            _weird.push_back(std::make_pair(abs(bollingerB - currentValue), currentValue));
        else if (currentValue > bollingerA)
            _weird.push_back(std::make_pair(abs(currentValue - bollingerA), currentValue));
    } else
    {
        if (currentValue > bollingerB)
            _weird.push_back(std::make_pair(abs(currentValue - bollingerB), currentValue));
        else if (currentValue < bollingerA)
            _weird.push_back(std::make_pair(abs(bollingerA - currentValue), currentValue));
    }
}

void Groundhog::computeStandard(void)
{
    if (_values.size() < _period)
    {
        std::cout << "nan";
        return;
    }
    double variance = 0;
    for (size_t i = 0; i < _values.size(); i++)
        variance += std::pow(_values[i] - computeAverage(), 2);
    double s = std::sqrt(variance / _values.size());
    std::cout << std::fixed << std::setprecision(2) << s;
    bollinger(s);
}