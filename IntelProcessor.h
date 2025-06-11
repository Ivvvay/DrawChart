#ifndef INTELPROCESSOR_H
#define INTELPROCESSOR_H

#include <IProcessor.h>

class IntelProcessor : public IProcessor
{
private:
    std::string _version;
    ProcessorType _type;
    double _speed;

public:
    IntelProcessor(std::string version, ProcessorType type, double speed) :
        _version(version), _type(type), _speed(speed) {}

    IntelProcessor() :
        IntelProcessor("i5-12400f", ProcessorType::x64, 2.5) {}

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

#endif // INTELPROCESSOR_H
