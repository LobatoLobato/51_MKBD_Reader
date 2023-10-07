#pragma once
#include "8052.h"

#define sei() EA = 1
#define cli() EA = 0