#include <Arduino.h>
#include <WiFi.h>

#include "SinricPro.h"
#include "SinricProSwitch.h"

/* ================= WIFI ================= */

char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";

/* ================= SINRIC PRO ================= */

#define APP_KEY "YOUR APP KEY"

#define APP_SECRET "YOUR APP SECRET KEY"

/* ================= LIGHT DEVICE ================= */

#define LIGHT_DEVICE_ID "YOUR LIGHT ID"

/* ================= FAN DEVICE ================= */

// Replace this with your Fan device ID from Sinric Pro
#define FAN_DEVICE_ID "YOUR FAN ID"

/* ================= PINS ================= */

#define LIGHT_PIN 13
#define FAN_PIN   14


/* =================================================
   LIGHT CALLBACK
   ================================================= */

bool onLightPowerState(
  const String &deviceId,
  bool &state
)
{
  Serial.printf(
    "Light %s turned %s\n",
    deviceId.c_str(),
    state ? "ON" : "OFF"
  );

  digitalWrite(
    LIGHT_PIN,
    state ? HIGH : LOW
  );

  return true;
}


/* =================================================
   FAN CALLBACK
   ================================================= */

bool onFanPowerState(
  const String &deviceId,
  bool &state
)
{
  Serial.printf(
    "Fan %s turned %s\n",
    deviceId.c_str(),
    state ? "ON" : "OFF"
  );

  digitalWrite(
    FAN_PIN,
    state ? HIGH : LOW
  );

  return true;
}


/* =================================================
   WIFI SETUP
   ================================================= */

void setupWiFi()
{
  Serial.print("Connecting to WiFi");

  WiFi.begin(
    ssid,
    pass
  );

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  Serial.print(
    "Connected! IP Address: "
  );

  Serial.println(
    WiFi.localIP()
  );
}


/* =================================================
   SINRIC PRO SETUP
   ================================================= */

void setupSinricPro()
{
  // -------- LIGHT --------

  SinricProSwitch &light =
    SinricPro[LIGHT_DEVICE_ID];

  light.onPowerState(
    onLightPowerState
  );


  // -------- FAN --------

  SinricProSwitch &fan =
    SinricPro[FAN_DEVICE_ID];

  fan.onPowerState(
    onFanPowerState
  );


  // -------- SINRIC PRO --------

  SinricPro.begin(
    APP_KEY,
    APP_SECRET
  );

  SinricPro.restoreDeviceStates(
    true
  );
}


/* =================================================
   SETUP
   ================================================= */

void setup()
{
  Serial.begin(115200);

  // Light
  pinMode(
    LIGHT_PIN,
    OUTPUT
  );

  digitalWrite(
    LIGHT_PIN,
    LOW
  );


  // Fan
  pinMode(
    FAN_PIN,
    OUTPUT
  );

  digitalWrite(
    FAN_PIN,
    LOW
  );


  setupWiFi();

  setupSinricPro();

  Serial.println();
  Serial.println(
    "=========================="
  );

  Serial.println(
    "Light + Fan System Ready"
  );

  Serial.println(
    "=========================="
  );
}


/* =================================================
   LOOP
   ================================================= */

void loop()
{
  SinricPro.handle();
}
