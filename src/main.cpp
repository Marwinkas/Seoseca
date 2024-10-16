// main.cpp

#include "UI/EngineUI.h"

sf::RenderWindow windows(sf::VideoMode(1920, 1080), "Seoseca",
                         sf::Style::Default);
sf::RenderWindow window2(sf::VideoMode(800, 300), "Seoseca", sf::Style::Close);
Menu menu(windows);
sf::Color hex2color(const std::string &hexcolor) {
  sf::Color color = sf::Color::Black;
  if (hexcolor.size() == 7) // #ffffff
  {
    color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
    color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
    color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
  } else if (hexcolor.size() == 4) // #fff
  {
    color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
    color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
    color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
  }
  return color;
}

FILE *f;
char Call[2048];
auto test_select_folder() {
  // Directory selection
  auto dir =
      pfd::select_folder("Select any directory", pfd::path::home()).result();
  return dir;
}
struct Themes {
  sf::Color backgroundColor;
  std::string texturePath;
};
void CreateProjectWindow(sf::RenderWindow *window) {
  Menu menu2(window2);
  window->setActive(true);
  sf::Text text("Hello world!", gui::Theme::getFont());
  text.setOrigin(text.getLocalBounds().width / 2,
                 text.getLocalBounds().height / 2);
  text.setPosition(480, 240);
  string textdirectory;
  menu2.setPosition(Vector2(20, 20));
  gui::Layout *vbox = menu2.addLayout();
  vbox->orientation = Vertical;
  gui::Layout *vbox2 = vbox->addLayout();
  vbox2->orientation = Vertical;
  gui::Layout *hbox = vbox->addLayout();
  hbox->orientation = Horizontal;
  gui::Layout *hbox2 = vbox->addLayout();
  hbox2->orientation = Horizontal;
  gui::TextBox *textbox3 = new gui::TextBox(100);

  Label *label = new Label("Project Name:");
  vbox2->add(label);
  gui::TextBox *textbox = new gui::TextBox();
  textbox->setText("");
  textbox->setSize(Vector2(460, textbox->m_box.getSize().y));
  textbox->m_box.setSize(460, textbox->m_box.getSize().y);
  textbox->setCallback([&]() {
    text.setString(textbox->getText());
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
  });
  textbox->setPlaceholder("");
  vbox2->add(textbox);

  Label *label2 = new Label("Project Path:");
  vbox2->add(label2);
  textbox3->setText("");
  textbox3->setSize(Vector2(305, textbox3->m_box.getSize().y));
  textbox3->m_box.setSize(305, textbox3->m_box.getSize().y);
  textbox3->setPlaceholder("");

  hbox->add(textbox3);
  Themes win98Theme = {hex2color("#d4d0c8"), "demo/texture-win98.png"};
  Themes defaultTheme = {hex2color("#dddbde"), "demo/texture-default.png"};

  gui::Button *buttons = new gui::Button("Browse");
  buttons->setCallback([&] {
    textdirectory = test_select_folder();
    textbox3->setText(textdirectory);
  });
  buttons->setSize(Vector2(150, buttons->m_box.getSize().y));
  buttons->m_box.setSize(150, buttons->m_box.getSize().y);
  buttons->m_box.centerTextHorizontally(buttons->m_box.item());
  hbox->add(buttons);

  gui::Button *buttons3 = new gui::Button("Create Project");
  buttons3->setCallback([&] { window->close(); });
  buttons3->setSize(Vector2(250, buttons3->m_box.getSize().y));
  buttons3->m_box.setSize(250, buttons3->m_box.getSize().y);
  buttons3->m_box.centerTextHorizontally(buttons3->m_box.item());
  hbox2->add(buttons3);

  gui::Button *buttons2 = new gui::Button("Cancel");
  buttons2->setCallback([&] { window->close(); });
  buttons2->setSize(Vector2(150, buttons2->m_box.getSize().y));
  buttons2->m_box.setSize(150, buttons2->m_box.getSize().y);
  buttons2->m_box.centerTextHorizontally(buttons2->m_box.item());

  hbox2->add(buttons2);
  buttons2->setPosition(Vector2(312, 0));
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      menu2.onEvent(event);
      if (event.type == sf::Event::Closed)
        window->close();
    }
    window->clear(Theme::windowBgColor);

    window->draw(menu2);
    window->display();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}

void renderingThread(sf::RenderWindow *window) {
  window->setActive(true);
  Themes defaultTheme = {hex2color("#1b1e20"), "demo/texture-default.png"};
  gui::Theme::loadTexture(defaultTheme.texturePath);
  gui::Theme::windowBgColor = defaultTheme.backgroundColor;

  Theme::loadFont("/home/marwinkas/Desktop/marwinkaengine/src/demo/tahoma.ttf");
  Theme::loadTexture(
      "/home/marwinkas/Desktop/marwinkaengine/src/demo/texture-default.png");
  Theme::textSize = 32;
  Theme::click.textColor = sf::Color::White;
  Theme::click.textColorHover = sf::Color::White;
  Theme::click.textColorFocus = sf::Color::White;
  Theme::click.textPlaceholderColor = sf::Color::White;
  Theme::click.textSelectionColor = Color("#585858");
  Theme::input.textColor = sf::Color::White;
  Theme::input.textColorHover = sf::Color::White;
  Theme::input.textColorFocus = sf::Color::White;
  Theme::input.textPlaceholderColor = sf::Color::White;
  Theme::input.textSelectionColor = Color("#585858");

  gui::Button *button = new gui::Button("Settings");

  button->m_box.item().setFont(Theme::getFont());
  button->m_box.item().setCharacterSize(Theme::textSize);
  button->setString("New Project");

  gui::Button *button2 = new gui::Button("Settings");

  button2->m_box.item().setFont(Theme::getFont());
  button2->m_box.item().setCharacterSize(Theme::textSize);
  button2->setString("New Project");

  gui::Layout *ProjectsMenu = menu.addLayout();
  ProjectsMenu->setSize(1620,1080 - 300);
  ProjectsMenu->orientation = None;
  ProjectsMenu->havebackground = true;
  ProjectsMenu->padding.up = 300;
  ProjectsMenu->padding.left = 300;
  ProjectsMenu->gap = 40;
  sf::Texture background;
  background.loadFromFile(
      "/home/marwinkas/Desktop/dd.jpg");
  ProjectsMenu->background.setTexture(background);
  
  ProjectsMenu->add(button);
  ProjectsMenu->add(button2);

  button->setCallback([] {
    window2.create(sf::VideoMode(1920, 1080), "Create New Project",
                   sf::Style::Close);
    EngineUI(&window2, window2);
  });

  while (window->isOpen()) {
    window->clear(Theme::windowBgColor);
    // Render menu
    window->draw(menu);

    window->display();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
}

double mousefix = 1;
double mousefix2 = 1;
int main() {
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 0;

  windows.setActive(false);
  window2.setActive(false);
  sf::Thread thread(&renderingThread, &windows);
  thread.launch();

  // Define a callback
  window2.close();
  while (windows.isOpen()) {
    sf::Vector2i cursorPos;

    cursorPos = sf::Mouse::getPosition(windows);
    sf::Event event;
    while (windows.pollEvent(event)) {
      menu.onEvent(event);
      if (event.type == sf::Event::Closed)
        windows.close();
    }
  }

  return 0;
}
