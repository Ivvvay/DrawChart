#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H

#include <functional>
#include <iostream>
#include <memory>
#include <map>
#include <string>
using namespace std;

class IOCContainer
{
    static int s_nextTypeId;
    template<typename T>
    static int getTypeID() {
        static int typeId = s_nextTypeId++;
        return typeId;
    }

public:
    //Создание typeid для типа
    /*
     * В предлагаемой реализации контейнера IOC  есть статическая целочисленная переменная,
     * указывающая идентификатор следующего типа, который будет выделен,
     * и экземпляр статической локальной переменной для каждого типа,
     * доступ к которому можно получить, вызвав метод GetTypeID.
    */

    /*
     * Получение экземпляров объекта
     * Теперь, когда у нас есть идентификатор типа,
     * мы должны иметь возможность хранить какой-то фабричный объект,
     * чтобы представить тот факт, что мы не знаем, как создать этот объект.
     * Поскольку я хочу хранить все фабрики в одной коллекции,
     * я выбираю абстрактный базовый класс, от которого будут производными фабрики,
     * и реализацию, которая фиксирует функтор для последующего вызова.
     * Для краткости я использовал std::map для хранения фабрик, однако
     * вы можете рассмотреть и другие варианты для повышения эффективности.
     */

    class FactoryRoot
    {
    public:
        virtual ~FactoryRoot() {}
    };

    std::map<int, std::shared_ptr<FactoryRoot>> m_factories;


    //Получить экземпляр объекта
    template<typename T>
    class CFactory : public FactoryRoot
    {
        std::function<std::shared_ptr<T>()> m_functor;

    public:
        ~CFactory() {}

        CFactory(std::function<std::shared_ptr<T>()> functor)
            : m_functor(functor) {}

        std::shared_ptr<T> getObject() {
            return m_functor();
        }
    };

    //Вся конструкция нужна для того, чтобы по типу T найти соответствующую фабрику, привести её к правильному типу и получить новый объект этого типа.
    template<typename T>
    std::shared_ptr<T> getObject() {
        auto typeId = getTypeID<T>();
        auto factoryBase = m_factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase); //Приведение умного указателя на базовый класс (FactoryRoot) к указателю на нужный шаблонный класс-фабрику (CFactory<T>).
        return factory->getObject();
    }

    //Регистрация экземпляров

    //Самая простая реализация - зарегистрировать функтор
    template<typename TInterface, typename... TS>
    void registerFunctor(
        std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)> functor) {
        m_factories[getTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
            [ = ] { return functor(getObject<TS>()...); });
    }

    //Регистрация одного экземпляра объекта
    template<typename TInterface>
    void registerInstance(std::shared_ptr<TInterface> t) {
        m_factories[getTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
            [ = ] { return t; });
    }

    //Подаем указатель на функцию
    template<typename TInterface, typename... TS>
    void registerFunctor(std::shared_ptr<TInterface> (*functor)(std::shared_ptr<TS>... ts)) {
        registerFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)>(functor));
    }

    //Фабрика, которая будет вызывать конструктор, для каждого экземпляра
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void registerFactory() {
        registerFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments>... ts)>(
                [](std::shared_ptr<TArguments>... arguments) -> std::shared_ptr<TInterface> {
                    return std::make_shared<TConcrete>(
                        std::forward<std::shared_ptr<TArguments>>(arguments)...);
                }));
    }

    //Фабрика, которая будет возвращать один экземпляр
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void registerInstance() {
        registerInstance<TInterface>(std::make_shared<TConcrete>(getObject<TArguments>()...));
    }
};

// инициализируем ненулевым числом
int IOCContainer::s_nextTypeId = 115094801;


#endif // IOCCONTAINER_H
