#include "proj_globals.h"
#include "proj_funcs.h"
#include "proj_setup.h"

void loop() {

	 MQTT_connect();
	 //if not going to send data within 5 min, ping the server
//	 if(!mqtt.ping()) {
//		  mqtt.disconnect();
//		}

	 //send request
	 	text = myNextion.listen();
	 	pageID = myNextion.pageId();
	 	if(text!=""){
	 		Serial.println("");
	 		Serial.println(text);
	 		text.remove(0, 3); //remove leading 70 code

			 if(pageID == SENDINGPAGE || pageID == 0){
				 sendRequest(text);
			 }else if(pageID == PINPAGE){
				 Serial.println("Checking PIN");
				 if(text == PIN){
					 myNextion.sendCommand(GRANT);
				 }else{
					 myNextion.sendCommand(DENY);
					 if(text == "1 9 9 3 "){
						 wifiManager.resetSettings();
					 }
				 }

			 }
	 	}


	 //check for access
	  while ((subscription = mqtt.readSubscription(500))) {
		  //check for access
		  if (subscription == &accessFeed) {
	    	access = (char*)accessFeed.lastread;
	    	if(access== "121"){
	    		myNextion.sendCommand(GRANT);
	    	}else{
	    		myNextion.sendCommand(DENY);
	    	}
	    	//check for update messages
	    }else if(subscription == &postupdateApt1Feed){
	    	 Serial.print(F("Got from PostUpdate for Apt1: "));
	    	 updateMess = (char*)postupdateApt1Feed.lastread;
	    	 Serial.println(updateMess);
	    	 myNextion.setComponentText("kaywanPage.t0", updateMess);
	    }else if(subscription == &postupdateApt2Feed){
	    	Serial.print(F("Got from PostUpdate for Apt2: "));
	    	updateMess = (char*)postupdateApt2Feed.lastread;
	    	Serial.println(updateMess);
	    	myNextion.setComponentText("ashotPage.t0", updateMess);
	    }else if (subscription == &postupdateManagerFeed){
	    	Serial.print(F("Got from PostUpdate for Manager: "));
	    	updateMess = (char*)postupdateManagerFeed.lastread;
	    	Serial.println(updateMess);
	    	myNextion.setComponentText("yinPage.t0", updateMess);
	    	 }
	    }



}





