# Create your models here.
# -*- coding: latin-1 -*-
#
# Por el coding ver:
# see http://www.python.org/peps/pep-0263.html
#
from django.db import models

# Modificado Mayo 2012
# Se introducen modelos:
#   Location: se modela la ubicacion de distintos dispositivos.
#
#   Red: entidad que agrupa a los gateways VER Q HACER CON ESTO
#   
#   mqttConfig: se guarda la configuracion basica de la cola de mensajes
#  
#   Gateway: el dispositivo particular  que vincula las mediciones 
#   de campo, con el software del servidor
#
#   RTU:
#
#   PV: modelo de una variable particular de proceso
#
#   Proces: el Proces, actividad o equipo sobre el que se realiza
#     el monitoreo
#
#   MedicionesHistoricas: guarda todas las mediciones de una PV
#


#
# Modelo de ubicacion obtenido en: http://www.givp.org/blog/2009/10/31/django-geolocation/
#
# Referencias a geopy: http://code.google.com/p/geopy/wiki/GettingStarted
#
# geopy makes it easy for developers to locate the coordinates of addresses,
# cities, countries, and landmarks across the globe using third-party geocoders
# and other sources of data, such as wikis.
#
#  
#
#
class Location (models.Model):
  title = models.CharField(max_length=200)
  descripcion = models.TextField('descripcion', blank=True, null=True)
  address = models.CharField(max_length=200, blank=True, null=True)
  postcode = models.CharField(max_length=200, blank=True, null=True)
  city = models.CharField(max_length=200, blank=True, null=True)
  country = models.CharField(max_length=100)
  geo_lat = models.DecimalField('latitud', max_digits=13, decimal_places=10, blank=True, null=True)
  geo_long = models.DecimalField('longitud', max_digits=13, decimal_places=10, blank=True, null=True)
  def __unicode__(self):
        return "Location: " + self.title


#
#  En una red se encuentran 1 o más gateways
#  La red es el tronco del árbol de donde se desprenden
#  los gateways, luego las RU, luego los sensores, 
#  luego las PV(Variables de proceso)
#
#  Los Gateways (GW) envian los mensajes recibidos de las 
#  Remote Terminal Units (RTU) a un manejador de cola de
#  mensajes, para este proyecto se eligió MQTT 
#  (MQ Telemetry Transport)
#
class mqttConfig (models.Model):
  topic = models.CharField(max_length=32)
  descripcion = models.TextField('descripcion', blank=True, null=True)
  #
  # direccion ip del servidor de colas de mensajes primario 
  #
  ipAddress = models.IPAddressField()
  def __unicode__(self):
        return "MQTTConfig: " + self.ipAddress


#
# Este comentario puede servir para generar una futura entidad
# que debería tener en cuenta los protocolos
#
# Ejemplo de protocolo es simpleWSN/SMB01AI
# este es el caso de los gateways destinados a tomar
# datos con el protocolo modbus simple de lectura 
# de una variables analogica

class gwType (models.Model):
  name = models.CharField(max_length=32, unique=True)
  description = models.TextField('description', blank=True, null=True)
  def __unicode__(self):
        return "GW Type: " +  self.name
  
TIPOGATEWAY_CHOICES = (
  ('SUSB', 'Arduino-USB'),
  ('MQTT', 'Arduino-MQTT'),
)
#
# Un gateway es el dispositivo que recibe los mensajes 
# de las unidades remotas, tiene una direccion 
# de red ip  y se encarga de enviar los mensajes a una
# cola de mensajes en el servidor
#
class Gateway (models.Model):
  descripcion = models.TextField('descripcion', blank=True, null=True)
  #
  # Describe el tipo de gateway por ejemplo serie (Arduino-USB)
  # o ethernet (Arduino-MQTT)
  #
  tipoGw = models.ForeignKey(gwType)
  #
  # Un gateway pertenece a una sola red, y una red
  # puede tener varios gateways
  #
  mqttConfig = models.ForeignKey (mqttConfig)  
  ipAddress = models.IPAddressField()
  #
  # La ubicacion del gateway dentro de la entidad red, puede
  # ser distinta, 
  #
  #  TAREA: analizar si la ubicacion de sensores y gateways, 
  #  podría hacerse como un desplazamiento en relación a la
  #  referencia de ubicacion q da la entidad RED
  # 
  ubicacion = models.ForeignKey(Location)
  def __unicode__(self):
        return "GW: " +  self.ipAddress


#
# La unidad remota es el dispositivo de campo que transmite
# los mensajes al gateway
#
class RTU (models.Model):
  descripcion = models.TextField('descripcion', blank=True, null=True)
  gateway = models.ForeignKey (Gateway)
  ruAddress = models.IntegerField(max_length=32)
  # numero de variables analogicas que tiene la unidad remote
  cantSensoresAnalog = models.IntegerField()   
  # ATENCION ver q son solo entradas
  cantSensoresDigitales = models.IntegerField()
  #
  #  Describe el tipo de dispositivo de campo
  #  ejemplo: arduino, launchpad
  #
  TIPORU_CHOICES = (
    ('ARDN', 'Arduino'),
    ('LNCH', 'Launchpad'),
   )
  tipoRTU = models.CharField(max_length=4, choices=TIPORU_CHOICES)
  ubicacion = models.ForeignKey(Location)
  def __unicode__(self):
        return "RU: " +  str(self.ruAddress)
#
# Modelo del proceso que se monitorea
#
#
class Proces (models.Model):
  descripcion = models.TextField('descripcion', blank=True, null=True)
  ubicacion = models.ForeignKey(Location)
  def __unicode__(self):
        return "Process: " +  self.descripcion
#
#   Sistema
#
#


#
#   Sub-Sistema
#
#


#
# Un Sensor esta asociado a una unidad remota
# y mide una variable de proceso
#
class PV(models.Model):
  descripcion = models.TextField('descripcion', blank=True, null=True)
  remoteUnit = models.ForeignKey (RTU)
  proceso = models.ForeignKey (Proces)
# analizarlo
  calibracion = models.DecimalField('Calibracion', max_digits=13, decimal_places=4, blank=True, null=True)
  TIPOSENSOR_CHOICES = (
    ('AI', 'Analog Input'),
    ('DI', 'Digital Input'),
#  
#    AI: Entrada analógica
#    DI: Entrada digital
#    AO y DO no van por no tratarse de una aplicación de control de procesos
#
#    ('AO', 'Analog Output'),
#    ('DO', 'Digital Output'),
   )
  tipoSensor = models.CharField(max_length=2, choices=TIPOSENSOR_CHOICES)
  def __unicode__(self):
        return "PV: "  + self.tipoSensor
#
# Almacenamiento persistente de los valores históricos
# de las variables de proceso
#
class pvArchive(models.Model):
  descripcion = models.TextField('descripcion', blank=True, null=True)
  pv = models.ForeignKey(PV)
  value = models.DecimalField('value', max_digits=13, decimal_places=4, blank=True, null=True)
  timeStamp = models.DateTimeField('date created')
  def __unicode__(self):
    return self.value
