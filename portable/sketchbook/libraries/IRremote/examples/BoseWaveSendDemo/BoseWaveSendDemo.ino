/*
 * Based on IRremote: IRsendDemo by Ken Shirriff
 *
 * Prompt user for a code to send.  Make sure your 940-950nm IR LED is
 * connected to the default digital output.  Place your Bose Wave Radio
 * CD in the line of sight of your LED, and send commands!
 */
#include <IRremote.h>


    //......................................................................
    //
    //                       Bose Wave Radio CD Remote Control
    //                    |-------------------------------------|
    //                    |   On/Off        Sleep       VolUp   |
    //                    |   Play/Pause    Stop       VolDown  |
    //                    |      FM          AM          Aux    |
    //                    |   Tune Down    Tune Up       Mute   |
    //                    |       1           2           3     |
    //                    |       4           5           6     |
    //                    |-------------------------------------|
#define BOSE_CMD_ON_OFF     0x00
#define BOSE_CMD_MUTE       0x01
#define BOSE_CMD_VOL_UP     0x02
#define BOSE_CMD_VOL_DOWN   0x03
#define BOSE_CMD_PRESET_6   0x04
#define BOSE_CMD_SLEEP      0x05
#define BOSE_CMD_FM         0x06
#define BOSE_CMD_AUX        0x07
#define BOSE_CMD_AM         0x08
#define BOSE_CMD_PLAY_PAUSE 0x09
#define BOSE_CMD_STOP       0x0A
#define BOSE_CMD_TUNE_UP    0x0B
#define BOSE_CMD_TUNE_DOWN  0x0C
#define BOSE_CMD_PRESET_1   0x0D
#define BOSE_CMD_PRESET_2   0x0E
#define BOSE_CMD_PRESET_3   0x0F
#define BOSE_CMD_PRESET_4   0x10
#define BOSE_CMD_PRESET_5   0x11

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

bool prompt;
void menu();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL) || defined(ARDUINO_attiny3217)
    delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

#if defined(USE_SOFT_SEND_PWM) || defined(USE_NO_SEND_PWM)
    IrSender.begin(IR_SEND_PIN, true); // Specify send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(true); // Enable feedback LED at default feedback LED pin
#endif

    prompt = true;
}



void loop() {
    if (prompt) {
        prompt = false;
        menu();
    }

    if (Serial.available()) {
        int answer = Serial.read();
        prompt = true;
        if (answer == -1) {
            delay(300);
        } else if (answer == 48) {    // 0
            IrSender.sendBoseWave(BOSE_CMD_ON_OFF);  // On/Off
        } else if (answer == 49) {    // 1
            IrSender.sendBoseWave(BOSE_CMD_VOL_UP);  // Volume Up
        } else if (answer == 50) {    // 2
            IrSender.sendBoseWave(BOSE_CMD_VOL_DOWN);  // Volume Down
        } else if (answer == 51) {    // 3
            IrSender.sendBoseWave(BOSE_CMD_TUNE_UP);  // Tune Up
        } else if (answer == 52) {    // 4
            IrSender.sendBoseWave(BOSE_CMD_TUNE_DOWN);  // Tune Down
        } else if (answer == 53) {    // 5
            IrSender.sendBoseWave(BOSE_CMD_AM);  // AM
        } else if (answer == 54) {    // 6
            IrSender.sendBoseWave(BOSE_CMD_FM);  // FM
        } else if (answer == 55) {    // 7
            IrSender.sendBoseWave(BOSE_CMD_PRESET_1);  // Preset 1
        } else if (answer == 56) {    // 8
            IrSender.sendBoseWave(BOSE_CMD_PRESET_2);  // Preset 2
        } else if (answer == 57) {    // 9
            IrSender.sendBoseWave(BOSE_CMD_PRESET_3);  // Preset 3
        } else if (answer == 97) {    // a
            IrSender.sendBoseWave(BOSE_CMD_PRESET_4);  // Preset 4
        } else if (answer == 98) {    // b
            IrSender.sendBoseWave(BOSE_CMD_PRESET_5);  // Preset 5
        } else if (answer == 99) {    // c
            IrSender.sendBoseWave(BOSE_CMD_PRESET_6);  // Preset 6
        } else if (answer == 100) {   // d
            IrSender.sendBoseWave(BOSE_CMD_MUTE);  // Mute
        } else if (answer == 101) {   // e
            IrSender.sendBoseWave(BOSE_CMD_PLAY_PAUSE);  // Pause
        } else if (answer == 102) {   // f
            IrSender.sendBoseWave(BOSE_CMD_STOP);  // Stop
        } else if (answer == 103) {   // g
            IrSender.sendBoseWave(BOSE_CMD_AUX);  // Aux
        } else if (answer == 104) {   // h
            IrSender.sendBoseWave(BOSE_CMD_SLEEP);  // Sleep
        } else {
            prompt = false;
        }
        delay(300);
    }
}

void menu() {
    Serial.println("0:  On / Off");
    Serial.println("1:  Volume Up");
    Serial.println("2:  Volume Down");
    Serial.println("3:  Tune Up");
    Serial.println("4:  Tune Down");
    Serial.println("5:  AM");
    Serial.println("6:  FM");
    Serial.println("7:  Preset 1");
    Serial.println("8:  Preset 2");
    Serial.println("9:  Preset 3");
    Serial.println("a:  Preset 4");
    Serial.println("b:  Preset 5");
    Serial.println("c:  Preset 6");
    Serial.println("d:  Mute");
    Serial.println("e:  Play/Pause");
    Serial.println("f:  Stop");
    Serial.println("g:  Aux");
    Serial.println("h:  Sleep");
}
