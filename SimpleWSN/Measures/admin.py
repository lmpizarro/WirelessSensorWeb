from Measures.models import mqttConfig
from Measures.models import Location
from Measures.models import gwType
from Measures.models import Gateway
from django.contrib import admin
from Measures.models import RTU
from Measures.models import Proces
from Measures.models import PV
from Measures.models import pvArchive

admin.site.register(mqttConfig)
admin.site.register(Location)
admin.site.register(Gateway)
admin.site.register(gwType)
admin.site.register(RTU)
admin.site.register(Proces)
admin.site.register(PV)
admin.site.register(pvArchive)

