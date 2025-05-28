#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
void prinq(T &queueValue)
{
    while (!queueValue.empty())
    {
        cout << queueValue.top() << " ";
        queueValue.pop();
    }
    cout << endl;
}

int main()
{
    {
        priority_queue<int> q;

        for (int elm : {23, 4, 1, 2, 4, 5, 6, 8, 3, 45})
        {
            q.push(elm);
        }
        prinq(q);
    }

    {
        priority_queue<int, vector<int>, greater<int>> q2;
        for (int elm : {23, 4, 1, 2, 4, 5, 6, 8, 3, 45})
        {
            q2.push(elm);
        }

        prinq(q2);
    }

    {
        auto cmp = [](int left, int right)
        {
            return (left) < (right);
        };

        priority_queue<int, vector<int>, decltype(cmp)> q3(cmp);

        for (int elm : {23, 4, 1, 2, 4, 5, 6, 8, 3, 45})
        {
            q3.push(elm);
        }
        prinq(q3);
    }

    return 0;
}