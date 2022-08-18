#pragma once
#include <memory>

#include "Mode.h"

class ArgumentParser;

std::unique_ptr<Mode> CreateModeFactory(const ArgumentParser& argParser);