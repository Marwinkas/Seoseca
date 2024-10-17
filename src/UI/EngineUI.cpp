#include "EngineUI.h"
#include <iostream>
#include <string>

bool pressed = false;

bool ctrlpressed = false;
bool addupdate = false;
int ctrlvalue = 1;
float mousex = 0;
float mousey = 0;
float usedmousedx = 0;
float usedmousedy = 0;
float buttonposx[50] = {0};
float buttonposy[50] = {0};
float buttonsizex[50] = {0};
float buttonsizey[50] = {0};
int addbuttonsize = 0;
int selectedobject[50] = {0};
int selectedcount = 0;
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Create New Project",
                        sf::Style::Default);
sf::Text text("Hello world!", gui::Theme::getFont());
sf::Texture background;

Menu *EngineUIMenu = new Menu(window);
Menu *EngineUIMenu2 = new Menu(window);
gui::Layout *EnginePanel2 =
    EngineUIMenu2->addLayout(Vertical, Vector2(1920, 1080));
gui::Layout *EnginePanel =
    EngineUIMenu->addLayout(Vertical, Vector2(1920, 1080));
gui::Layout *PanelMenu = EnginePanel->addLayout(Horizontal, Vector2(1920, 50));
gui::Layout *EngineMenu =
    EnginePanel->addLayout(Horizontal, Vector2(1920, 1030));
gui::Layout *InspectorMenu =
    EngineMenu->addLayout(Vertical, Vector2(390, 1030));
gui::Layout *WindowMenu = EngineMenu->addLayout(Vertical, Vector2(1120, 1030));
gui::Layout *WindowMenuMenu = WindowMenu->addLayout(Vertical, Vector2(1120, 0));
gui::Layout *WindowMenuOverview =
    WindowMenu->addLayout(None, Vector2(1120, 1030));
gui::Layout *SettingsMenu = EngineMenu->addLayout(Vertical, Vector2(390, 1030));
gui::FormLayout *SettingsFormMenu =
    SettingsMenu->addFormLayout(Vector2(390, 1030));
gui::FormLayout *SettingsFormMenu2 =
    SettingsMenu->addFormLayout(Vector2(390, 1030));
gui::FormLayout *SettingsFormMenu3 =
    SettingsMenu->addFormLayout(Vector2(390, 1030));
gui::Button *buttoned[500] = {nullptr};
gui::SpriteButton *insbuttoned[500] = {nullptr};
gui::SpriteButton *addbutton = new gui::SpriteButton(
    "/home/marwinkas/Desktop/marwinkaengine/add.png", "", 50, 50);
gui::Button *editbutton[50] = {nullptr};

gui::TextBox *textbox = {nullptr};
gui::TextBox *textbox2 = {nullptr};
gui::TextBox *textbox3 = {nullptr};
gui::TextBox *textbox4 = {nullptr};
gui::TextBox *textbox5 = {nullptr};
gui::Button *buttonmini(string &text) {
  auto *button = new gui::Button(text);

  button->setSize(button->m_box.getSize().x + 5, button->m_box.getSize().y);

  button->m_box.centerTextHorizontally(button->m_box.item());

  return button;
}

void EditScaleButtonsPosition() {

  for (int i = 0; i < selectedcount; i++) {

    if (buttoned[selectedobject[i]] != nullptr) {

      gui::Button &button = *buttoned[selectedobject[i]];
      sf::Vector2f position = button.getAbsolutePosition();
      sf::Vector2f scale = button.getSize();
      int a = i * 4;

      if (editbutton[i * 4] == nullptr)
        for (int g = a; g < a + 4; g++) {
          editbutton[g] = new gui::Button("");
          editbutton[g]->m_box.setSize(30, 30);
          editbutton[g]->setSize(30, 30);

          EnginePanel2->add(editbutton[g]);
        }

      auto &scalebutton = *editbutton[i * 4];

      sf::Vector2f editscale = scalebutton.getSize();
      float offsetX = position.x - editscale.x;
      float offsetY = position.y - editscale.y;

      if (editbutton[i * 4] != nullptr)
        editbutton[i * 4]->setPosition(offsetX, offsetY);
      if (editbutton[i * 4 + 1] != nullptr)
        editbutton[i * 4 + 1]->setPosition(offsetX, position.y + scale.y);
      if (editbutton[i * 4 + 2] != nullptr)
        editbutton[i * 4 + 2]->setPosition(position.x + scale.x, offsetY);
      if (editbutton[i * 4 + 3] != nullptr)
        editbutton[i * 4 + 3]->setPosition(position.x + scale.x,
                                           position.y + scale.y);
    }
  }
  gui::Button &button = *buttoned[selectedobject[selectedcount - 1]];
  textbox->setText(button.getString());
  textbox2->setText(to_string(button.getPosition().x));
  textbox3->setText(to_string(button.getPosition().y));
  textbox4->setText(to_string(button.getSize().x));
  textbox5->setText(to_string(button.getSize().y));
}

