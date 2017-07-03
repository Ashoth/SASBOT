/*
 * proj_globals.h
 *
 *  Created on: Apr 10, 2017
 *      Author: Ash
 */

#ifndef PROJ_GLOBALS_H_
#define PROJ_GLOBALS_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Nextion.h"
#include <SoftwareSerial.h>
#include <String.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Your Username"
#define AIO_KEY         "Your Key"

/************************* Global State  ********************************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'reply' for subscribing to changes.
Adafruit_MQTT_Subscribe accessFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/access");
Adafruit_MQTT_Subscribe postupdateApt1Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/postupdateapt1");
Adafruit_MQTT_Subscribe postupdateApt2Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/postupdateapt2");
Adafruit_MQTT_Subscribe postupdateManagerFeed =
		Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/postupdatemanager");


/*************************** Sketch Code ************************************/
#define PIN "1 2 3 4 "
#define DENY "page deniedPage"
#define GRANT "page grantedPage"
#define PINPAGE 6
#define SENDINGPAGE 9

//We are using NodeMCU for this project
SoftwareSerial nextionSerial(D4, D5); // RX, TX
Nextion myNextion(nextionSerial, 9600);
WiFiClientSecure secureClient;
//char* apt; //todo set to users apt
String text = ""; //null pointer
String url = "/prod/PostToSlack";
String access = ""; //null pointer
String updateMess = ""; //null pointer
uint8_t pageID = 0; //init to 0 unsigned char
const char* host = "YOURHOST.execute-api.us-west-1.amazonaws.com";
const int httpsPort = 443;
const char* fingerprint = "80 C7 E4 AF 9B DB 3D 9A 09 25 28 8A EF 3B 1C 9B 08 47 70 A4";
Adafruit_MQTT_Subscribe *subscription;
WiFiManager wifiManager;

#endif /* PROJ_GLOBALS_H_ */
