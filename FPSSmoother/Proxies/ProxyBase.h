#pragma once

class ProxyBase
{
public:
    virtual void CopyTo(ProxyBase *other) = 0;
};