#include "Arduino.h"
#include "ButtonManager.h"

ButtonManager buttonManager(PIN_A0);

int playlistButton;
int playlist2Button;
int nextSongButton;
int volumeUpButton;
int volumeDownButton;
int prevSongButton;

void buttonUp(int button)
{
  if (button == nextSongButton)
    Serial.println("NEXT SONG");

  if (button == volumeUpButton)
    Serial.println("VOLUME UP");

  if (button == volumeDownButton)
    Serial.println("VOLUME DOWN");

  if (button == prevSongButton)
    Serial.println("PREV SONG");

  if (button == playlistButton)
    Serial.println("PLAYLIST 1");

  if (button == playlist2Button)
    Serial.println("PLAYLIST 2");
}

void handler(bool down, int buttonId)
{
  if (!down)
    buttonUp(buttonId);
}

void setupButtons()
{
  buttonManager.begin();

  // Pin is connected to ground through a 100kOhm resistor (R0).
  // Each button is connected to the pin and the 5V through a resistor (R1) of different values.
  // The low and high value are close to: 1024 * (1 - R1 / (R0 + R1))

  playlistButton = buttonManager.addButton(80, 120, handler); // 1MOhm
  playlist2Button = buttonManager.addButton(160, 200, handler); // 470kOhm
  nextSongButton = buttonManager.addButton(290, 350, handler); // 220kOhm
  prevSongButton = buttonManager.addButton(480, 540, handler); // 100kOhm
  volumeDownButton = buttonManager.addButton(620, 750, handler); // 47kOhm
  volumeUpButton = buttonManager.addButton(940, 1024, handler); // 1kOhm
  
  // It's also possible to detect when 2 buttons are pressed simultaneously since it creates a new resistance value
  //playlist1and2Buttons = buttonManager.addButton(230, 260, handler);
  //nextAndPrevButtons = buttonManager.addButton(570, 610, handler);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("initializing...");

  setupButtons();
}

void loop()
{
  buttonManager.loop();
  delay(1);
}
