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
        if (!std::isdigit(line[i]) && line[i] != '.')
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
    groundhog.setPeriod(std::stoi(line));
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
        if (line.compare("STOP") == 0)
            break;
        if (line.compare("EOF") == 0 || !isNumber(line))
            return (84);
        groundhog.addInput(line);
        groundhog.displayData();
    }
    return (0);
}