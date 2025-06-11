#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include <iostream>
#include <string>
#include <memory>

enum ProcessorType
{
    x86,
    x64
};

class IProcessor
{
public:
    virtual ~IProcessor() = default;

    virtual std::string getProcessorVersion() const = 0;
    virtual ProcessorType getProcessorType() const = 0;
    virtual double getProcessorSpeed() const = 0;

    virtual void getProcessorInfo() const = 0;
};

#endif // IPROCESSOR_H
