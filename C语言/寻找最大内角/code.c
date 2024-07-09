#include <stdio.h>
#include <math.h>

struct Point
{
    int x;
    int y;
};

int MAX(double a, double b, double c)
{
    double max = a;
    max = b > max ? b : max;
    max = c > max ? c : max;
    if (max == a)
        return 0;
    else if (max == b)
        return 1;
    else
        return 2;
}

double LEN(struct Point *p1, struct Point *p2)
{
    return sqrt(pow((p1->x - p2->x), 2) + (pow(p1->y - p2->y, 2)));
}

double mycos(double a, double b, double c)
{
    return (a * a + b * b - c * c) / (2 * a * b);
}

double GetMaxAngle(struct Point pts[], int n)
{
    double max, len[3];
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                len[0] = LEN(&pts[i], &pts[j]);
                len[1] = LEN(&pts[i], &pts[k]);
                len[2] = LEN(&pts[j], &pts[k]);
                double temp = 0;
                switch (MAX(len[0], len[1], len[2]))
                {
                case 0:
                {
                    temp = acos(mycos(len[1], len[2], len[0]));
                    break;
                }
                case 1:
                {
                    temp = acos(mycos(len[0], len[2], len[1]));
                    break;
                }
                case 2:
                {
                    temp = acos(mycos(len[1], len[0], len[2]));
                    break;
                }
                }
                max = temp > max ? temp : max;
            }
        }
    }
    return max;
}

int main()
{
    int i, n;
    struct Point pts[50];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    printf("%.6f", GetMaxAngle(pts, n));
    return 0;
}