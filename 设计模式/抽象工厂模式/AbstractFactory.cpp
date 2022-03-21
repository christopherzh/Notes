#include<iostream>
#include<string>

class ProductA
{
public:
    virtual ~ProductA(){};
    virtual std::string UsefulFunctionA() const = 0;
};

class ConcreteProductA1:public ProductA{
public:
  std::string UsefulFunctionA() const override {
    return "The result of the product A1.";
  }
};

class ConcreteProductA2:public ProductA{
public:
  std::string UsefulFunctionA() const override {
    return "The result of the product A2.";
  }
};

class ProductB
{
public:
    virtual ~ProductB(){};
    virtual std::string UsefulFunctionB() const =0;
    virtual std::string AnotherUsefulFunctionB(const ProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public ProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B1.";
  }

  std::string AnotherUsefulFunctionB(const ProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B1 collaborating with ( " + result + " )";
  }
};

class ConcreteProductB2 : public ProductB {
 public:
  std::string UsefulFunctionB() const override {
    return "The result of the product B2.";
  }
  /**
   * The variant, Product B2, is only able to work correctly with the variant,
   * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
   * argument.
   */
  std::string AnotherUsefulFunctionB(const ProductA &collaborator) const override {
    const std::string result = collaborator.UsefulFunctionA();
    return "The result of the B2 collaborating with ( " + result + " )";
  }
};



class AbstractFactory
{
public:
    virtual ProductA* CreateProductA() const=0;
    virtual ProductB* CreateProductB() const=0;
};

class ConcreteFactory1:public AbstractFactory{
public:
    ProductA* CreateProductA()const override{
        return new ConcreteProductA1();
    };
    ProductB* CreateProductB()const override{
        return new ConcreteProductB1();
    };
};

class ConcreteFactory2:public AbstractFactory{
public:
    ProductA* CreateProductA()const override{
        return new ConcreteProductA2();
    };
    ProductB* CreateProductB()const override{
        return new ConcreteProductB2();
    };
};

void ClientCode(const AbstractFactory &factory) {
  const ProductA *product_a = factory.CreateProductA();
  const ProductB *product_b = factory.CreateProductB();
  std::cout << product_b->UsefulFunctionB() << "\n";
  std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
  delete product_a;
  delete product_b;
}

int main() {
  std::cout << "Client: Testing client code with the first factory type:\n";
  AbstractFactory *f1 = new ConcreteFactory1();
  ClientCode(*f1);
  delete f1;
  std::cout << std::endl;
  std::cout << "Client: Testing the same client code with the second factory type:\n";
  AbstractFactory *f2 = new ConcreteFactory2();
  ClientCode(*f2);
  delete f2;
  return 0;
}


