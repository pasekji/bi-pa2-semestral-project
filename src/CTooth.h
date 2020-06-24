#ifndef TOOTH_H
#define TOOTH_H

#include "CMisc.h"

class CTooth : public CMisc
{
    public:
        CTooth() = default;
        virtual ~CTooth() = default;

        std::string getLabel() const override;
};

#endif