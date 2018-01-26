## Your first engine ##

The StbxEngine library resides on a simple yet powerful concept: the "Engine" ecosystem.\n
The base class of the project is the stb::Engine class, which you should inherit from, and\n
implement update/draw logic from your game. Basically, most of StbxEngine component act as\n
Extendable interfaces that you inherit from, or feed with functors.\n

### Hello World! ###

    class MyGame : public stb::Engine //Inherit from StbxEngine class
    {
    public:
	    MyGame()
      {
        init(); //Call init to start Engine and window
        tgui::Label::Ptr lHello = tgui::Label::Create("Hello World!"); //Thanks to tgui, displaying some text has never been so easy.
        lHello->setPosition(_winWidth / 2, _winHeight / 2); //Set the label in the center of screen.
        gui->add(lHello); //Add the label to the gui, that's it.
      }

	    bool update(const sf::Event &e)
      {
        //Your game logic goes here
      }

	    void draw(sf::RenderWindow &win)
      {
        //Render your game here
      }
    };

    int main(int argc, char **argv)
    {
      MyGame game; //Instanciate your game

      if (argc > 0)
        engine.handleArgs(argc, argv); //If arguments present, handle them (Note: you can call handleArgs without testing.)
      engine.mainLoop(); //Start the game loop.
      return (0);
    }

With this architecture, every aspect of the game has its container:\n
Please note: EVERY Drawable class you write should implement this update/draw logic\n
The draw function should only draw, and therefore should be const passive to its owner.\n
The update method is called BEFORE each frame is drawn on screen; the draw method is called when everything has updated.\n

### Adding network capabilities ###

Now that you played around with the window, you probably wonder: "How will my players connect together into a game ?"\n
Well, that can be done as easy as a few lines of code. Following the last example, let's add a stb::NetworkManager component to our engine.

    class MyGame : public stb::Engine //Inherit from StbxEngine class
    {
    public:
	    MyGame();

	    bool update(const sf::Event &e);
	    void draw(sf::RenderWindow &win);
    private:
      stb::NetworkManager _network;
    };

The stb::NetworkManager component encapsulate both server and client. It can start any of the two at anytime asynchronously from main thread.\n
You can hopefully close server, disconnect client, or abort when undesired behaviour happens without crashing your game.
Let's start a simple server and connect to it. First of all, you have to define your Client and Server classes, because, they should behave as YOU intend to;\n
We are in a game, after all ! That implies inheriting from stb::Client and stb::Server and implementing the following virtual functions respectively:

#### Server ####

		//Overload feature
		virtual void loop() = 0; //What should the server do ?
		virtual void setClientData(stb::Packet &data) = 0; //How do you manage remote clients ? Where do you store their info ?
		virtual void sendServerData(clientNode &client) = 0; //What kind of data should the server send to client upon connection ?

		//Error handling
		virtual void onClientTimeout() = 0; //When the client takes too much time to answer, what to do ?
		virtual void onNetworkError() = 0; //When the socket is broken, or you cannot establish connection to internet?
		virtual void onBindError() = 0; //When the port used to bind the server to is already used, or blocked ?

#### Client ####
	
		//Overload features
		virtual void receiveServerInfo(Packet &serverInfo) = 0; //What to do with the Server info ?
		virtual void receivePlayer(Packet &playerData) = 0; //Where to store the other players that the server describes ?

		//Error handling
		virtual void onServerFull() = 0; //What if the server is full ?
		virtual void onServerTimeout() = 0; //When the server takes too much time to answer ?
		virtual void onVersionMismatch() = 0; //When you have a different version from server ?
		virtual void onNetworkError() = 0; //When the socket is broken, or you cannot establish connection to internet?
