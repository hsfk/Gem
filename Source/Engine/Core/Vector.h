#pragma once

#include "Serial.h"
#include <vector>

template <typename T>
class Vector : public Serial, public std::vector<T>
{
public:
        virtual void save(Ostream& out) const override
        {
                out < size();
                for (size_t i = 0; i < size(); i++)
                        out < (*this)[i];
        }

        virtual void load(Istream& in) override
        {
                resize(in.read<size_t>());
                for (size_t i = 0; i < size(); i++)
                        in > (*this)[i];
        }
        
        DECLARE_SERIAL(Vector)
};
