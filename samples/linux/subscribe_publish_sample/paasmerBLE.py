from magicblue import MagicBlue
import sys
import time
print "the arguments are " + str(sys.argv)

blue = 0

def ConnectBlue(mac):
        global blue
        if mac:
                blue = MagicBlue(mac, 9)
                status = blue.connect()
                return status
        else :
                return false
def WriteBlue(mac, state):
        global blue
        #mac = BlueIP[number - 1]
	#mac = 0
        status = ConnectBlue(mac)
        if status:
                if state == "on":
                        print "BLE Bulb ON"
                        blue.turn_on()
                        #BlueStatus[number - 1] = 1
                        #blue.disconnect()
                else:
                        print "BLE Bulb OFF"
                        blue.turn_off()
                        #BlueStatus[number - 1] = 0
                        #blue.disconnect()
                time.sleep(1)
                blue.disconnect()

WriteBlue(sys.argv[1],sys.argv[2])
