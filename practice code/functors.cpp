
//Functors are the class or the struct which act like a function when the isnstance get created
//which is achived using the operator() function .


#include<iostream>
#include<vector>
#include <algorithm>  

using namespace std;
class functors_ex
{
public:
    int factor;
public:
    functors_ex(int fact)
    {
        factor = fact;
    }
    int operator()(int &x) // & to modify the data
    {
        // cout<<"operator callesx";
       // return x * factor;
        return x *= factor;  // if we use the for_each to store dyanamically we should this 
    }
};
int main()
{
    vector<int>v = { 1,2,3,4 };
    functors_ex obj10(10);
    for_each(v.begin(), v.end(), obj10); // this will make the data store in the vector automatically 
    for (auto i : v)
    {
        cout << i;
    }
    // for(auto x:v)
    // {
            // if we do this then we have to asssign it manually like bewlow


    //     functors_ex obj10(10); // this will create a functor which will
    //     cout<<endl<<obj10(x);
             ///for(auto i:v)
            //{
               // i.pushback(obj10(x))
            //}
    // }

}
