#include <EEPROM.h>
#include "TimeLib.h"
char project_name[] = "Auto_version";
struct Version {
  time_t last_upload;
  unsigned int version_number;
};
void setup() {
  Serial.begin(115200);
  //initVersion();
  check_for_upload();
  PrintVersion();
}
void loop() {

}

void initVersion() {
  Version current;
  current.last_upload = str_to_time(__DATE__, __TIME__);
  current.version_number = 0;
  EEPROM.put(0, current);
  Serial.println("Init Version..");
}
void check_for_upload() {
  Version last_version;
  EEPROM.get(0, last_version);
  if (last_version.last_upload != str_to_time(__DATE__, __TIME__)) {
    last_version.last_upload = str_to_time(__DATE__, __TIME__);
    last_version.version_number ++;
    EEPROM.put(0, last_version);
  }
}
void PrintVersion() {
  Version last_version;
  EEPROM.get(0, last_version);
  Serial.print("Project Name : ");
  Serial.println(project_name);
  Serial.print("Version: ");
  Serial.println(last_version.version_number);
  Serial.print("Last Upload: ");
  printTime(last_version.last_upload);
}

