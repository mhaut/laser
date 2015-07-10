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

/**
       \brief
       @author authorname
*/







#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

#include <QtCore>
#include <stdint.h>
#include <qlog/qlog.h>
#include <Laser.h>
#include "SickLMS.hh"
#include "SickLMS1xx.hh"

using namespace SickToolbox;

class SpecificWorker : public GenericWorker
{
Q_OBJECT
private:
 	RoboCompLaser::TLaserData laserData;
 	RoboCompLaser::LaserConfData laserConf;
 	RoboCompDifferentialRobot::DifferentialRobotPrx differentialrobot;
 	RoboCompDifferentialRobot::TBaseState bState;

	
// 	SickLMS        *sicklms;
	/*
	* Instantiate an instance
	*/
	SickLMS1xx sicklms;
	
	std::string     sicklms_dev_path;
	sick_lms_baud_t sicklms_desired_baud;
	double          sick_scan_angle;
	double          sick_scan_resolution;
	unsigned int polarvalues[SickLMS::SICK_MAX_NUM_MEASUREMENTS]; // Uses macro defined in SickLMS.hh
	unsigned int num_values;
	double       laserPolarData[361];
	double div_factor;
	double scanres;
	sick_lms_measuring_units_t units;
  
public:
	RoboCompLaser::TLaserData getNewData();
	RoboCompLaser::LaserConfData getLaserConf();
	RoboCompDifferentialRobot::TBaseState getBaseData();

	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);


private:
	bool readLaserData();
	bool readLaserData2();

public slots:
	RoboCompDifferentialRobot::TBaseState getBaseState()
	{
		RoboCompDifferentialRobot::TBaseState b;
		try
		{
			differentialrobot->getBaseState(b);
		}
		catch(Ice::Exception e)
		{
			rDebug("Error talking to differentialRobot");
		}
		return b;
	}
	void compute(); 	

private:
	
};

#endif

