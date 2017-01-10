#ifndef __H_DISCRETIZATORS_FACTORY
#define __H_DISCRETIZATORS_FACTORY

#include "Discretizator.h"
#include "Configuration.h"


class DiscretizatorsFactory
{
public:
	Discretizator * manufacture(Configuration * configuration, long coreId, long coresQuantity);
};

#endif
