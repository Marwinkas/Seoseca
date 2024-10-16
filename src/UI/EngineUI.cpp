#include "EngineUI.h"
#include <string>
#include <iostream>
bool pressed = false;
bool addupdate = false;
float mousex = 0;
float mousey = 0;
float buttonposx = 0;
float buttonposy = 0;
float buttonsizex = 0;
float buttonsizey = 0;
int addbuttonsize = 0;

gui::Button *buttonmini(string &text) {
  auto *button = new gui::Button(text);

  button->setSize(button->m_box.getSize().x + 5, button->m_box.getSize().y);

  button->m_box.centerTextHorizontally(button->m_box.item());

  return button;
}
void EditScaleButtonsPosition(gui::Button *editbutton[],
                              gui::Button *testbutton) {
  sf::Vector2f position = testbutton->getPosition();
  sf::Vector2f scale = testbutton->getSize();
  sf::Vector2f editscale = editbutton[0]->getSize();

  float offsetX = position.x - editscale.x;
  float offsetY = position.y - editscale.y;

  editbutton[0]->setPosition(offsetX, offsetY);
  editbutton[1]->setPosition(offsetX, position.y + scale.y);
  editbutton[2]->setPosition(position.x + scale.x, offsetY);
  editbutton[3]->setPosition(position.x + scale.x, position.y + scale.y);
}
int selectedobj = 0;
void ScaleButtonFunction(gui::Button *scalebutton[], gui::Button *button,
                         sf::RenderWindow &window, gui::Layout *layer) {
  float currentMouseX = sf::Mouse::getPosition(window).x;
  float currentMouseY = sf::Mouse::getPosition(window).y;
  if (mousex == 0) {
    mousex = currentMouseX;
    mousey = currentMouseY;
    buttonposx = button->getPosition().x;
    buttonposy = button->getPosition().y;
    buttonsizex = button->getSize().x;
    buttonsizey = button->getSize().y;
  }

  float mouseDeltaX = currentMouseX - mousex;
  float mouseDeltaY = currentMouseY - mousey;

  Vector2 pos = button->getPosition();
  Vector2 scale = button->getSize();

  if (scalebutton[0]->isFocused()) {
    scale.x = std::max(0.f, buttonsizex - mouseDeltaX);
    scale.y = std::max(0.f, buttonsizey - mouseDeltaY);
    pos.x = buttonposx + mouseDeltaX;
    pos.y = buttonposy + mouseDeltaY;
  } else if (scalebutton[1]->isFocused()) {
    scale.x = std::max(0.f, buttonsizex - mouseDeltaX);
    scale.y = std::max(0.f, buttonsizey + mouseDeltaY);
    pos.x = buttonposx + mouseDeltaX;
  } else if (scalebutton[2]->isFocused()) {
    scale.x = std::max(0.f, buttonsizex + mouseDeltaX);
    scale.y = std::max(0.f, buttonsizey - mouseDeltaY);
    pos.y = buttonposy + mouseDeltaY;
  } else if (scalebutton[3]->isFocused()) {
    scale.x = std::max(0.f, buttonsizex + mouseDeltaX);
    scale.y = std::max(0.f, buttonsizey + mouseDeltaY);
  } else if (button->isFocused()) {
    pos.x = buttonposx + mouseDeltaX;
    pos.y = buttonposy + mouseDeltaY;
  }

  Vector2 layerscale = layer->getSize();
  scale.x = std::min(scale.x, layerscale.x - 60);
  scale.y = std::min(scale.y, layerscale.y - 60);

  Vector2 layerpos = layer->getPosition();
  pos.x = std::max(layerpos.x + 30,
                   std::min(pos.x, layerpos.x + layerscale.x - scale.x - 30));
  pos.y =
      std::max(30.f, std::min(pos.y, layerpos.y + layerscale.y - scale.y - 30));

  button->setSize(scale.x, scale.y);
  button->m_box.centerTextHorizontallyVertically(button->m_box.item());
  button->setPosition(pos.x, pos.y);

  EditScaleButtonsPosition(scalebutton, button);
}
void resetbutton(gui::SpriteButton *button[]) {
  for (int i = 0; i < 500; i++) {
    if (button[i] != nullptr) {
      button[i]->selected = false;
      button[i]->background.setTexture(button[i]->backgrounddefault);
    }
  }
}
string MenuButtonsName[] = {"File", "Edit", "Window"};

