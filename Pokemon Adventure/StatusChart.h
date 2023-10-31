#pragma once
#include "Status.h"
#include <unordered_map>

namespace statusIDs
{
	static const unsigned int null = 0;
	static const unsigned int burn = 1;
}



static Status noStatus("", false, false, -1, 0, statusIDs::null);
static Status burn("Burned", true, false, 80, 50, statusIDs::burn);


static std::unordered_map<unsigned int, Status> id_to_status = {

	{statusIDs::null,noStatus},
	{statusIDs::burn,burn}

};