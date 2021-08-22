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
  buttonManager.setup();

  playlistButton = buttonManager.addButton(80, 120, handler);
  playlist2Button = buttonManager.addButton(160, 200, handler);

  //playlist1and2Buttons = buttonManager.addButton(230, 260, handler);

  nextSongButton = buttonManager.addButton(290, 350, handler);
  prevSongButton = buttonManager.addButton(480, 540, handler);
  //nextAndPrevButtons = buttonManager.addButton(570, 610, handler);
  volumeDownButton = buttonManager.addButton(620, 750, handler);
  volumeUpButton = buttonManager.addButton(940, 1024, handler);
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
