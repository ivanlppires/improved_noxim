#include "Hub.h"
#include "Target.h"



void Target::b_transport(tlm::tlm_generic_payload & trans, sc_time & delay)
{
	struct Flit *my_flit = (struct Flit *)trans.get_data_ptr();


	LOG << "*** Received: " << *my_flit << endl;

	if (!buffer_rx.IsFull())
	{

		int dst_port = hub->tile2Port(my_flit->dst_id);

		if (hub->antenna2tile_reservation_table.isAvailable(dst_port))
			GlobalParams::total_wirelessflits++;


		if (my_flit->flit_type == FLIT_TYPE_HEAD)
		{
			if (hub->antenna2tile_reservation_table.isAvailable(dst_port))
			{
				LOG << "Reserving output port " << dst_port << " for channel "
					<< local_id << " for flit " << *my_flit << endl;
				hub->antenna2tile_reservation_table.reserve(local_id, dst_port);

				// The number of commucation using the wireless network, accounting also
				// partial wired path
				hub->wireless_communications_counter++;
			}
			else
			{
				LOG << "WARNING: cannot reserve output port " << dst_port <<
					" for channel " << local_id << ", flit " << *my_flit << endl;
				return;
			}

		}

		if (my_flit->flit_type == FLIT_TYPE_TAIL)
		{
			LOG << "Releasing reservation for output port " << dst_port <<
				", flit " << *my_flit << endl;
			hub->antenna2tile_reservation_table.release(dst_port);
		}


		LOG << "Flit " << *my_flit << " moved to rx_buffer " << endl;
		buffer_rx.Push(*my_flit);
		hub->power.antennaBufferPush();
		// Obliged to set response status to indicate successful completion
		trans.set_response_status(tlm::TLM_OK_RESPONSE);
	}
	else
	{
		LOG << "WARNING: buffer_rx is full cannot store flit " << *my_flit << endl;
	}


	// FIXME: controlla commento in RadioProcess 

}
