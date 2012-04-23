#!/usr/bin/python
#
#
#
#   Recibe un mensaje por el puerto serie del tipo :xxxxxxxxxx!
#   De la clase RTU ASCII con Codigo Func 3, obtiene la info del
#   ADC y la imprime  
#   Aplicable al ADC con sensor de temp del MSP430g2231 
#
#
#

import time
import serial
import sys
import sys
class Logger(object):
    def __init__(self, filename="Default.log"):
        self.terminal = sys.stdout
        self.log = open(filename, "a")

    def write(self, message):
        self.terminal.write(message)
        self.log.write(message)




def adcToDec (mensaje):
  dec = 16*16*16*int(mensaje[5],16) + 16*16*int(mensaje[6],16) +  16*int(mensaje[7],16) + int(mensaje[8],16) 
  return dec

def deviceIdToDec (mensaje):
  dec = 16*int(mensaje[1],16) + int(mensaje[2],16) 
  return dec

def decToTempCelsiusMSP430g2231 (dec):
  return ((dec - 673.0)*423.0)/1024.0
  
def decToTempFarenheitMSP430g2231 (dec):
  return ((dec - 630.0)*761.0)/1024.0

def timeToTimeAdq ():
  now = time.localtime(time.time())
  timeAdq = time.strftime("%y/%m/%d %H:%M:%S", now) + " "
  return timeAdq


def procMensajeBueno(mensaje):
  #en las posiciones 5,6,7,8 est el valor buscado
  dec = adcToDec (mensaje)
  devId = deviceIdToDec (mensaje)
  #print "mensaje bueno " ,  mensaje, timeAdq, decToTempCelsiusMSP430g2231(dec), decToTempFarenheitMSP430g2231 (dec)
  print "%s %d %3.2f %3.2f " % (timeToTimeAdq(), devId, decToTempCelsiusMSP430g2231(dec), decToTempFarenheitMSP430g2231 (dec))


def procMensajeMalo():
  print "%s Mensaje malo" % (timeToTimeAdq())


#
#  http://stackoverflow.com/questions/676172/full-examples-of-using-pyserial-package
#  
#

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=57600,
    #parity=serial.PARITY_ODD,
    #stopbits=serial.STOPBITS_TWO,
    #bytesize=serial.SEVENBITS
)

sys.stdout = Logger("./temp.log")
print "Hello world !" # this is should be saved in yourlogfilename.txt
#sys.stdout = open('temp.log', 'w')
ser.open()
ser.isOpen()

mensaje = [None]*12
input=1
i = 0
while 1 :
  # let's wait one second before reading output (let's give device time to answer)
  time.sleep(1)
  while ser.inWaiting() > 0:
      c = ser.read(1)
      if (c ==':'):
        i = 0
        mensaje[i] = c
      else:    # No es el comienzo
        if (c=='!'):  # es el fin ?
          if (i==10):
            i = i + 1
            mensaje[i] = c
            #print "mensaje bueno " ,  mensaje
            procMensajeBueno(mensaje)
          else:
            procMensajeMalo()
            i=0
            break
        else:
          i = i + 1
          if (i > 11):
            procMensajeMalo()
            i=0
            break
          mensaje[i] = c
