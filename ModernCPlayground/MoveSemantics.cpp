#include "ModernCPlayground.h"
#include <memory>
#include <array>

class Embedded
{
public:

    Embedded() = default;
    Embedded(Embedded const& rhs);
    Embedded(Embedded&& rhs) noexcept;
    Embedded& operator = (const Embedded& rhs);
    Embedded& operator = (Embedded&& rhs) noexcept;

private:

    std::array<int, 16> values = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
};

class Container
{
public :

    Container()
    {
        values = new int[1];
        values[0] = 0;
    }

    ~Container()
    {
        delete[] values;
    }

    Container(Container const& rhs);
    Container(Container&& rhs) noexcept;
    Container& operator = (Container const& rhs);
    Container& operator = (Container&& rhs) noexcept;

    int Size() const { return size; }
private :
    int* values = nullptr;
    int size = 0;
    Embedded embedded;
};

template <class T>
void Swap(T& a, T& b)
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

Container ReturnAContainer()
{
    Container container;
    return container;
}

Embedded::Embedded(Embedded const& rhs)
{
    values = rhs.values;
}

Embedded::Embedded(Embedded&& rhs) noexcept
{
    values = rhs.values;
}

Embedded& Embedded::operator = (const Embedded& rhs)
{
    values = rhs.values;
    return *this;
}

Embedded& Embedded::operator = (Embedded&& rhs) noexcept
{
    values = rhs.values;
    return *this;
}

Container::Container(Container const& rhs)
{
    auto newValues = new int[rhs.size];
    memcpy(newValues, rhs.values, sizeof(int) * size);
    values = newValues;
    size = rhs.size;
    embedded = rhs.embedded;
}

Container& Container::operator = ( const Container & rhs)
{
    auto newValues = new int[rhs.size];
    memcpy(newValues, rhs.values, sizeof(int) * size);
    delete[] values;
    values = newValues;
    size = rhs.size;
    embedded = rhs.embedded;
    return *this;
}

Container::Container(Container&& rhs) noexcept
{
    Swap(values, rhs.values);
    size = rhs.size;
    embedded = std::move(rhs.embedded);
}

Container& Container::operator = (Container&& rhs) noexcept
{
    Swap(values, rhs.values);
    size = rhs.size;
    embedded = std::move(rhs.embedded);
    return *this;
}

int TestMove()
{
    Container a = ReturnAContainer();
    Container b(a);
    Container c = a;
    Container d;
    d = Container();
    return d.Size();
}