# Green-Energy
Green Energy is an open source solar energy system.

Solar energy is the cleanest and most available renewable energy source. The Modern technology can harness this energy for a variety of uses, including producing electricity, providing light and heating water for domestic, commercial or industrial application.

The aim of this repository is to design and construct an off grid solar energy system. The systen is broken into the following modules;
1. Oscillator Module: Testing stage.
2. Power Inverter Module: Coming soon.
3. Display Module: Coming soon.
4. Current Sensor Module: Coming soon.
5. Power Supply Module: Coming soon.
6. Solar Charge Controller Module: Coming soon.
7. Transformer: Coming soon.

1.Oscillator  Module ( Version2020-03) The oscilator module generates the sinosodial pulse width  muldulated signal.

Pin1: 3.3V Output. 
Pin2: NTC ( 10K ) Input.
Pin3: LM35 Input reserved.
Pin4: VBat Input, Battery sense input pin. The controller multiplies the voltage at Vbat by 10 for 12V and 24V system, and by 100 for         36V and 48V system, ie. 1.2V= 12V for 12V system, 2.4V=24 for 24V system, 0.36V=36V for 36V system, 0.48V=48V for 48V system. 
Pin5: VMns Input, Mains voltage sense input pin, The controller multiplies the voltage at this pin by 100, ie. 2.20 = 220Vac mains.
Pin6: VFb Input, Inverter output feed back voltage sense, he controller multiplies the voltage at this pin by 100, ie. 2.20 = 220Vac. 
Pin7: IAc Input, The controller measure the AC load current via this pin. 
Pin8: GND, Ground.
Pin9 and Pin10: Relay Output, Open drain, The controller controlls the load via this pin.
Pin11: ZCD, Zero Cross Detector, this pin is reserved.
Pin15: GND, Ground.
Pin16: IDc, Input, The controller measures the shunt current via this pin.
Pin17 and Pin18: HLO, High Frequency, Low side Out, to mosfet driver.
Pin19: GND, Ground.
Pin20: 12V to 18V VCC Input.
Pin22: HVB High Frequency VB, to mosfet driver.
Pin23: GND, Ground.
Pin24 and Pin25: HHO, High Frequency, High side Out, to mosfet driver. 
Pin26 and Pin27: LLO, Low Frequency, Low side Out, to mosfet driver. 
Pin28: GND, Ground.
Pin29: 12V to 18V VCC Input.
Pin31: LVB Low Frequency VB, to mosfet driver.
Pin32: GND, Ground.
Pin33: LHO, Low Frequency, High side Out, to mosfet driver. 
Pin34: FAN2, Fan2 control, reserved.
Pin35: FAN1, Fan1 control, This pin controls a cooling fan vai a mosfet or transistor depending on the current capacity of the fan.
Pin36: GND, Ground.
Pin37: 5V, Input.










