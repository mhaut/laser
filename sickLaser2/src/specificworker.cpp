
/*
 *    Copyright (C) 2015 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
  
	/* A string for the IP address */
	string sick_ip_addr(DEFAULT_SICK_IP_ADDRESS);

	sick_ip_addr = "192.168.187.204";

	/* Define the data buffers */
	double values[SickLD::SICK_MAX_NUM_MEASUREMENTS] = {0};
	unsigned int num_values = 0;

	/* Define the bounds for a single sector */
	double sector_start_ang = 90;
	double sector_stop_ang = 270;

	/* Define the object */
	SickLD sick_ld(sick_ip_addr);

	/*
	* Initialize the Sick LD
	*/
	try {
	sick_ld.Initialize();
	}

	catch(...) {
	cerr << "Initialize failed! Are you using the correct IP address?" << endl;
	//     return -1;
	}

	try {
		/* Set the desired sector configuration */
		sick_ld.SetSickTempScanAreas(&sector_start_ang,&sector_stop_ang,1);

		/* Print the sector configuration */
		sick_ld.PrintSickSectorConfig();

		/* Acquire some range measurements */
		for (unsigned int i = 0; i < 10; i++)
		{
			/* Here we only want the range values so the second arg is NULL */
			sick_ld.GetSickMeasurements(values,NULL,&num_values);
			for (unsigned int i = 0; i < num_values; i++)
			{
				cout << values[i] <<endl;
			} 
		}


	}
	/* Catch any exceptions */
	catch(...)
	{
		cerr << "An error occurred!" << endl;
	}
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	/*
	* Uninitialize the device
	*/
	try
	{
		sick_ld.Uninitialize();
	}

	catch(...)
	{
		cerr << "Uninitialize failed!" << endl;
	}
}

RoboCompLaser::TLaserData SpecificWorker::getNewData()
{
	return laserData;
}

RoboCompLaser::LaserConfData SpecificWorker::getLaserConf()
{
	return laserConf;  
}

RoboCompDifferentialRobot::TBaseState SpecificWorker::getBaseData()
{
	return bState;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	timer.start(Period);
	return true;
}

void SpecificWorker::compute()
{
	
}