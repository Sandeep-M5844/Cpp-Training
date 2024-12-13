#include <iostream>
#include <stdexcept>  // For runtime_error
using namespace std;

class x : public exception
{
public:
    const char* what() const noexcept override
    {
        return "insufficient";  // Custom exception message
    }
};

int main()
{
    try
    {
        int numerator = 10;
        int denominator = 0;
        int res;

        // Check if denominator is 0, then throw a runtime error or a custom exception.
        if (denominator == 0)

        {

             
                //creates a temporary object of type x(i.e., an instance of the x class).
                //The x class inherits from std::exception and overrides the what() method, 
                //so when the exception is caught, you can access that message through what().
          // throw runtime_error("division by zero is not possible");  // Throw runtime_error
            // Alternatively, you can throw your custom exception here like:
           
                throw x();  // if you want to use the custom 'x' exception.
        }

        // Calculate result if no exception occurs
        res = numerator / denominator;
        cout << "Result after division: " << res << endl;
    }
    // Catch block to catch the thrown exception
    //catch (const exception & e)  // Catch runtime_error specifically
    //{
    //    // Print the exception message
    //    cout << "Exception: " << e.what() << endl;  // Expected output: "Exception: division by zero is not possible"
    //}
    catch (const exception &e)  // If you decide to throw 'x' instead
    {
        cout << "Custom Exception: " << e.what() << endl;  // Custom exception message
    }

    return 0;
}
