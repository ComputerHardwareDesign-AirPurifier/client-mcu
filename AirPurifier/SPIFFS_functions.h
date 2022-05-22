/////////////////////
#define FS_NO_GLOBALS
#include <FS.h>
#include <SPIFFS.h>
/////////////////////

void listAllFiles() {
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.print("FILE: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }

}

void SPIFFS_init() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("\n\n----Listing files before format----");
  listAllFiles();
}

void SPIFFS_format() {
  bool formatted = SPIFFS.format();
  if (formatted) {
    Serial.println("\n\nSuccess formatting");
  } else {
    Serial.println("\n\nError formatting");
  }
  Serial.println("\n\n----Listing files after format----");
  listAllFiles();
}
