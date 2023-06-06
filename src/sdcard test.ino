#include <M5Stack.h>
 
//Micro SD / TF Card Test

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){

    // Print blank line on screen
    M5.Lcd.printf(" \n  ");
    M5.Lcd.printf(" \n  ");
    
    Serial.printf("Listing directory: %s\n", dirname);
    M5.Lcd.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        M5.Lcd.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        M5.Lcd.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            M5.Lcd.print("  DIR : ");
            Serial.println(file.name());
            M5.Lcd.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            M5.Lcd.print("  FILE: ");
            Serial.print(file.name());
            M5.Lcd.print(file.name());
            Serial.print("  SIZE: ");
            M5.Lcd.print("  SIZE: ");
            Serial.println(file.size());
            M5.Lcd.println(file.size());
        }
        file = root.openNextFile();
    }
}

void readFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\n", path);
    M5.Lcd.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        M5.Lcd.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    M5.Lcd.print("Read from file: ");
    while(file.available()){
        int ch = file.read();
        Serial.write(ch);
        M5.Lcd.write(ch);
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);
    M5.Lcd.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        M5.Lcd.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
        M5.Lcd.println("File written");
    } else {
        Serial.println("Write failed");
        M5.Lcd.println("Write failed");
    }
}

// the setup routine runs once when M5Stack starts up

void setup() { 
 
    // initialize the M5Stack object
    M5.begin();

    // M5.startupLogo();
    Wire.begin();

    // Lcd display
    M5.Lcd.setBrightness(100);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);

    // Page Header
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 05);
    M5.Lcd.printf("           Testing Micro SD Card Functions:\r\n");
    // digitalWrite(TFT_CS, 1);
 
    // Print blank line on screen
    M5.Lcd.printf(" \n    ");
    M5.Lcd.printf(" \n    ");
    
    listDir(SD, "/", 0);
    M5.Lcd.printf("");
    M5.Lcd.printf("");

    // Print blank line on screen
    M5.Lcd.printf(" \n  ");
    M5.Lcd.printf(" \n  ");
    
    writeFile(SD, "/hello.txt", "Hello world from M5Stack !!");
    M5.Lcd.printf("");
    M5.Lcd.printf("");

    // Print blank line on screen
    M5.Lcd.printf(" \n  ");
    M5.Lcd.printf(" \n  ");

    // Print blank line on screen
    M5.Lcd.printf(" \n  ");
    M5.Lcd.printf(" \n  ");
    
    readFile(SD, "/hello.txt");
}

void loop() {

  // put your main code here, to run repeatedly:
   
    M5.update();
}