void EngineUI(sf::RenderWindow *window, sf::RenderWindow &renderwindow) {
  Menu menu(renderwindow);
  window->setActive(true);

  sf::Text text("Hello world!", gui::Theme::getFont());
  text.setOrigin(text.getLocalBounds().width / 2,
                 text.getLocalBounds().height / 2);
  text.setPosition(480, 240);

  gui::Button *selectedobject = new gui::Button("");
  gui::Button *buttoned[500] = {nullptr};
  gui::SpriteButton *insbuttoned[500] = {nullptr};

  Theme::textSize = 14;
  Theme::MARGIN = 0;

  gui::Layout *EnginePanel = menu.addLayout();
  EnginePanel->orientation = Vertical;
  EnginePanel->setSize(1920, 1080);
  sf::Texture panelimage;
  panelimage.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/upperpanel.png");
  gui::Layout *PanelMenu = EnginePanel->addLayout();
  PanelMenu->orientation = Horizontal;
  PanelMenu->setSize(1920, 50);
  PanelMenu->padding.left = 10;
  PanelMenu->havebackground = true;
  PanelMenu->background.setTexture(panelimage);
  PanelMenu->recomputeGeometry();

  gui::Layout *EngineMenu = EnginePanel->addLayout();
  EngineMenu->orientation = Horizontal;
  EngineMenu->setSize(1920, 1030);

  gui::Layout *InspectorMenu = EngineMenu->addLayout();
  InspectorMenu->orientation = Vertical;
  InspectorMenu->setSize(390, 970);

  gui::Layout *InspectorMenuMenu = InspectorMenu->addLayout();
  InspectorMenuMenu->orientation = Horizontal;
  InspectorMenuMenu->setSize(400, 0);

  sf::Texture addimage;
  addimage.loadFromFile("/home/marwinkas/Desktop/marwinkaengine/add.png");

  gui::SpriteButton *addbutton = new gui::SpriteButton(addimage, "", 50, 50);

  addbutton->backgroundclick.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/addclick.png");
  addbutton->backgroundhover.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/addhover.png");
  addbutton->backgrounddefault.loadFromFile(
      "/home/marwinkas/Desktop/marwinkaengine/add.png");
  addbutton->setSize(50, 50);

  PanelMenu->add(addbutton);
  PanelMenu->recomputeGeometry();

  gui::Layout *WindowMenu = EngineMenu->addLayout();
  WindowMenu->orientation = Vertical;

  gui::Layout *WindowMenuMenu = WindowMenu->addLayout();
  WindowMenuMenu->orientation = Vertical;

  gui::Layout *WindowMenuOverview = WindowMenu->addLayout();
  WindowMenuOverview->orientation = None;
  WindowMenuOverview->setSize(1920 - 800, 1080);

  gui::Layout *SettingsMenu = EngineMenu->addLayout();
  SettingsMenu->orientation = Vertical;
  SettingsMenu->setSize(390, 970);

  gui::FormLayout *SettingsFormMenu = SettingsMenu->addFormLayout();
  SettingsFormMenu->orientation = Vertical;
  SettingsFormMenu->setSize(390, 970);

    gui::FormLayout *SettingsFormMenu2 = SettingsMenu->addFormLayout();
  SettingsFormMenu2->orientation = Vertical;
  SettingsFormMenu2->setSize(390, 970);
  sf::Texture background;

  background.loadFromFile("/home/marwinkas/Desktop/marwinkaengine/panels.png");
  SettingsMenu->havebackground = true;
  SettingsMenu->background.setTexture(background);
  SettingsMenu->padding = Vector2(5, 5);
  SettingsMenu->recomputeGeometry();

  InspectorMenu->padding = Vector2(5, 5);
  InspectorMenu->havebackground = true;
  InspectorMenu->background.setTexture(background);
  InspectorMenu->recomputeGeometry();

  gui::Button *editbutton[4];
  for (int i = 0; i < 4; i++) {
    editbutton[i] = new gui::Button("");
    editbutton[i]->m_box.setSize(30, 30);
    editbutton[i]->setSize(30, 30);
    WindowMenuOverview->add(editbutton[i]);
  }

  addbutton->setCallback([&] {
    sf::Texture addimage;
    addimage.loadFromFile("/home/marwinkas/Desktop/marwinkaengine/btn.png");
    gui::SpriteButton *inspectornewbtn = new gui::SpriteButton(
        addimage, "test",
        InspectorMenu->getSize().x - InspectorMenu->margin.left -
            InspectorMenu->margin.right - InspectorMenu->padding.left -
            InspectorMenu->padding.right,
        30);
    inspectornewbtn->background.setTexture(inspectornewbtn->backgrounddefault);
    inspectornewbtn->backgroundclick.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnclicked.png");
    inspectornewbtn->backgroundhover.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnhover.png");
    inspectornewbtn->backgrounddefault.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btn.png");
    inspectornewbtn->backgroundselected.loadFromFile(
        "/home/marwinkas/Desktop/marwinkaengine/btnselected.png");
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
    addupdate = true;
  });
  gui::TextBox *textbox2 = new gui::TextBox();
  textbox2->setText("Hello world!");
  textbox2->setCallback(
      [&editbutton, &selectedobject, &textbox2, &buttoned,
                         &insbuttoned] {
    
    try {
      string da = textbox2->getText();
      int value = std::stoi(da);
      buttoned[selectedobj]->setPosition(buttoned[selectedobj]->getSize().x,
                                         value);
    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition(editbutton, selectedobject);
      });

  gui::TextBox *textbox3 = new gui::TextBox();
  textbox3->setText("Hello world!");
  textbox3->setCallback([&editbutton, &selectedobject, &textbox3, &buttoned,
                         &insbuttoned] {
    
    try {
      string da = textbox3->getText();
      int value = std::stoi(da);
      buttoned[selectedobj]->setPosition(
                                         value,buttoned[selectedobj]->getSize().y);
    } catch (const std::invalid_argument &e) {
      std::cerr << "Ошибка: введено не число." << std::endl;
    } catch (const std::out_of_range &e) {
      std::cerr << "Ошибка: число вне допустимого диапазона." << std::endl;
    }
    EditScaleButtonsPosition(editbutton, selectedobject);
  });
  textbox2->setPlaceholder("Type something!");
  SettingsFormMenu->addRow("Coordinates", textbox2, textbox3);

  gui::TextBox *textbox = new gui::TextBox();
  textbox->setText("Hello world!");
  textbox->setCallback([&textbox, &buttoned, &insbuttoned] {
    buttoned[selectedobj]->setString(textbox->getText());
    insbuttoned[selectedobj]->setString(textbox->getText());
  });
  textbox->setPlaceholder("Type something!");
  SettingsFormMenu2->addRow("Name", textbox);

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      menu.onEvent(event);
      if (event.type == sf::Event::Closed)
        window->close();

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left)
        pressed = true;
      else if (event.type == sf::Event::MouseButtonReleased &&
               event.mouseButton.button == sf::Mouse::Left)
        pressed = false;

      if (pressed) {
        ScaleButtonFunction(editbutton, selectedobject, renderwindow,
                            WindowMenuOverview);
      } else if (mousex != 0) {
        mousex = mousey = buttonposx = buttonposy = buttonsizex = buttonsizey =
            0;
      }

      if (addupdate) {
        for (int i = 0; i < 500; i++) {
          if (buttoned[i] != nullptr) {
            auto button = buttoned[i];
            SpriteButton *button2 = insbuttoned[i];
            buttoned[i]->setCallback([&editbutton, &selectedobject, button,
                                      button2, &insbuttoned, &textbox,&textbox2,&textbox3, i] {
              resetbutton(insbuttoned);
              button2->selected = true;
              button2->background.setTexture(button2->backgroundselected);
              selectedobject = button;
              selectedobj = i;
              textbox->setText(button->getString());
              textbox2->setText(to_string(button->getPosition().x));
              textbox3->setText(to_string(button->getPosition().y));
              EditScaleButtonsPosition(editbutton, selectedobject);
            });
            insbuttoned[i]->setCallback([&editbutton, &selectedobject, button,
                                         button2, &insbuttoned, &textbox, i,&textbox2,&textbox3] {
              resetbutton(insbuttoned);
              button2->selected = true;
              button2->background.setTexture(button2->backgroundselected);
              selectedobject = button;
              selectedobj = i;
              textbox->setText(button->getString());
                            textbox2->setText(to_string(button->getPosition().x));
              textbox3->setText(to_string(button->getPosition().y));
              EditScaleButtonsPosition(editbutton, selectedobject);
            });
          }
        }
        addupdate = false;
      }
    }

    window->clear(Theme::windowBgColor);
    window->draw(menu);
    window->display();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}