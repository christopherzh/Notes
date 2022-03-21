#include <iostream>
#include <string>
#include<algorithm>

class Target // 客户端直接调用的接口
{
private:
public:
    virtual ~Target() = default;
    virtual std::string Request() const
    {
        return "Target: The default target's behavior.";
    };
};

class Adaptee // 服务代码，有不兼容的情况
{
public:
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

class Adapter:public Target // 用于适配特殊服务adaptee的适配器
{
private:
    Adaptee *adaptee_;
public:
    Adapter(Adaptee* adaptee):adaptee_(adaptee){};
    std::string Request() const override{
        std::string to_reverse=adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(),to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    };
};

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target *target)
{
    std::cout << target->Request();
}

int main()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";

    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";

    
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}