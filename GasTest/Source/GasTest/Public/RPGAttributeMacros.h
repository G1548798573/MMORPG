﻿#pragma once
#pragma once

#include"AttributeSet.h"
#define PROPERTY_FUNCTION_REGISTRATION(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct RPGAttributeMacros
{
	
};
