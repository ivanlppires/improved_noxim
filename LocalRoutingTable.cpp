/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2015 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the implementation of the local routing table
 */

#include "LocalRoutingTable.h"

LocalRoutingTable::LocalRoutingTable()
{
}

void LocalRoutingTable::configure(GlobalRoutingTable & rtable, const int _node_id)
{
	//~ cout << "\t- rt_node = rtable.getNodeRoutingTable(" << _node_id << ") <- ";
	rt_node = rtable.getNodeRoutingTable(_node_id);
	node_id = _node_id;
}

AdmissibleOutputs LocalRoutingTable::getAdmissibleOutputs(const LinkId &
														  in_link, const int destination_id)
{
	//~ cout << "\t\t- return rt_node[<"<< in_link.first <<","<< in_link.second <<">][" << destination_id << "]" << endl; 
	return rt_node[in_link][destination_id];
}

AdmissibleOutputs LocalRoutingTable::getAdmissibleOutputs(const int
														  in_direction, const int destination_id)
{

	LinkId lid = direction2ILinkId(node_id, in_direction);

	return getAdmissibleOutputs(lid, destination_id);
}
