#include "Routing_TABLE_BASED.h"

RoutingAlgorithmsRegister Routing_TABLE_BASED::routingAlgorithmsRegister("TABLE_BASED", getInstance());

Routing_TABLE_BASED * Routing_TABLE_BASED::routing_TABLE_BASED = 0;

Routing_TABLE_BASED * Routing_TABLE_BASED::getInstance() {
	if ( routing_TABLE_BASED == 0 )
		routing_TABLE_BASED = new Routing_TABLE_BASED();

	return routing_TABLE_BASED;
}

vector<int> Routing_TABLE_BASED::route(Router * router, const RouteData & routeData)
{


    Coord current = id2Coord(routeData.current_id);
    Coord destination = id2Coord(routeData.dst_id);

    AdmissibleOutputs ao = router->routing_table.getAdmissibleOutputs(routeData.dir_in, routeData.dst_id);

    if (ao.size() == 0) {
        LOG << "dir: " << routeData.dir_in << ", (" << current.x << "," << current.
            y << ") --> " << "(" << destination.x << "," << destination.
            y << ")" << endl << routeData.current_id << "->" <<
            routeData.dst_id << endl;
    }

    if(ao.size()==0){
        cout <<	"\n\tRouteData:" <<
            "\t- current_id=" << routeData.current_id << 
            "\t- src_id=" << routeData.src_id << 
            "\t- dst_id=" << routeData.dst_id << 
            "\t- dir_in=" << routeData.dir_in << endl << endl;	
            assert(ao.size() > 0 && "Possible problem on the routing table\n");		
    }

    return admissibleOutputsSet2Vector(ao);
}
