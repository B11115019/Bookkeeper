#pragma once
#include "RecordSystem.h"
#include "include/nlohmann/json.hpp"
#include <fstream>

bool loadRecordData(RecordSystem&);
bool saveRecordData(RecordSystem&);