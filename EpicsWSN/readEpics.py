from epics import caget
import time

i = 0
while (1):
   m1 = caget('calib:v1')
   m2 = caget('v1')
   print m1, m2
   time.sleep(2)
