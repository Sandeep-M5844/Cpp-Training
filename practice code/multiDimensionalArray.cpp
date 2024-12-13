
#include<iostream>
#include <vector>
using namespace std;

int main()
{
    // 1 D array
    cout << endl << "1 Dimmensional array" << endl;
    int row_1 = 3;

    int* arr_1 = new int[row_1];

    for (int i = 0; i < row_1; i++)
    {
        arr_1[i] = i;
        cout << arr_1[i] << " ";
    }

    delete[] arr_1;

    // 2D array 

    cout << endl << "2 Dimmensional array" << endl;

    int** arr = new int*[10];// arr stores the address of a varible in this case it is columnn

    int row = 3;
    int col = 3;
    for (int i = 0; i < row; i++)
    {
        arr[i] = new int[col]; // wea are storing the colunm addressin to each row which result in the 2D array
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = i * col + j;
            cout << arr[i][j]<<" ";
        }
        cout << endl;
    }

    for (int i = 0; i < row; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    // 3d array 

    cout << endl << "3d array delecration"<<endl;

    int row_3 = 3;
    int col_3 = 3;
    int dept_3 = 3;

    int*** arr_3 = new int**[dept_3]; // creating a pointer to 2 pointer which point to the address of a pointer
    //which store the address of col and this pointer points to rows
    // ***arr_3::depth->**arr_3::rows->*arr_3::colomun

    for (int i = 0; i < dept_3; i++)
    {
        arr_3[i] = new int*[row]; // this will store the each depth with the no of row 
        for (int j = 0; j < row_3; j++)
        {
            arr_3[i][j] = new int[col]; // each depth in the eaach row stroes the each column
        }
    }

    for (int i = 0; i < dept_3; i++)
    {
        for (int j = 0; j < row_3; j++)
        {
            for (int k = 0; k < col_3; k++)
            {
                arr_3[i][j][k] = i * row_3 * col_3 + j * col_3 + k; //just oder indexing of each column
                cout << arr_3[i][j][k] << " ";
            }
            cout << endl;
        }
    }

    // deletion

    for (int i = 0; i < dept_3; i++)
    {
        for (int j = 0; j < row_3; j++)
        {
            delete[] arr_3[i][j]; // intilallly deletiong the each column in the each row
        }
        delete[] arr_3[i]; // deleting the each row in the depth
        
    }
    delete[] arr_3; // deeting the depth


    // 2 D array using the vector --> 2D vector

    cout << "2 D array using the vector-- > 2D vector" << endl;

    int row_2v = 3;
    int col_2v = 3;


    vector<vector<int>> vec(row, vector<int>(col));

    /* using iteration
    for(auto rowit = vec.begin();rowit!=end;rowit++)
    * {
    *      for(auto colit = rowit->begin();colit!=rowit->end();colit++)
    * { 
    *   cout<<*colit;
    * }
    * }
    * 
    * // or 
    * 
    * for(auto &rowit:vec)
    * {
    *   for(auto ele:rowit)
    * {
    *   cout<<ele;
    * }
    * cout<<endl;
    * }
    */

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            vec[i][j] = i * col + j;

            cout << vec[i][j]<<" ";
        }
        cout<<endl;
    }

    // 3 D array using the vector --> 2D vector

    cout << "3 D array using the vector-- > 3D vector" << endl;

    int row_3v = 3;
    int col_3v = 3;
    int dept_3v = 3;

    vector<vector<vector<int>>> vec_3(dept_3v, vector<vector<int>>(row_3v, vector<int>(col_3v)));

    for (int i = 0; i < dept_3v; i++)
    {
        for (int j = 0; j < row_3v; j++)
        {
            for (int k = 0; k < col_3v; k++)
            {
                vec_3[i][j][k] = i * row_3v * col_3v + j * col_3v + k;;

                cout << vec_3[i][j][k] << " ";
            }
            cout << endl;
        }
     
    }

    return 0;
}




