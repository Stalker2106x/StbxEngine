## Heads Up Display ##

The Engine class provides a HUD component.\n
It is used as a container for HUDElement childs, which can be HUDPanel, HUDDraggablePanel and HUDIndicator.\n
To add an element to panel, call the appropriate method on the Engine::hud member.\n

Small example of panel creation with indicator of integer value

       HUDElement *panelHandle = Engine::hud->addPanel("test_panel01", sf::Vector2f(300, 500), sf::Color::Cyan); //We add the panel to HUD and grab handle
       
       int *var = new int(420); //we declare an integer
       panel->addElement(new HUDIndicator<int>("var: ", var); //We attach a new indicator to the variable with label "var: "
       *var += 5; //Change the int value, the panel should update instantly!