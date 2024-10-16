subdir('libs')
subdir('UI')
executable(
  'source',
  'main.cpp',
  install : false,
  include_directories : all_includes,
  dependencies : all_deps,
  link_with: [EngineUI_lib,UI_lib,Logic_lib,FormLayout_lib,Layout_lib,Arrow_lib,Box_lib,Cross_lib,Button_lib,CheckBox_lib,Image_lib,Label_lib,Menu_lib,ProgressBar_lib,Slider_lib,SpriteButton_lib,TextBox_lib,Theme_lib,Widget_lib]
)