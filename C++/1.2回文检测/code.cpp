#include <iostream>
#include <algorithm>
#define MAX 81
using namespace std;

int main()
{
    while (true)
    {
        int n = 0;
        cout << "Plase enter the number of characters(quit with 0): ";
        cin >> n;
        if (!n)
            break;
        char s[MAX];
        for (int i = 0; i < n; i++)
        {
            cout << "Enter character(rest " << n - i << " ): ";
            cin >> s[i];
            cout << endl;
        }
        cout << "Enter complished,the result is:";
        int flag = 1;
        for (int i = 0, j = n - 1; i != j && (i - j) != 1; i++, j--)
        {
            if (s[i] == s[j])
                continue;
            else
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            cout << "Yes,it is a palindrome." << endl;
        else
            cout << "No,it is not a palindrome." << endl;
        cout << endl;
    }

    return 0;
}