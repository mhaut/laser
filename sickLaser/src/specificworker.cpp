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
// // 	sicklms = new SickLMS("/dev/ttyUSB0");	
	try {
		sicklms.Initialize();
	}

	catch(...) {
		cerr << "Initialize failed! Are you using the correct IP address?" << endl;
	}
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
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

bool SpecificWorker::readLaserData()
{
// 	try 	
// 	{
// 		try
// 		{
// 			sicklms.GetSickScan(polarvalues, num_values);
// 		}
// 		catch (SickConfigException e)
// 		{
// 			printf("ddede %d   %s\n", __LINE__, e.what());
// 		}
// 		catch (SickTimeoutException e)
// 		{
// 			printf("ddede %d\n", __LINE__);
// 		}
// 		catch (SickIOException e)
// 		{
// 			printf("ddede %d\n", __LINE__);
// 		}
// 		catch (SickThreadException e)
// 		{
// 			printf("ddede %d\n", __LINE__);
// 		}
// 		if(num_values > 361) num_values = 361;
// 		for(unsigned int i = 0; i < num_values; i++)
// 		{
// 			laserPolarData[i] = (double)polarvalues[i]/div_factor;
// 			laserData[i].angle = (180- i*0.5)*M_PI/180.f;
// 			laserData[i].dist = (double)polarvalues[i]/div_factor*1000;
// 		}
// 		for(unsigned int i = 0; i < num_values; i++)
// 		{
// 			printf ("medida de %d es %f \n",i,laserData[i].dist);
// 		}
// 	}
// 	// Catch possible exceptions
//   	catch(...) 
// 	{
// 		std::cerr << "Error while receiving laser data\n" << std::endl;
//  		return false;
//   	}  
   	return true;
}

bool SpecificWorker::readLaserData2()
{
	  try {
    unsigned int status = 1;
    unsigned int num_measurements = 0;
    unsigned int range_1_vals[SickLMS1xx::SICK_LMS_1XX_MAX_NUM_MEASUREMENTS];
    unsigned int range_2_vals[SickLMS1xx::SICK_LMS_1XX_MAX_NUM_MEASUREMENTS];
    //sick_lms_1xx.SetSickScanFreqAndRes(SickLMS1xx::SICK_LMS_1XX_SCAN_FREQ_25,
    //SickLMS1xx::SICK_LMS_1XX_SCAN_RES_25);
    //sick_lms_1xx.SetSickScanDataFormat(SickLMS1xx::SICK_LMS_1XX_DIST_DOUBLE_PULSE,
    //				         SickLMS1xx::SICK_LMS_1XX_REFLECT_NONE);
    sicklms.SetSickScanDataFormat(SickLMS1xx::SICK_LMS_1XX_SCAN_FORMAT_DIST_DOUBLE_PULSE_REFLECT_16BIT);
    for (int i = 0; i < 1000; i++) {
      sicklms.GetSickMeasurements(range_1_vals,range_2_vals,range_1_vals,range_2_vals,num_measurements,&status);
      std::cout << i << ": " << num_measurements << " " << status << std::endl;
    }
  }
	catch (SickConfigException e)
	{
		printf("ddede %d   %s\n", __LINE__, e.what());
	}
  return true;
}

void SpecificWorker::compute()
{
	readLaserData2();
// 	try{
// 		differentialrobot->getBaseState(bState);
// 	}
// 	catch(Ice::Exception e)
// 	{
// 		rError("Error talking to differentialRobot");
// 	}
// 	if (readLaserData()==false)
// 	{
// 		std::cout << "Error reading laser " << std::endl;
// 	}
// 	//usleep(Period*100);
}







