# Green-Energy
Green Energy is an open source solar energy system.

Solar energy is the cleanest and most available renewable energy source. The Modern technology can harness this energy for a variety of uses, including producing electricity, providing light and heating water for domestic, commercial or industrial application.

The aim of this repository is to design and construct an off grid solar inverter system with mains charging function. The systen is broken into the following modules;
1. Oscillator Module: 

          (i). oscBoard Complited, this board has fully been tested on 12v battery system. 
              Testing on 24V system is ongoing. for more infomation please dowload the manual DOC.rar
              
          (ii). EGS002 proMAX 1 (atmega328P version) coming soon
          
          (iii). EGS002 proMAX  (stm32f103 version), this board has fully been tested on 12V and 24V battery system. 
     
2. Power Inverter Module: Tested.
3. Display Module: Testes.
4. Current Sensor Module: Tested.
5. Power Supply Module: Tested.
6. Solar Charge Controller Module: Coming soon.
#


# 1.0 OSCILATOR / CONTROLLER BOARD

# 1.1 EGS002 proMAX (stm32f103 version)

The EGS002 proMAX module generates the sinusoidal pulse width modulated signal.

![image](https://user-images.githubusercontent.com/10567566/179360064-9f22c057-112e-46ec-b4c9-f8ef385ee254.png)

                                   Fig1 EGS002 proMax front view
#                                   
![image](https://user-images.githubusercontent.com/10567566/179359965-8ca474b1-2b20-4ba8-ae52-40b16689451f.png)

                                    Fig2 EGS002 proMax back view
#
# Main Controllers

EG8010 Chip: Generates the fundamental frequency of 50Hz for the inverter using sinusoidal pulse width modulation, with a modulation frequency of 23.4Khz.

STM32F103: Generates 50KHz for the boost converter, and also provides all the control function for the inverter.

PZEM004T: Provides all metering function for power management.

# Specification
Fundamental frequency is 50Hz
Modulation frequency is 23.4KHz
Boost converter frequency is 50KHz
Unipolar Modulation
Constant current CC and constant voltage CV charging (bulk, absorption and float)
Charging control algorithm (P controller)
Inverter output voltage control algorithm (PI controller)
Short circuit protection (not tested yet)
Mains over voltage and under voltage protection
Inverter over voltage and under voltage cut-off
Serial LCD interface (modbus RTU)

# User interface
1.	TWI interface
2.	Serial LCD interface (using UART or Modbus RTU)
3.	Power ON/OFF switch interface
4.	Programing Enable Interface (Boot0)
5.	Debug Enable Interface
6.	Configuration Enable Interface
7.	Programing Interface (UART)

 for more infomation on the EGS002 proMAX, please download the manual 

# 2.0 MODBUS RTU DISPLAY 

# 2.1 LCD 20X4 
![modbus LCD 20X4](https://user-images.githubusercontent.com/10567566/179361122-a421a52c-c0ea-41c4-9047-653224a37eed.png)
#


# 3.0 CURRENT SENSOR BOARD 

# 3.1 ACS758 200A module 
![image](https://user-images.githubusercontent.com/10567566/179361096-ceef462d-aa66-4501-96e7-fec9bdf6242c.png)
#

# 3.2 INA282 module 

#

# 3.3 Short circuit module
#

# 4.0 PZEM004T 100A BOARD
![PZEM004T](https://user-images.githubusercontent.com/10567566/179361354-1cf5e786-5747-41f2-82ad-4491fac4e1cc.jpg)

#





