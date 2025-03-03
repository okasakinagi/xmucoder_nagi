#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct lastname
{
    string name;
    // other data
    int key;
    lastname(char const *input)
    {
        inline int get_key(string input);
        name = string(input);
        key = get_key(name);
    }
    lastname() : name(""), key(0) {}
    bool operator==(const lastname &other) const
    {
        return key == other.key;
    }
};

inline int get_key(string input)
{
    int key = 0;
    for (int i = 0; i < input.size(); i++) // 采用ascii码计算姓氏的key值
        key += int(input[i]);
    return key;
}

inline int get_key(char const *input)
{
    int key = 0;
    for (int i = 0; input[i] != '\0'; i++) // 采用ascii码计算姓氏的key值
        key += int(input[i]);
    return key;
}

int hash_func(int key, vector<lastname> &result, bool search_mode = false)
{
    int index = key % (result.size() + 1);
    int except = index;
    while ((search_mode || result[index].key != 0) && (!search_mode || result[index].key != key)) // 双条件分别对应创建和查找
    {
        index++;
        if (index == result.size()) // 循环创建同时排除由+1取余导致的溢出情况
            index = 0;
        if (except == index) // 查找失败退出
            return -1;
    }
    return index;
}

int main()
{
    cout << "enter the whole number of last names:";
    int N = 0;
    cin >> N;
    vector<lastname> result(N);
    cout << "enter the last names:";
    for (int i = 0; i < N; i++)
    {
        char name[10];
        cin >> name;
        int key = hash_func(get_key(name), result);
        result[key] = lastname(name);
    }
    // search
    string input;
    cout << "Enter a last name to be searched(end with #):";
    cin >> input;
    while (input != "#")
    {
        int key = get_key(input);
        int index = hash_func(key, result, true);
        if (index == -1)
            cout << "Not found" << endl;
        else
            cout << "Found data: " << result[index].name << endl;
        cin >> input;
    }
    return 0;
}