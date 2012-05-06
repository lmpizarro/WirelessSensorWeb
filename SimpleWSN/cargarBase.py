import os
import sys
from optparse import OptionParser


usage = "usage: %prog -s SETTINGS | --settings=SETTINGS"
parser = OptionParser(usage)
parser.add_option('-s', '--settings', dest='settings', metavar='SETTINGS',
                  help="The Django settings module to use")
(options, args) = parser.parse_args()
if not options.settings:
    parser.error("You must specify a settings module")

os.environ['DJANGO_SETTINGS_MODULE'] = options.settings

from Measures.models import mqttConfig
from Measures.models import gwType
from Measures.models import Location
from Measures.models import Gateway

#m = mqttConfig (topic="un topic", descripcion="estoy viendo como es", ipAddress="192.168.1.10")
#m.save()
#print m.id

#m = gwType (name="Arduino-USB",description="Arduino conectado a un puerto USB")

#m.save()
#print m.id

#m = gwType (name="Arduino-MQTT",description="Arduino conectado a Ethernet como cliente MQTT")

#m.save()
#print m.id

#m = Location (title="Casa Pepe", country = "Argentina", geo_lat = -34.00, geo_long = -56.00)

#m.save()
#print m.id


#m = Gateway (descripcion="Gateway Inicial", tipoGw = gwType.objects.get(pk=1), mqttConfig=mqttConfig.objects.get(pk=1), ipAddress="192.168.34.23", ubicacion=Location.objects.get(pk=1))

#m.save()
#print m.id


