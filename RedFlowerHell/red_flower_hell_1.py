import MalmoPython
import os
import sys
import time
import random
import json
import math
from enum import Enum

#Create default Malmo objects:

agent_host = MalmoPython.AgentHost()
try:
    agent_host.parse(sys.argv)
except RuntimeError as e:
    print('ERROR:', e)
    print(agent_host.getUsage())
    exit(1)
if agent_host.receivedArgument("help"):
    print(agent_host.getUsage())
    exit(0)

# -- set up the mission -- #
missionXML_file='nb4tf4i.xml'
with open(missionXML_file, 'r') as f:
    print("Loading mission from %s" % missionXML_file)
    mission_xml = f.read()
    my_mission = MalmoPython.MissionSpec(mission_xml, True)
    my_mission.drawBlock( 0, 0, 0, "lava")


my_mission_record = MalmoPython.MissionRecordSpec()

# Attempt to start a mission:
for retry in range(6):
    try:
        agent_host.startMission(my_mission, my_mission_record)
        break
    except RuntimeError as e:
        if retry == 5:
            print("Error starting mission:", e)
            exit(1)
        else:
            print("Attempting to start the mission:")
            time.sleep(2)

# Loop until mission starts:
print("Waiting for the mission to start ")
world_state = agent_host.getWorldState()

while not world_state.has_mission_begun:
    print(".", sep="", end="", flush=True)
    time.sleep(0.5)
    world_state = agent_host.getWorldState()
    for error in world_state.errors:
        print("Error:",error.text)

##############################################################################################

print("\nNB4tf4i Red Flower Hell running\n")

class Action(Enum):
    RESET = 0
    SEARCH = 1
    MOVE = 2
    COLLECT = 3

iter = 0
ob = None
state = Action.RESET
target_flower = None

#commands are sent 20 times a sec apparently
#TODO: sleep is not exactly reliable, find a better way to sync stuff
while world_state.is_mission_running:
    print("\033c", sep="", end="", flush=True)

    ob = None
    while ob == None:
        world_state = agent_host.getWorldState()
        if len(world_state.observations) > 0:
            ob = json.loads(world_state.observations[-1].text)

            #print(ob.get("LineOfSight"))
            #XPos, YPos, ZPos, Pitch, Yaw, Hotbar_[0-9]_size, Hotbar_[0-9]_item --player stuff
        time.sleep(1/20)

    print("State:", state)

    if state == Action.RESET:
        if ob.get("Pitch") != 90:
            agent_host.sendCommand("pitch 1")
        else:
            state = Action.SEARCH
    elif state == Action.SEARCH:
        sight = ob.get("LineOfSight")
        if sight == None:
            if ob.get("Pitch") < 45:
                state = Action.RESET    
        else:
            agent_host.sendCommand("pitch -0.05"
                + str(max(-0.05, 0.1 / sight.get("distance")))
            )
            agent_host.sendCommand("turn "
                + str(min(1.0, 1.0 / sight.get("distance")))
            )
        
        if sight != None and sight.get("type") == "red_flower":
            target_flower = sight
            state = Action.MOVE
    elif state == Action.MOVE:
        if target_flower == None:
            state = Action.RESET
        else:
            agent_host.sendCommand("pitch 0")
            agent_host.sendCommand("turn 0")

    time.sleep(1/20)
    iter += 1



print("Number of flowers: " + str(n_flowers))
print("Mission ended")