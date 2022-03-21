#include<iostream>
#include<string>

class Product{
    public:
        virtual std::string DoStuff() const=0;
        virtual ~Product(){};
};
class ConcreteProductA:public Product{
    public:
        std::string DoStuff() const override{
            return "{Result of the ConcreteProductA}";
        };
};
class ConcreteProductB:public Product{
    public:
        std::string DoStuff() const override{
            return "{Result of the ConcreteProductB}";
        };
};


class Creator{
    public:
        std::string SomeOperation() const{
            Product* product=CreateProduct();
            std::string result = "Creator: The same creator's code has just worked with " + product->DoStuff();
            delete product;
            return result;
        };
        virtual ~Creator(){};
        virtual Product* CreateProduct()const=0;
};
class ConcreteCreatorA:public Creator{
    public:
        Product* CreateProduct() const override{
            return new ConcreteProductA; 
        };
};
class ConcreteCreatorB:public Creator{
    public:
        Product* CreateProduct() const override{
            return new ConcreteProductB(); 
        };
};

//客户端并不需要了解creator里的具体是哪个产品，只需要使用需要的操作即可，虚函数的重写会实现多态，从而动态确定需要的操作
void ClientCode(const Creator& creator) {
  // ...
  std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.SomeOperation() << std::endl;
  // ...
}


int main() {
  //需要根据需要的产品来调用不同的构造函数
  std::cout << "App: Launched with the ConcreteCreatorA.\n";
  Creator* creator = new ConcreteCreatorA();
  ClientCode(*creator);
  std::cout << std::endl;
  std::cout << "App: Launched with the ConcreteCreatorB.\n";
  Creator* creator2 = new ConcreteCreatorB();
  ClientCode(*creator2);

  delete creator;
  delete creator2;
  return 0;
}