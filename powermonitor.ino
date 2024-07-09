#define BLYNK_TEMPLATE_ID "TMPL6efXFTF-m"
#define BLYNK_TEMPLATE_NAME "powermonitor"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <PZEM004Tv30.h>
#include <Preferences.h>

// Blynk Auth Token
char auth[] = "";

// WiFi credentials
char ssid[] = "";
char pass[] = "";

// PZEM-004T connection
PZEM004Tv30 pzem1(Serial2, 16, 17); // PZEM-004T #1 on Serial2 (RX2, TX2)
PZEM004Tv30 pzem2(Serial1, 4, 2);   // PZEM-004T #2 on Serial1 (RX1, TX1)

// Blynk virtual pins
#define V_PIN_VOLTAGE_1 V1
#define V_PIN_CURRENT_1 V2
#define V_PIN_POWER_1 V3
#define V_PIN_VOLTAGE_2 V4
#define V_PIN_CURRENT_2 V5
#define V_PIN_POWER_2 V6
#define V_PIN_FREQUENCY_1 V7
#define V_PIN_POWERFACTOR_1 V8
#define V_PIN_TOTALPOWER_1 V9
#define V_PIN_FREQUENCY_2 V10
#define V_PIN_POWERFACTOR_2 V11
#define V_PIN_TOTALPOWER_2 V12
#define V_PIN_RESET_BUTTON V13

Preferences preferences;
float totalEnergy1 = 0;
float totalEnergy2 = 0;

void resetTotalPower() {
  totalEnergy1 = 0;
  totalEnergy2 = 0;
  preferences.putFloat("totalPower1", totalEnergy1);
  preferences.putFloat("totalPower2", totalEnergy2);
}
BLYNK_WRITE(V_PIN_RESET_BUTTON) {
  if (param.asInt() == 1) {
    pzem1.resetEnergy();
    pzem2.resetEnergy();
    resetTotalPower();
  }
}


void setup() {
  // Debug console
  Serial.begin(115200);

  // Initialize Serial ports for PZEM modules
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX2, TX2
  Serial1.begin(9600, SERIAL_8N1, 4, 2);  // RX1, TX1

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize Preferences
  preferences.begin("powerMonitor", false);
  totalEnergy1 = preferences.getFloat("totalEnergy1", 0);
  totalEnergy2 = preferences.getFloat("totalEnergy2", 0);
  
}

void loop() {
  Blynk.run();
  if (Blynk.connected()) {
    Blynk.syncVirtual(V_PIN_RESET_BUTTON); // Check for updates from the app
  }

  // Read values from first PZEM-004T
  float voltage1 = pzem1.voltage();
  float current1 = pzem1.current();
  float power1 = pzem1.power();
  float frequency1 = pzem1.frequency();
  float powerFactor1 = pzem1.pf();
  float energy1 = pzem1.energy();
  
  if (power1 <= 0) {
    voltage1 = 0;
    current1 = 0;
    power1 = 0;
    frequency1 = 0;
    powerFactor1 = 0;
  }else{

  // Accumulate total energy consumption
  totalEnergy1 = energy1;}

  // Print to Serial Monitor
  Serial.print("Voltage1: "); Serial.print(voltage1); Serial.println("V");
  Serial.print("Current1: "); Serial.print(current1); Serial.println("A");
  Serial.print("Power1: "); Serial.print(power1); Serial.println("W");
  Serial.print("Frequency1: "); Serial.print(frequency1); Serial.println("Hz");
  Serial.print("Power Factor1: "); Serial.print(powerFactor1); Serial.println();
  Serial.print("Total Energy1: "); Serial.print(totalEnergy1); Serial.println("kWh");

  // Send data to Blynk
  Blynk.virtualWrite(V_PIN_VOLTAGE_1, voltage1);
  Blynk.virtualWrite(V_PIN_CURRENT_1, current1);
  Blynk.virtualWrite(V_PIN_POWER_1, power1);
  Blynk.virtualWrite(V_PIN_FREQUENCY_1, frequency1);
  Blynk.virtualWrite(V_PIN_POWERFACTOR_1, powerFactor1);
  Blynk.virtualWrite(V_PIN_TOTALPOWER_1, totalEnergy1);

  // Read values from second PZEM-004T
  float voltage2 = pzem2.voltage();
  float current2 = pzem2.current();
  float power2 = pzem2.power();
  float frequency2 = pzem2.frequency();
  float powerFactor2 = pzem2.pf();
  float energy2 = pzem2.energy();
  if (power2 <= 0) {
    voltage2 = 0;
    current2 = 0;
    power2 = 0;
    frequency2 = 0;
    powerFactor2 = 0;
  } else{

  // Accumulate total energy consumption
  totalEnergy2 =energy2;}

  // Print to Serial Monitor
  Serial.print("Voltage2: "); Serial.print(voltage2); Serial.println("V");
  Serial.print("Current2: "); Serial.print(current2); Serial.println("A");
  Serial.print("Power2: "); Serial.print(power2); Serial.println("W");
  Serial.print("Frequency2: "); Serial.print(frequency2); Serial.println("Hz");
  Serial.print("Power Factor2: "); Serial.print(powerFactor2); Serial.println();
  Serial.print("Total Energy2: "); Serial.print(totalEnergy2); Serial.println("kWh");

  // Send data to Blynk
  Blynk.virtualWrite(V_PIN_VOLTAGE_2, voltage2);
  Blynk.virtualWrite(V_PIN_CURRENT_2, current2);
  Blynk.virtualWrite(V_PIN_POWER_2, power2);
  Blynk.virtualWrite(V_PIN_FREQUENCY_2, frequency2);
  Blynk.virtualWrite(V_PIN_POWERFACTOR_2, powerFactor2);
  Blynk.virtualWrite(V_PIN_TOTALPOWER_2, totalEnergy2);

  // Save total energy consumption to non-volatile storage
  preferences.putFloat("totalEnergy1", totalEnergy1);
  preferences.putFloat("totalEnergy2", totalEnergy2);

  // Wait for a while before the next loop
  delay(1000);
}
