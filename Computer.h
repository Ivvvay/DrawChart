#ifndef COMPUTER_H
#define COMPUTER_H

#include <IComputer.h>

class Computer : public IComputer
{
private:
    std::shared_ptr<IProcessor> _processor;
public:
    Computer(std::shared_ptr<IProcessor> processor) :
        _processor(processor) {}

    void getComputerInfo() const override {
        std::cout << "Computer has ";
        _processor->getProcessorInfo();
    }
};

#endif // COMPUTER_H
