'''
Created on Mar 4, 2017

@author: Ash
'''


#mess = {}  #dictionary
atta = [] #list
actions = []
conf = {'title': 'Are you sure?', 'text': 'Are you sure?', 'ok_text': 'Yes', 'dismiss_text':'No'}

actions.append({'name':'access', 'text':'Grant', 'type':'button', 'value':'grant'})
actions.append({'name':'access', 'text':'Deny', 'style':'danger',
                'type':'button', 'value':'deny', 'confirm': conf })

atta=[{'text':'Do you want to let them in?', 'fallback':'You are unable to control from here',
             'callback_id':'callback','color':'#3aa3e3', 'attachment_type':'default',
             'actions':actions}]

Status200 = "{'statusCode': '200','headers': {'Content-Type': 'application/json',},}"