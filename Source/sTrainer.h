#pragma once

#include "sSquadler.h"

struct sTrainer
{

	sSquadler* m_squadlers[6] = { nullptr };

	sf::String m_name;

	sSquadler* m_selected_squadler = nullptr;
};