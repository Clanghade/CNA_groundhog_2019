/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "../include/Groundhog.hpp"

void displayHelp(void)
{
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "    ./groundhog period" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "    period        the number of days defining a period" << std::endl;
    exit(0);
}

bool isNumber(std::string line)
{
    for (int i = 0; i < line.length(); i++) {
        if (!std::isdigit(line[i]) && line[i] != '.' && line[i] != '-')
            return (false);
    }
    return (true);
}

int main(int ac, char **av)
{
    if (ac == 1) return (84);
    Groundhog groundhog;
    std::string line = av[1];

    if (line.compare("-h") == 0)
        displayHelp();
    if (line.compare("0") == 0)
        return (84);
    groundhog.setPeriod(std::stoi(line));
    while (std::getline(std::cin, line))
    {
        if (line.compare("STOP") == 0)
            break;
        // std::cout << line << std::endl;
        if (line.compare("EOF") == 0 || !isNumber(line) || line.compare("") == 0)
            return (84);
        groundhog.addInput(line);
        groundhog.displayData();
    }
    if (!groundhog.enoughValues() || line.compare("STOP") != 0)
        return (84);
    groundhog.finalDisplay();
    return (0);
}