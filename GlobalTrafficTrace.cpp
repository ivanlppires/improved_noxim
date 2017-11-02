/*
 * Improved Noxim
 * This file contains the implementation of the global traffic trace to Noxim
 */

#include "GlobalTrafficTrace.h"

GlobalTrafficTrace::GlobalTrafficTrace(const char *fname, int id)
{

	// Open file 

	char pe_fname[50];
	sprintf(pe_fname, "%03d_%s", id, fname);

	ifstream fin(pe_fname, ios::in);
	if (!fin)
		assert(false);

	this->local_id = id;

	// Cycle reading file
	while (!fin.eof())
	{
		char line[512];
		fin.getline(line, sizeof(line) - 1);

		if (line[0] != '\0')
		{
			if (line[0] != '%')
			{
				int dst, sz;

				int params = sscanf(line, "%d %d", &dst, &sz);
				if (params >= 2)
				{
					// Create a communication from the parameters read on the line
					Commtrace ct;

					// Mandatory fields
					ct.src = id;
					ct.dst = dst;
					ct.sz = sz;

					// Add this communication to the vector of communications
					traffic_trace.push(ct);
				}
			}
		}
	}
}

bool GlobalTrafficTrace::isEmpty()
{


	if (traffic_trace.empty() && traffic_trace.size() == 0)
	{

		if (!GlobalParams::trace_eof[this->local_id])
		{
			GlobalParams::trace_eof[this->local_id] = true;
			cout << "[" << sc_time_stamp() << "] " << local_id << " is done" << endl;
		}
		return true;
	}
	return false;
}

Commtrace GlobalTrafficTrace::getComm()
{
	Commtrace comm = traffic_trace.front();
	traffic_trace.pop();
	return comm;
}
