# -*- coding: utf-8 -*-
"""
Created on Mon Sep 11 22:49:24 2017

@author: franc
"""

from time import sleep

import serial 
import numpy as np  
import matplotlib.pyplot as plt 
from drawnow import *
import pandas as pd

ser = serial.Serial('COM7', 9600) # stabilisce connessione nella porta selezionata
cnt = 0
data_f = pd.DataFrame(columns = ['Degrees', 'Distance'])
deg_data = []
dist_data = []
while True:
    while (ser.inWaiting()==0): # aspetta(pass) finchè non arrivano i dati
        pass
    string_ser = ser.readline()
    data_string = string_ser.split(',')
    data_f['Degrees'].append(int(data_string[0])) 
    data_f['Distance'].append(int(data_string[1]))
    cnt = cnt+1
    if(cnt == 20):
        break
    # bisogna fare una lista e metterli li dentro
    #print ser.readline()
     #sleep(.1)
        # funziona

