
//David Harbottle
//10-08-15
//voltage level sensor for 12v sealed lead acid battery

double resistor1 = 980.0; //ohms measurement from ohmmeter
double resistor2 = 9830.0; //ohms measurement from ohmmeter
double zenerdiode = 7.74;  //voltage drop across zener diode

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  //voltage max: ~13.4V, 1023 limit hit
  //voltage min: ~7.8V, 1-0 limit hit

  //voltage drop on zener diode : ~7.7V
  //voltage divider circuit:

  /***

  v+ (12v sealed lead acid battery)
  |
  |
  D1 (7.74v zener diode)
  |
  |
  R1 (980 Ohm)
  |
  |
  . ---------> <A3] Arduino
  |
  |
  R2 (9830 Ohm)
  |
  |
  __
  V0


  ***/

  //MATHS:


  // read voltage, calculate battery's voltage, print it out
  Serial.print(voltageCalc(analogRead(A3)));
  Serial.println("v");
  delay(1000);
}


// floating point arithmatics
// Arduino does ADC on pin A3 and returns a value from (0-1023)
// but what we need is the recorded voltage, so we re-map it
// to compute the voltage on pin A3
double voltageCalc (int input)
{
  double temp = (map(input, 0, 1023, 0, 500) / 100.0);

  return (0.04 + zenerdiode + temp * ((resistor1 + resistor2) / resistor2));
}

