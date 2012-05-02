#!/usr/bin/python

import mosquitto
import time



def on_message(message):
  print "Message", message.payload

def on_connect(rc):
    if rc == 0:
        print "Connected successfully."

def on_subscribe(obj, mid, granted_qos):
  print "subscribed"


#mosquitto_sub -d -t Sensores/+/

#create a broker
#client = mosquitto.Mosquitto(client_id, user_obj=None)
client = mosquitto.Mosquitto("test-subsc")

client.on_connect = on_connect
client.on_message = on_message
client.on_subscribe = on_subscribe


#client.connect(hostname="127.0.0.1", port=1883, keepalive=60, clean_session=true)
client.connect("127.0.0.1", port=1883, keepalive=60)


#client.loop(timeout=-1)

#client.subscribe(topic, qos)
client.subscribe("hola/+", 0)

while client.loop()==0:
  pass