void ScaleButtonFunction() {
  float mouseDeltaX = sf::Mouse::getPosition(window).x - mousex;
  float mouseDeltaY = sf::Mouse::getPosition(window).y - mousey;

  for (int i = 0; i < selectedcount; i++) {

    if (buttoned[selectedobject[i]] != nullptr) {

      auto &button = *buttoned[selectedobject[i]];
      Vector2 pos = button.getPosition();
      Vector2 scale = button.getSize();

      auto &scalebutton = *editbutton[i * 4];
      auto &scalebutton2 = *editbutton[i * 4 + 1];
      auto &scalebutton3 = *editbutton[i * 4 + 2];
      auto &scalebutton4 = *editbutton[i * 4 + 3];
      if (ctrlpressed)
        ctrlvalue = 10;
      else
        ctrlvalue = 1;

      if (scalebutton.isFocused()) {
        scale.x = std::max(5.f, button.getSize().x - mouseDeltaX + usedmousedx);
        scale.y = std::max(5.f, button.getSize().y - mouseDeltaY + usedmousedy);

        pos.x = button.getPosition().x + mouseDeltaX - usedmousedx;
        pos.y = button.getPosition().y + mouseDeltaY - usedmousedy;
        usedmousedx = mouseDeltaX;
        usedmousedy = mouseDeltaY;
        button.setSize(scale.x, scale.y);
        button.setPosition(pos);

      } else if (scalebutton2.isFocused()) {
        scale.x = std::max(5.f, button.getSize().x - mouseDeltaX + usedmousedx);
        scale.y = std::max(5.f, button.getSize().y + mouseDeltaY - usedmousedy);
        pos.x = button.getPosition().x + mouseDeltaX - usedmousedx;
        usedmousedx = mouseDeltaX;
        usedmousedy = mouseDeltaY;
        button.setSize(scale.x, scale.y);
        button.setPosition(pos);
      } else if (scalebutton3.isFocused()) {
        scale.x = std::max(5.f, button.getSize().x + mouseDeltaX - usedmousedx);
        scale.y = std::max(5.f, button.getSize().y - mouseDeltaY + usedmousedy);
        pos.y = button.getPosition().y + mouseDeltaY - usedmousedy;
        usedmousedx = mouseDeltaX;
        usedmousedy = mouseDeltaY;
        button.setSize(scale.x, scale.y);
        button.setPosition(pos);
      } else if (scalebutton4.isFocused()) {

        scale.x = button.getSize().x + mouseDeltaX - usedmousedx;
        scale.y = button.getSize().y + mouseDeltaY - usedmousedy;
        usedmousedx = mouseDeltaX;
        usedmousedy = mouseDeltaY;
        button.setSize(scale.x, scale.y);
        button.setPosition(pos);
      }

      else if (button.isFocused()) {
        for (int g = 0; g < selectedcount; g++) {

          gui::Button &button = *buttoned[selectedobject[g]];
          pos.x = button.getPosition().x + mouseDeltaX - usedmousedx;
          pos.y = button.getPosition().y + mouseDeltaY - usedmousedy;
          button.setPosition(pos);
        }
        usedmousedx = mouseDeltaX;
        usedmousedy = mouseDeltaY;
      }

      button.m_box.centerTextHorizontallyVertically(button.m_box.item());
      EditScaleButtonsPosition();

    }
  }
}
void resetbutton() {
  for (int i = 0; i < 500; i++) {

    if (insbuttoned[i] != nullptr) {
      auto &button = *insbuttoned[i];
      button.selected = false;
      button.background.setTexture(button.backgrounddefault);
    }
  }
}

