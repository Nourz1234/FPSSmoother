#pragma once

template <typename T>
class ICloneable
{
public:
    virtual void CopyTo(T *other) = 0;
};