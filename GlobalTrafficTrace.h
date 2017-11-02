/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the definition of the global traffic table
 */

#ifndef __NOXIMGLOBALTRAFFIC_TRACE_H__
#define __NOXIMGLOBALTRAFFIC_TRACE_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "DataStructs.h"

using namespace std;

// Structure used to store information into the table
struct Commtrace
{
	int src;					// ID of the source node (PE)
	int dst;					// ID of the destination node (PE)
	int sz;						// Size of information
};

class GlobalTrafficTrace
{

  public:

	GlobalTrafficTrace(const char *fname, int id);

	// Check the queue
	bool isEmpty();

	// return the traffic trace
	Commtrace getComm();

  private:

	int local_id;
	  queue < Commtrace > traffic_trace;
};


#endif
