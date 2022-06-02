// ----------------------------------------------------------------------------------------------------------
// RFID
// ----------------------------------------------------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>

/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

// ----------------------------------------------------------------------------------------------------------

enum RFID_PINS
{
  RST_PIN = 22,
  SS_PIN  =  5
};

// ----------------------------------------------------------------------------------------------------------

inline void rfid_setup(MFRC522* instance)
{
  SPI.begin();
  instance->PCD_Init();
  delay(4);
  instance->PCD_DumpVersionToSerial();
}

// ----------------------------------------------------------------------------------------------------------

inline bool rfid_is_idle(MFRC522* instance)
{
  if (!instance->PICC_IsNewCardPresent())
  {
    return true;
  }

  if (!instance->PICC_ReadCardSerial())
  {
    return true;
  }

  return false;
}

// ----------------------------------------------------------------------------------------------------------

inline unsigned int rfid_read(MFRC522* instance)
{
  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  unsigned int card = 0;

  card =  instance->uid.uidByte[0] << 24;
  card += instance->uid.uidByte[1] << 16;
  card += instance->uid.uidByte[2] << 8;
  card += instance->uid.uidByte[3];

  return card;
}

// ----------------------------------------------------------------------------------------------------------

#define skip_if_idle(instance)  \
  if (rfid_is_idle(&instance))  \
  {                             \
    return;                     \
  }                             \

// ----------------------------------------------------------------------------------------------------------
