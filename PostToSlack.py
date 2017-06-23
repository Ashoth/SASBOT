'''
Created on Mar 4, 2017

@author: Ash
'''

from __future__ import print_function
from slackclient import SlackClient
import time
import json
from CommonStrings import *


ashapptoken = "Your token" //tenant1
kayapptoken = "Your token"  //tenant2
bottoken = "Your token"
botsc = SlackClient(bottoken)
ashappsc = SlackClient(ashapptoken)
kayappsc = SlackClient(kayapptoken)
appsc = ashappsc

def lambda_handler(event, context):

    anounce = "Hey, Someone is at your door."
    apt = event['body']
    apt = apt.replace(" ", "")
    print(apt)
    if apt == "building":
        anounce = "Emergency service is at your door!"
    postStatus = json.dumps(botsc.api_call("chat.postMessage", username='botbot', icon_emoji=':robot_face:',
                       channel=apt, text=anounce, attachments=atta))
    postStatus = json.loads(postStatus)
    print(postStatus)
    print(postStatus['channel'])

    #sleep then check if the user responded
    if (apt == "apt1"):
        appsc = kayappsc
    else:
        appsc = ashappsc
    time.sleep(15)
    currentStatus = json.dumps(appsc.api_call("groups.history", channel=postStatus['channel'],
                                            latest=postStatus['ts'],
                                            oldest=postStatus['ts'], inclusive="true"))
    currentStatus = json.loads(currentStatus)
    print(currentStatus)
    if(not(currentStatus['messages'][0]['text']=="Access Granted" or
      currentStatus['messages'][0]['text']=="Access Denied")):
        #if no response mark as "expired"
        json.dumps(botsc.api_call("chat.update", username='botbot',
            ts=postStatus['ts'], channel=postStatus['channel'], text="Expired",
            attachments=None))
        #delete the message
        time.sleep(5)
        json.dumps(botsc.api_call("chat.delete",
            ts=postStatus['ts'], channel=postStatus['channel']))

    return {
        "statusCode": "200",
        "body": "Request Sent!",
        "headers": {
            "Content-Type": "application/json",
        },
    }
