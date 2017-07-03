/*
 * proj_setup.h
 *
 *  Created on: Apr 10, 2017
 *      Author: Ash
 */
#include "proj_globals.h"

#ifndef PROJ_SETUP_H_
#define PROJ_SETUP_H_

void setup() {
	//setup HW serial
	Serial.begin(115200);

	//to configure WIFI for the connect to SASBOT with
	//password of "password" and follow the prompts
	//to reset WIFI go to pin page and enter 1993,
	//then restart the system.
	wifiManager.autoConnect("SASBOT", "password");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	//Nextion
	myNextion.init();

	// Setup MQTT subscriptions
	 mqtt.subscribe(&accessFeed);
	 mqtt.subscribe(&postupdateApt1Feed);
	 mqtt.subscribe(&postupdateApt2Feed);
	 mqtt.subscribe(&postupdateManagerFeed);


}




#endif /* PROJ_SETUP_H_ */
