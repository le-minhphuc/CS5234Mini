import csv
from geopy.distance import geodesic


# Read airports data (id, latitude, longitude)
airports_path = "open_flights_airports.csv"
airports = {}
with open(airports_path, "r") as csv_file:
    data_reader = csv.reader(csv_file, delimiter=",")
    for entry in data_reader:
        airports[entry[0]] = (entry[6], entry[7])


# Read routes data (source id, destination id)
routes_path = "open_flights_routes.csv"
routes = []
with open(routes_path, "r") as csv_file:
    data_reader = csv.reader(csv_file, delimiter=",")
    for entry in data_reader:
        if (entry[3] == "\\N"):
            continue
        if (entry[5] == "\\N"):
            continue
        routes.append((entry[3], entry[5]))


# Combine airports and routes
temp_routes = []
used_airports = {}
for (source, destination) in routes:
    try:
        (source_latitude, source_longitude) = airports[source]
        (destination_latitude, destination_longitude) = airports[destination]
        used_airports[int(source)] = True
        used_airports[int(destination)] = True
        temp_routes.append((source, source_latitude, source_longitude,
                            destination, destination_latitude, destination_longitude))
    except:
        pass


# Convert airports id
conversion = {}
labels = sorted(used_airports.keys())
for i in range(len(labels)):
    conversion[labels[i]] = i


# Create final routes data
final_routes = []
for route in temp_routes:
    (s, slat, slon, d, dlat, dlon) = route
    source_location = (slat, slon)
    destination_location = (dlat, dlon)
    distance = geodesic(source_location, destination_location).km
    final_routes.append((conversion[int(s)], conversion[int(d)], distance))
    print("%s %s %s" % (conversion[int(s)], conversion[int(d)], distance))
