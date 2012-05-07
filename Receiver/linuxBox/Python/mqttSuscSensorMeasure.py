#!/usr/bin/python

import mosquitto
import time




def on_message(msg):
  message = msg.payload.split('%')
  timeAdq = message [0]
  gatewayIP = message[1]
  sensorMsg = message[2]
  sensorID = sensorMsg[1] + sensorMsg [2]
  codeFunction = sensorMsg[3] + sensorMsg [4]
  sensorValue = sensorMsg[5] + sensorMsg [6] + sensorMsg [7] + sensorMsg [8]
  ckSum   = sensorMsg[9] +sensorMsg[10]
   
  print "time:%s gw:%s sid:%s cf:%s sv:%s"%(timeAdq, gatewayIP, sensorID, codeFunction, sensorValue)
  #print  msg.payload, msg.mid, msg.topic,  msg.qos, msg.retain, countMess

def on_connect(rc):
    if rc == 0:
        print "Connected successfully."

def on_subscribe(obj, mid, granted_qos):
  print "subscribed"

def on_unsubscribe(mosq, obj, mid):
    print("Unsubscribe with mid "+str(mid)+" received.")


 


#mosquitto_sub -d -t Sensores/+/

#create a broker
#client = mosquitto.Mosquitto(client_id, user_obj=None)
client = mosquitto.Mosquitto("test-subsc")

client.on_connect = on_connect
client.on_message = on_message
client.on_subscribe = on_subscribe
client.on_unsubscribe = on_unsubscribe


#client.connect(hostname="127.0.0.1", port=1883, keepalive=60, clean_session=true)
client.connect("127.0.0.1", port=1883, keepalive=60)


#client.loop(timeout=-1)

#client.subscribe(topic, qos)
client.subscribe("simpleWSN/SMB", 0)

countMess = 0
while client.loop()==0:
  pass
