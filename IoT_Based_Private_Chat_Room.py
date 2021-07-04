import paho.mqtt.client as mqtt
import time

pubtop=input("Enter topic name to be published : ")
subtop=input("Enter topic name to be subscribed : ")

def on_connect(client,userdata,flags,rc):
    if(rc==0):  #successful connection of the client with the broker
        client.connect_flag = True  #set connect_flag to TRUE
        print("Connected Successfully")
    else:
        print("Connection failed, returned code = ",rc)
        
def on_message(client,userdata,message):
    print("Message recieved from",message.topic)
    if(str(message.topic)!=pubtop):
        print("Message : ",str(message.payload.decode('utf-8')))
        print("")

def on_subscribe(client,userdata,mid,granted_qos):
    print("")       
    
def on_unsubscribe(client,userdata,mid):
    print("")
    

def on_disconnect(client,userdata,rc):
    if(rc!=0):
        print("Unexpected disconnection")

broker_addr="test.mosquitto.org"
port=1883

client=mqtt.Client()
client.on_subscribe=on_subscribe
client.on_unsubscribe=on_unsubscribe
client.on_connect=on_connect
client.on_message=on_message
client.connect(broker_addr,port)

client.loop_start()
client.subscribe(subtop)

time.sleep(5) #wait some time to connect

while(1):
    print("\nFollowing functions are provided\n")
    print("Type 'quit' to exit.")
    print("Type 'sub' to subscribe new topic.")
    print("Type 'unsub' to unsubscribe ",subtop)
    print("Type 'pub' to publish new topic.")
    print("Type 'chat' to start conversation with",subtop)
    choice=input("\nEnter your choice : ")
    print("");
    if(choice=="quit"):
        client.disconnect()
        client.loop_stop()
        break
    elif(choice=="sub"):
        new_subtop=input("Enter topic name to be subscibed : ")
        client.subscribe(new_subtop)
        print("Subscribed to",new_subtop)
    elif(choice=="unsub"):
        unsubtop=input("Enter topic name to be unsubscibe : ")
        client.unsubscribe(unsubtop)
        print(unsubtop," is unsubscribed.")
    elif(choice=="pub"):
        pubtop=input("Enter topic name to be published : ")
    elif(choice=="chat"):
        print("Start conversation")
        print("Type 'quit' to exit conversation\n")
        print("Type your message")
        while(1):
            msg=input()
            if(msg=='quit'):
                break
            else:
                client.publish(pubtop,msg)
                print("Message send to",subtop)
                print("")
    else:
        print("Invalid entry")      
