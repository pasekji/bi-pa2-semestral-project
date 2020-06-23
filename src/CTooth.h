#ifndef TOOTH_H
#define TOOTH_H

#include "CMisc.h"

class CTooth : public CMisc
{
    public:
        CTooth() = default;
        ~CTooth()
        {}

        std::string getLabel() const override
        {
            return "TOOTH";
        }
};

#endif