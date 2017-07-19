## Heads Up Display ##

The Engine class provides a HUD component.\n
It is used as a container for HUDElement childs, which can be panels and indicators.\n
To add an element to panel, call the appropriate method on the Engine::hud member.\n

Small example of panel creation with indicator of int

       Engine::hud->addPanel("test_panel01", sf::Vector2f(300, 500), sf::Color::Cyan);
       HUDElement *panel = Engine::hud->getElement("test_panel01");
       int *var = new int(420);
       panel->addElement(new HUDIndicator<int>("var: ", var);


Note: Don't forget to add panel to the update/draw routine !