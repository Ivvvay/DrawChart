#include <QApplication>

#include <IOCContainer.h>
#include <IProcessor.h>
#include <IntelProcessor.h>
#include <AMDProcessor.h>
#include <Computer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IOCContainer conteiner;

    conteiner.registerInstance<IProcessor, AMDProcessor>();
    auto processorInstance = conteiner.getObject<IProcessor>();
    processorInstance->getProcessorInfo();


    std::cout<< "\n";
    conteiner.registerFactory<IComputer, Computer, IProcessor>();
    conteiner.getObject<IComputer>()->getComputerInfo();

    return a.exec();
}
