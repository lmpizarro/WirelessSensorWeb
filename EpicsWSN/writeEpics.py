from epics import caput
import time

i = 0
while (1):
   i = i + 1
   v = i%1023
   m1 = caput('v1',v)
   print v
   time.sleep(1)
