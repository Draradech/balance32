#include "stdinc.h"

#include <WiFi.h>

const char* ssid = "balance32";
const char* passwd = "balance32pwd";

void setupWifi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, passwd);
}