void updatelistbutton() {
  for (int i = 0; i < 500; i++) {
    if (buttoned[i] != nullptr && insbuttoned[i] != nullptr) {
      auto &button = *buttoned[i];
      auto &button2 = *insbuttoned[i];
      button.setCallback([&button, &button2, i] {
        if (ctrlpressed) {
            int selectedIndex = 0;
            bool found = false;
            for (int g = 0; g < selectedcount; g++) {
              if (selectedobject[g] == i) {
                found = true;
                selectedIndex = g; // Save the index for removal
                break;             // Exit the loop early once found
              }
            }
            if (!found) {
              selectedobject[selectedcount] = i;
              selectedcount++;
              button2.selected = true;
              button2.background.setTexture(button2.backgroundselected);
            }
            else {
              for (int d = selectedIndex; d < selectedcount - 1; d++) {
                selectedobject[d] = selectedobject[d + 1]; // Shift left
              }
              selectedcount--;
              button2.selected = false;
              button2.background.setTexture(button2.backgrounddefault);
            }

            EnginePanel2->reset();
            for (int i = 0; i < 50; i++) {
              editbutton[i] = {nullptr};
            }
            EditScaleButtonsPosition();
            
          }

        if (!button2.selected && !ctrlpressed) {
           {
            bool da = false;
            for (int g = 0; g < selectedcount; g++) {
              if (selectedobject[g] == i) {
                da = true;
              }
            }
            if (!da) {
              selectedobject[0] = i;
              selectedcount = 0;
              resetbutton();
              EnginePanel2->reset();
              for (int i = 0; i < 50; i++) {
                editbutton[i] = {nullptr};
              }
              EditScaleButtonsPosition();
            }
            selectedcount++;
            button2.selected = true;
            button2.background.setTexture(button2.backgroundselected);
          }
        }

        
        

        EditScaleButtonsPosition();
      });

      button2.setCallback([&button, &button2, i] {
        resetbutton();
        button2.selected = true;
        button2.background.setTexture(button2.backgroundselected);
        if (ctrlpressed)
          selectedobject[selectedcount] = i;
        else {
          selectedcount = 0;
          selectedobject[0] = i;
        }
        selectedcount++;

        EditScaleButtonsPosition();
      });
    }
  }
}
void EngineUI() {
  Theme::textSize = 14;

  EnginePanel->orientation = Vertical;

  sf::Texture panelimage;
  panelimage.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/upperpanel.png");

  PanelMenu->padding.left = 10;
  PanelMenu->havebackground = true;
  PanelMenu->background.setTexture(panelimage);
  PanelMenu->recomputeGeometry();

  addbutton->backgroundclick.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/addclick.png");
  addbutton->backgroundhover.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/addhover.png");
  addbutton->backgrounddefault.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/add.png");
  addbutton->backgroundselected.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/addclick.png");
  addbutton->background.setTexture(addbutton->backgrounddefault);

  PanelMenu->add(addbutton);

  background.loadFromFile("/home/marwinkas/Desktop/marwinkaengine/panels.png");
  SettingsMenu->havebackground = true;
  SettingsMenu->background.setTexture(background);
  SettingsMenu->padding = Vector2(5, 5);
  SettingsMenu->recomputeGeometry();

  InspectorMenu->padding = Vector2(5, 5);
  InspectorMenu->havebackground = true;
  InspectorMenu->background.setTexture(background);
  InspectorMenu->recomputeGeometry();

  textbox2 = new gui::TextBox();
  textbox2->setText("");
  textbox2->setCallback([] {
    try {
      string da = textbox2->getText();
      float value = std::stof(da);

    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition();
  });

  textbox3 = new gui::TextBox();
  textbox3->setText("");
  textbox3->setCallback([] {
    try {
      string da = textbox3->getText();
      float value = std::stof(da);

    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition();
  });

  textbox2->setPlaceholder("");
  textbox2->setSize(100, 25);
  textbox3->setSize(100, 25);

  textbox2->m_box.setSize(100, 25);
  textbox3->m_box.setSize(100, 25);
  SettingsFormMenu2->addRow("Coordinates", textbox2, textbox3);

  textbox = new gui::TextBox();
  textbox->setText("");
  textbox->setCallback([] {
    buttoned[selectedobject[sizeof(selectedobject) / sizeof(selectedobject[0])]]
        ->setString(textbox->getText());
    insbuttoned[selectedobject[sizeof(selectedobject) /
                               sizeof(selectedobject[0])]]
        ->setString(textbox->getText());
  });
  textbox->setPlaceholder("");
  SettingsFormMenu->addRow("Name", textbox);

  textbox4 = new gui::TextBox();
  textbox4->setText("");
  textbox4->setCallback([] {
    try {
      string da = textbox4->getText();
      float value = std::stof(da);
      buttoned[selectedobject[sizeof(selectedobject) /
                              sizeof(selectedobject[0])]]
          ->setSize(value, buttoned[selectedobject[sizeof(selectedobject) /
                                                   sizeof(selectedobject[0])]]
                               ->getSize()
                               .y);

    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition();
  });

  textbox5 = new gui::TextBox();
  textbox5->setText("");
  textbox5->setCallback([] {
    try {
      string da = textbox5->getText();
      float value = std::stof(da);
      buttoned[selectedobject[sizeof(selectedobject) /
                              sizeof(selectedobject[0])]]
          ->setSize(buttoned[selectedobject[sizeof(selectedobject) /
                                            sizeof(selectedobject[0])]]
                        ->getSize()
                        .x,
                    value);
    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition();
  });

  textbox5->setPlaceholder("");
  textbox4->setSize(100, 25);
  textbox5->setSize(100, 25);

  textbox4->m_box.setSize(100, 25);
  textbox5->m_box.setSize(100, 25);
  SettingsFormMenu3->addRow("Size:", textbox4, textbox5);

  addbutton->setCallback([&] {
    gui::SpriteButton *inspectornewbtn = new gui::SpriteButton(
        "/home/marwinkas/Desktop/marwinkaengine/btn.png", "test",
        InspectorMenu->getSize().x - InspectorMenu->margin.left -
            InspectorMenu->margin.right - InspectorMenu->padding.left -
            InspectorMenu->padding.right,
        30);

    inspectornewbtn->backgroundclick.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnclicked.png");
    inspectornewbtn->backgroundhover.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnhover.png");
    inspectornewbtn->backgrounddefault.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btn.png");
    inspectornewbtn->backgroundselected.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnselected.png");
    inspectornewbtn->background.setTexture(inspectornewbtn->backgrounddefault);
    gui::Button *addbtn = new gui::Button("Test");
    addbtn->m_box.centerTextHorizontallyVertically(addbtn->m_box.item());
    sf::Texture addimages;
    inspectornewbtn->icontext.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/buttonicon.png");
    inspectornewbtn->haveicon = true;
    inspectornewbtn->icon.setTexture(inspectornewbtn->icontext);
    inspectornewbtn->setIcon(addimages);

    WindowMenuOverview->add(addbtn);
    InspectorMenu->add(inspectornewbtn);

    inspectornewbtn->setSize(
        InspectorMenu->getSize().x - InspectorMenu->margin.left -
            InspectorMenu->margin.right - InspectorMenu->padding.left -
            InspectorMenu->padding.right,
        30);

    buttoned[addbuttonsize] = addbtn;
    insbuttoned[addbuttonsize] = inspectornewbtn;
    buttoned[addbuttonsize]->setSize(100, 100);
    addbuttonsize++;
    updatelistbutton();
  });

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      EngineUIMenu->onEvent(event);
      EngineUIMenu2->onEvent(event);
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed &&
          event.mouseButton.button == sf::Keyboard::LControl)
        ctrlpressed = true;
      else if (event.type == sf::Event::KeyReleased &&
               event.mouseButton.button == sf::Keyboard::LControl)
        ctrlpressed = false;

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left)
        pressed = true;
      else if (event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Left)
        pressed = false;

      if (pressed) {
        float currentMouseX = sf::Mouse::getPosition(window).x;
        float currentMouseY = sf::Mouse::getPosition(window).y;

        if (mousex == 0) {
          mousex = currentMouseX;
          mousey = currentMouseY;
        }
        ScaleButtonFunction();

      }

      else{



      
      for (int i = 0; i < 50; i++)
          mousex = mousey = usedmousedy = usedmousedx = 0;
      }
        
    }
    window.clear(Theme::windowBgColor);
    window.draw(*EngineUIMenu);
    window.draw(*EngineUIMenu2);
    window.display();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}