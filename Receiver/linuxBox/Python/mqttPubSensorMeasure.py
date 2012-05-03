import mosquitto
import time
import random


def on_publish(mid):
    print "Message ",mid," published."

#
#
#
#client = mosquitto.Mosquitto(client_id, user_obj=None)
client = mosquitto.Mosquitto("test-client")

#client.connect(hostname, port=1883, keepalive=60, clean_session=true)
client.connect("127.0.0.1")

#client.loop(timeout=-1)
client.loop()

#
#   La forma de interrogar a los sensores es la de Maestro-Esclavo
#   el maestro le pregunta a los esclavos y el esclavo responde, el maestro
#   conoce todo sobre los esclavos. Maestro-Esclavo es igual a  Cliente-Servidor
#    
#
#   Un sensor esta conectado a un Transmisor
#   Un Transmisor puede tener varios sensores
#   a Transmisor se le pide el estado de un sensor por vez   
#   un Transmisor puede tener n entradas digitales y p entradas analogicas
#   El pedido de estado se hace considerando una identificacion de transmisor y
#   una identificacion de sensor ejemplo TransmiterId:SensorId
#   La forma de SensorId a/d(i)  a es analogico, d es digital e i un valor 
#   entero que va de 0 a n-1 para los digitales y de 0 a p-1 para los analogicos
#   La red de sensores inalambricos puede tener M sensores, las direcciones para
#   sensores van de 1 a M-1, la direccion 0 queda reservada para quien interroga 
#   la red, ejemplo   32:a0  interroga la entrada analogica 0 del sensor en la direccion
#   32 de la red.  
#   
#
#   Para identificar un sensor en una instalacion se necesita considerar una agrupacion 
#   Sistema:SubSistema:Transmisor:Sensor  ej 1:2:32:a0 o s1:sb2:t32:a0
#   
#   Hay que considerar q un transmisor no esta compartido entre sistemas
#
#



client.on_publish = on_publish


while client.loop() == 0:

  now = time.localtime(time.time())
  timeAdq = time.strftime("%y/%m/%d %H:%M:%S", now) + " "
  message = timeAdq + " " + ":0204FFFFFF!" 
  clave = "Sensor/"  

  client.publish(clave, message , 1)

  print message


  time.sleep(2)


