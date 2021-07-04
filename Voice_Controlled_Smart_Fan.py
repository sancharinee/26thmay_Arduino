import requests
import serial

com=serial.Serial("COM2",9600)

def thingspeak_read():
    URL='https://api.thingspeak.com/channels/1422918/feeds.json?api_key='
    key='BQ82R4M8LOJZKTL9'
    header='&results=1'
    new_url=URL+key+header
    get_data=requests.get(new_url).json()
    print("Data recieved")
    entry_no=get_data['channel']['last_entry_id']
    fanStatus=get_data['feeds'][0]['field1']
    print("Entry no. = ",entry_no)
    print("Fan Status = ",fanStatus)
    print("")
    com.write(fanStatus.encode('utf-8'))


while 1:
    thingspeak_read()
