#pragma once

#include "Action.h"

class HuntAction : public Action {
public:
	bool CanExecute(const State& state) override;
	void Execute(State& state) override;
};