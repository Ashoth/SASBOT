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

    payload = payload[8:]
    payload = json.loads(payload)
    print(payload)
    access = payload['actions'][0]['value']

    if(access == "grant"):
        update = 'Access Granted'
        aio.send('access', 121)
    else:
        update = 'Access Denied'
        aio.send('access', 120)

    return {
        'statusCode': '200',
        'body': update,
        'headers': {
            'Content-Type': 'application/json',
        },
    }
