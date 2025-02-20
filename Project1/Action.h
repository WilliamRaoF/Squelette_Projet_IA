#pragma once

#include "State.h"

class Action {
public:
	virtual bool CanExecute(const State& state) = 0;
	virtual void Execute(State& state) = 0;
	virtual ~Action() {}
};