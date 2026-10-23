#include <Arduino.h>
#include <WiFi.h>

#include "SinricPro.h"
#include "SinricProSwitch.h"

/* ================= WIFI ================= */

char ssid[] = "G";
char pass[] = "123456789";

/* ================= SINRIC PRO ================= */

#define APP_KEY "9a05f916-1efe-4e75-830c-87cc70f0fa7d"

#define APP_SECRET "379d9804-a479-4504-b565-e26094377601-4466d061-c322-4667-a6ca-7eff0ca65450-4466d061-c322-4667-a6ca-7eff0ca65450"

/* ================= LIGHT DEVICE ================= */

#define LIGHT_DEVICE_ID "6a3001f6969af7ec2454250d"

/* ================= FAN DEVICE ================= */

// Replace this with your Fan device ID from Sinric Pro
#define FAN_DEVICE_ID "6ab4b877b597c4e1235321ba"

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