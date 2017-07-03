'''
Created on Mar 4, 2017

@author: Ash
'''

from __future__ import print_function
from Adafruit_IO import Client
import json
import urllib


# Set to your Adafruit IO key.
ADAFRUIT_IO_KEY = 'Your Token'
aio = Client(ADAFRUIT_IO_KEY)


def lambda_handler(event, context):

    payload = urllib.unquote(urllib.unquote(event['body']))
    print(payload);
    message = payload[payload.find("text")+5:]
    message = message[:message.find("&")]
    message = message.replace("+", " ")
    print(message)
    channel = payload[payload.find("channel_id")+11:]
    channel = channel[:channel.find("&")]
    print(channel)
    if channel == "your channel ID":
        channel = "manager"
    elif channel == "your channel ID":
        channel = "apt1"
    elif channel == "your channel ID":
        channel = "apt2"
    else:
        return {
            'statusCode': '200',
            'body': 'Cannot post updates here.',
            'headers': {
                'Content-Type': 'application/json',
            },
        }

    channel = "postupdate" + channel
    aio.send(channel, message)

    return {
        'statusCode': '200',
        'body': 'Updated!',
        'headers': {
            'Content-Type': 'application/json',
        },
    }
