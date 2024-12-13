// copy_assignment_constructor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class a
{
    public:

    int val1 = 0, val2 = 0;
    //encapculating the val1 and val2 in to class to binding and hiding from the other classes.
    int* dp = new int(1);
public:
    a() // default constructor if we dont create it constrcutor will create by default 
    {
        cout << endl << "base class constructor";

    }
    a(int pc)
    {
        cout <<endl<< "parameterized base class constructor" << pc;
    }
    //a(a& obj)
    //{ // this acts as a shallow copy constructor as the new copy for the dynamic varibles are not created.
    //    cout << endl<<"default copy constructor"<<obj.val1;
    //}
    a(a& obj)
    {
        //dp = obj.dp; // this act as a shallow copy
        // as the new copy is not created the value will be changed tot he dynamic varible in the runtime.
        val1 = obj.val1;
        dp = new int;
        *dp = *(obj.dp);
        cout << endl << " copy constructor";
    }


    void dispalay()
    {
        cout <<endl <<"v1:"  << val1;
        cout << endl<<"dp"  << *dp;
    }



};

class b :public a
{
public:
    b()
    {
        cout << endl << "derived class constructor";

    }
    b(int pc)
    {
        cout << endl << "parameterized derived class constructor" << pc;
    }

};
int main()
{
    a *obj = new b(1);
    a obj2 = *obj; //calls the copy constructor is called
    a &obj3 = obj2; 
    // this act as a referance not the shallo copy not call the copy constructor
    a obj5;
    obj5 = obj2; 
    // assignment operator // will not call the copy constructor
    /* difference between assignment operator and copy:
    * in the asignment operator where we assign the other object to the existing object 
    * in copy we will create an object crete a copy of it .
    * 
    * 
    * 
    **/
    

    obj->dispalay();
    obj->val1 = 20;
    *(obj->dp) = 40;
    obj->dispalay(); 
    a obj4 = obj2; 
    obj4.dispalay();
    cout << endl << "address of obj2"<<&obj2;
    cout << endl << "address of copyed object obj4" << &obj4; 
    // this doesnot share the same object address ... 
    // but in the concept of the deep copy it will share same address related to the member varibles 

    cout << endl<<"varibles related to the obj2";
    cout << endl<<"address of val1"<<endl << &obj2.val1;
    cout << endl<<"address of dp" << endl << obj2.dp;
    cout << endl << "varibles related to the obj4";
    cout <<endl<< "address of val1" << endl << &obj4.val1;
    cout <<endl<< "address of dp" << endl << obj4.dp; 
    // if it is a shallow then the obj2 dp and obj4.dp will share same addresss ass it is shallow
    // if it is a deep then the obj2 dp and obj4.dp will share different addresss ass it is deep copy




    
}
