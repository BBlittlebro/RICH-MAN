#include "CMapUnit.h"
#include <stdio.h>
int MapUnit::index = 0;
void UpUnit::SetFineList(const int num[], const int n)
{
    for (int i = 0; i < n; ++i)
    {
        fine_list_[i] = num[i];
    }
}
int RandUnit::Fine() const
{
    srand(time(NULL));
    return ((rand() % 6) + 1) * fine_;
}
void UpUnit::Display() const
{
    if (Host() == Init)
        printf("  [%d]%10s     B$%5d       ", Id(), Name().c_str(), Price());
    else
        printf("  [%d]%10s {%d} U$%5d L%d    ", Id(), Name().c_str(), Host(), Price(), Level());
}
void ColUnit::Display() const
{
    if (Host() == Init)
        printf("  [%d]%10s     B$%5d       ", Id(), Name().c_str(), Price());
    else
        printf("  [%d]%10s {%d} x", Id(), Name().c_str(), Host());
}
void RandUnit::Display() const
{
    if (Host() == Init)
        printf("  [%d]%10s     B$%5d       ", Id(), Name().c_str(), Price());
    else
        printf("  [%d]%10s {%d} ?             ", Id(), Name().c_str(), Host());
}
void JailUnit::Display() const
{
    printf("  [%d]      Jail                   ", Id());
}
