#ifndef AMDPROCESSOR_H
#define AMDPROCESSOR_H

#include <IProcessor.h>

class AMDProcessor : public IProcessor
{
private:
    std::string _version;
    ProcessorType _type;
    double _speed;

public:
    AMDProcessor(std::string version, ProcessorType type, double speed) :
        _version(version), _type(type), _speed(speed) {}

    AMDProcessor() :
        AMDProcessor("Ryzen 9 7950X", ProcessorType::x86, 4.5) {}

    std::string getProcessorVersion() const override {
        return _version;
    }

    ProcessorType getProcessorType() const override {
        return _type;
    }

    double getProcessorSpeed() const override {
        return _speed;
    }

    void getProcessorInfo() const override {
        std::cout << "Processor for " + getProcessorVersion() + " "
            + std::to_string(getProcessorSpeed()) + " GHz "
            + std::string((getProcessorType() == x86) ? "x86" : "x64") << std::endl;
    }
};

#endif // AMDPROCESSOR_H
