## Working with GUI ##

The GUI module provides all kind of drawable on screen elements, used for in-game HUD, menus, interaction panels, inventory...\n
Every supported Item is described in the next section XML reference.\n
The GUI module is accessible through the Engine class, which has a public pointer to it
	stb::Engine::instance->gui //or accessible via a single "gui" in your inherited Engine.
It uses "screens" mechanism, which consists of XML Layouts: Each screen in defined inside an XML file (a single file may be used to store all screens) linked between themselves via interaction with buttons, or others GUIElements.\n
You can easily change to a screen by calling the gui method:
	stb::Engine::instance->gui->changeScreen("ScreenID");
where ScreenID is the corresponding ID set inside the XML file.\n
NOTE: If the file storing the menu has a different name than ScreenID, you must add its name as second argument to changeScreen method as follows\n
	stb::Engine::instance->gui->changeScreen("ScreenID", "ScreenFile");

## Designing GUI Screens ##

Following what you have read in the last section, you may want to create your own screens as of now.\n
To do so, create any XML file in your binary file tree, and open it with your favourite editor.\n
First of all, you want to define the screen.\n
	<screen id="main">
	</screen>
This screen is already loadable into the GUI module, but first, lets add some background image, of name "lucky"\n
	<screen id="main" background="lucky">
	</screen>
Now, understand that we added a background but we could have added any option supported in the  next section table at the corresponding container and type.\n
We will for example add a basic menu inside our "main" screen.\n
	<screen id="main" background="lucky">
		<text text="title" font="default" />
		<pair>
			<text text="name:" font="default" />
			<edit width="100px" />
		</pair>
		<button text="ok" font="default" />
	</screen>
Now if we load this menu, we can hopefully input text in the edit, and click button, but nothing is usable as is. We have to link button to action, and give some id to elements we want to extract data later on.

### StbxEngine XML Reference

<table>
  <tr>
    <th colspan="2">Type</th><th>Option</th><th>XML</th><th>Description</th><th>Default Value</th><th>Accepted Value</th>
  </tr>
  <tr>
    <td colspan="2" rowspan="4">GUIElement (any)</td>
    <td>id</td><td>Attribute</td><td>Sets the entity ID</td><td>""</td><td>Any String</td>
  </tr>
  <tr><td>color</td><td>Element</td><td>Sets element color [DEPRECATED]</td><td>#255255255255</td><td>#RRRGGGBBBAAA</td></tr>
  <tr><td>x</td><td>Attribute</td><td>Sets screen horizontal coordinates of Element</td><td>Parent's x value</td><td>Integer</td></tr>
  <tr><td>y</td><td>Attribute</td><td>Sets screen vertical coordinates of Element</td><td>Ordered by parent</td><td>Integer</td></tr>
  <tr>
    <td colspan="2" rowspan="3">button</td>
    <td>target</td><td>Attribute</td><td>Set target screen to go to on click</td><td>None</td><td>String (Screen ID)</td>
  </tr>
  <tr><td>action</td><td>Attribute</td><td>Set custom function identifier to call on click</td><td>None</td><td>String (Functor ID)</td></tr>
  <tr><td>command</td><td>Attribute</td><td>Set console command to run on click</td><td>None</td><td>String (Command)</td></tr>
  <tr>
    <td colspan="2" rowspan="1">toggleButton</td>
    <td>N/A</td><td></td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">settingButton</td>
    <td>value</td><td>Element</td><td>Push value in Button list (First in)</td><td>None</td><td>String (Value)</td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">buttonBar</td>
    <td>N/A</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">checkbox</td>
    <td>checked</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="2">edit</td>
    <td>maxLength</td><td>Attribute</td><td>Sets the maximum length of input string</td><td>-1</td><td>Integer (-1 for none)</td>
  </tr>
  <tr><td>geometry</td><td>Attribute</td><td>Sets x, y, width and height of edit</td><td>0,0,0,0</td><td>X,Y,WIDTH,HEIGHT (Integer)</td></tr>
  <tr>
    <td colspan="2" rowspan="2">pair</td>
    <td>GUIElement</td><td>Element</td><td>Push element in pair (First in)</td><td></td><td>GUIElement (any)</td>
  </tr>
  <tr><td>spacing</td><td>Attribute</td><td>Sets horizontal spacing in pixels between elements of pair</td><td>0</td><td>Integer</td></tr>
  <tr>
    <td colspan="2" rowspan="2">panel</td>
    <td>GUIElement</td><td>Element</td><td>Push element in pair (First in)</td><td></td><td>GUIElement (any)</td>
  </tr>
  <tr><td>geometry</td><td>Attribute</td><td>Sets x, y, width and height of panel</td><td>0,0,0,0</td><td>X,Y,WIDTH,HEIGHT (Integer)</td></tr>
  <tr>
    <td colspan="2" rowspan="1">screen</td>
    <td colspan="5">Screen implements every option of Panel</td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">indicator</td>
    <td>N/A</td><td></td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="2">text</td>
    <td>text</td><td>Attribute</td><td>Set text of element</td><td>""</td><td>String</td>
  </tr>
  <tr><td>font</td><td>Attribute</td><td>Set font of element text</td><td>Default</td><td>Font ID (String)</td></tr>
  <tr>
    <td colspan="2" rowspan="2">textArea</td>
    <td>text</td><td>Attribute</td><td>Set text of element</td><td>""</td><td>String</td>
  </tr>
  <tr><td>lines</td><td>Attribute</td><td>Set height (in text "lines") of element</td><td>""</td><td>String</td></tr>
</table>

### Create your XML screen

To instanciate a GUIScreen in your project, you have to create a valid XML resource to load it from.\n

Here is a valid example screen.xml

        <screen id="main">    <!-- We declare a screen with id "main" -->
          <background>background</background>     <!-- We define the screen background -->
          <menu>              <!-- We add a menu to the screen to hold all of our controls -->
            <spacing>30</spacing>
            <fontsize>16</fontsize>
            <item type="Link" target="yebakg" location="./Data/screen/opt.xml">
              <label>Link</label>
            </item>
            <item type="Setting">
              <label>Refresh Rate</label>
              <padding>150</padding>
              <setting>50Hz</setting>
              <setting>60Hz</setting>
            </item>
            <item type="DynamicSetting" filler="Resolutions" y="400">
              <label>Resolution</label>
            </item>s
            <item type="Edit">
              <label>Pseudo</label>
              <padding>125</padding>
              <inputlength>200</inputlength>
              <inputcolor>#050050255</inputcolor>
            </item>
            <item type="Slider">
              <label>Volume</label>
              <padding>100</padding>
              <barwidth>250</barwidth>
              <min>0</min>
              <max>100</max>
            </item>
            <item type="Checkbox">
              <label>Checkbox</label>
            </item>
            <item type="Link" command="exit">
              <label>Quit</label>
              <color>#255255255</color>
            </item>
          </menu>
        </screen>

### Load your menu

To load a menu, just call the function Menu::loadFromFile(const std::string &file)

      Menu menu();

      menu.loadFromFile("./Data/menu/menu.xml");
