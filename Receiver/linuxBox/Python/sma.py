from collections import deque

#
# http://rosettacode.org/wiki/Averages/Simple_moving_average#Python
#

 
 
class Simplemovingaverage():
    def __init__(self, period):
        assert period == int(period) and period > 0, "Period must be an integer >0"
        self.period = period
        self.stream = deque()
 
    def __call__(self, n):
        stream = self.stream
        stream.append(n)    # appends on the right
        streamlength = len(stream)
        if streamlength > self.period:
            stream.popleft()
            streamlength -= 1
        if streamlength == 0:
            average = 0
        else:
            average = sum( stream ) / streamlength
 
        return average


if __name__ == '__main__':
    for period in [3, 5]:
        print ("\nSIMPLE MOVING AVERAGE (class based): PERIOD =", period)
        sma = Simplemovingaverage(period)
        for i in range(1,6):
            print ("  Next number = %-2g, SMA = %g " % (i, sma(i)))
        for i in range(5, 0, -1):
            print ("  Next number = %-2g, SMA = %g " % (i, sma(i)))
