import random 
def main():

    lines = []
    temp_list = []
    humidity_list=[]
    pressure_list =[]
    number_of_sensors = 5
    #mean and standard deviation
    mu = 0
    sigma = 1
    with open('scenario1_output.txt') as f:
        lines = f.readlines()

        for line in lines: 
            line = line.strip("\n")
            if not(line.find("Main") != -1 or line.find("reachable") != -1 or line.find("collected") != -1):
                data = line.split("#")
                data = data[1].split(",")
                listtostring = ' '.join([str(element) for (element) in data])
                listtostring = listtostring.split(" ")


                temp     = float(listtostring[2])
                humidity = float(listtostring[5])
                pressure = float(listtostring[8])
                
      

                temp_list.append(abs(25.0 - ((temp/number_of_sensors)+random.gauss(mu, sigma))))
                humidity_list.append(abs(40.0-((humidity/number_of_sensors)+random.gauss(mu, sigma))))
                pressure_list.append(abs(101000.0 - ((pressure/number_of_sensors)+random.gauss(mu, sigma))))

        smallest_Temp_error = min(temp_list)
        largest_Temp_error  = max(temp_list)
        average_Temp_error  = round(sum(temp_list)/len(temp_list),2)
        
        smallest_humidity_error = min(humidity_list)
        largest_humidity_error  = max(humidity_list)
        average_humidity_error  = round(sum(humidity_list)/len(humidity_list),2)
        
        smallest_pressure_error = min(pressure_list)
        largest_pressure_error  = max(pressure_list)
        average_pressure_error  = round(sum(pressure_list)/len(pressure_list),2)
        print(f"smallest_Temp_error     = {smallest_Temp_error}, largest_Temp_error = {largest_Temp_error}, average_Temp_error = {average_Temp_error}\n")
        print(f"smallest_humidity_error = {smallest_humidity_error}, largest_humidity_error = {largest_humidity_error}, average_humidity_error = {average_humidity_error}\n")
        print(f"smallest_pressure_error = {smallest_pressure_error}, largest_pressure_error = {largest_pressure_error}, average_pressure_error = {average_pressure_error}\n")
               


main()