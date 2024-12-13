

#include <iostream>
using namespace std;
class base
{
private: int data_encap = 0;
       void private_function()
       {
           cout << endl << "iam private function";
       }
public:
    base()
    {
        cout << endl<< "base class constructor";
    }
    base(int val)
    {
        data_encap = val;
        cout << endl << "parameterized base class constructor"<<val;
    }
    // encapsulation 
    void seter(int val)
    {
        data_encap = val;
    }

    int geter()
    {
        return data_encap;
    }

    void base_fun()
    {
        cout << endl<<"base function";
    }
    virtual void v_f()
    {
        cout << endl<<"virtual function";
    }
    virtual void pvf() = 0;
    virtual ~base() { cout << endl << "base destructor"; } // if there no virtual destructor then while deleting
    // the base class object the derived object will not delete even it is assigned.
    friend int friend_function(base& obj);
    
    friend class derived;
   

};
int friend_function  (base& obj)
{
    obj.private_function();
    return obj.data_encap;
}
class derived :public base
{
public:
    derived() 
    { 
        cout << endl << "derived class constructor";
    }
    derived(int val):base(val) // this will help to call derived and base clss parameterized constructor at a time
    {
        cout << endl<< "parameterized derived class constructor";
    }
    void v_f()
    {
        cout << endl<<"override non virtual function";
    }

    void pvf()
    {
        cout << endl << "pure virtual function";

    }
    ~derived()
    {
        cout <<endl<< "derived destructor";
    }

    void f_fun()
    {

        cout << endl << "iam from the friend class: " << data_encap;
        private_function();
    }
};

int main()
{
    base *obj= new derived(1); // in this case we can  call the parameterized constructor of base class
    cout << endl << "friend fucntion " << friend_function(*obj);
    derived d;
    d.f_fun();
  
    cout << endl << "encapsulated private data is achived using setter and getter";
    obj->seter(100);
    cout << endl << obj->geter();
    obj->base_fun();
    obj->v_f();
    obj->pvf();
    delete obj;
    return 0;
}

