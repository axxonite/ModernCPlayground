#include "ModernCPlayground.h"

int leftValue = 42;
int* pLeftValue = &leftValue;

int& ReturnsReference() { return leftValue; }
int ReturnsValue() { return 42; }

void TestRValues()
{
    ReturnsReference() = 42;
    int* pValue = &ReturnsReference();
    int value = 0;
    value = ReturnsValue();
#if REJECTED
    // Cannot take the address of an rvalue.
    pValue = &ReturnsValue();
#endif
    value = 42;
}