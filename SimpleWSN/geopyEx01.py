from geopy import geocoders 

g = geocoders.Google()
#place, (lat, lng) = g.geocode("10900 Euclid Ave in Cleveland")  
#place, (lat, lng) = g.geocode("3895 Baigorria in Buenos Aires")  
#place, (lat, lng) = g.geocode("80 Liniers in Viedma")  
place, (lat, lng) = g.geocode("4080 Corrientes Ave in Buenos Aires")  
print "%s: %.5f, %.5f" % (place, lat, lng)  
