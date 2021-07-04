import random
import urllib.request
import time

def thingspeak_write():
    val1=random.randint(1,100)
    URL='https://api.thingspeak.com/update?api_key='
    key='QMFW604LDZXHEZV2'
    header1='&field1={}'.format(val1)
    new_url1=URL+key+header1
    print("Random val1 = ",val1)
    print(new_url1)
    v1=urllib.request.urlopen(new_url1)
    print(v1)
    print("Data send\n")
    
while(True):
    thingspeak_write()
    time.sleep(20) #thingspeak needs minimum 15 sec delay between updates
