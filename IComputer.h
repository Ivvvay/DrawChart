#ifndef ICOMPUTER_H
#define ICOMPUTER_H

#include <IProcessor.h>

class IComputer
{
public:
    virtual ~IComputer() = default;
    virtual void getComputerInfo() const = 0;
};

#endif // ICOMPUTER_H
