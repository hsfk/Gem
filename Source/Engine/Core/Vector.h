#pragma once

#include "Serial.h"
#include <vector>

template <typename T>
class Vector : public Serial, public std::vector<T>
{
public:
        virtual void save(Ostream& out) const override {}
        virtual void load(Istream& in) override {}
        
        DECLARE_SERIAL(Vector)
};
