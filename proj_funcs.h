/*
 * proj_funcs.h
 *
 *  Created on: Apr 10, 2017
 *      Author: Ash
 */
#include "proj_globals.h"


#ifndef PROJ_FUNCS_H_
#define PROJ_FUNCS_H_

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

void sendRequest(String apt){

	if (!secureClient.connect(host, httpsPort)) {
		    Serial.println("connection failed");
		    return;
		  }
		if (secureClient.verify(fingerprint, host)) {
		    Serial.println("certificate matches");
		  } else {
		    Serial.println("certificate doesn't match");
		  }

		if(apt == "emergency"){
			apt = "building";
		}

	  // Now we can publish stuff!
	   Serial.println(F("Sending request"));
	   secureClient.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
			   "content-length: 10\r\n\r\n" +
			    apt + "        \r\n"); //make sure spaces + apt.size <= 10


	   Serial.println("request sent");

}




#endif /* PROJ_FUNCS_H_ */
