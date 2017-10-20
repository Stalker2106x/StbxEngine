## Designing GUI Screens (Menus) ##

The GUIScreen class is the starting point of the engine interfaces. It handles layout on screen of menus, sprites, and various GUIElements together.\n
The GUIMenu class is a GUIElement that can be added to GUIScreen, and represents a clickable menu that handle labels, controls/values and their various interactions.\n
It acts as a container for GUIMenuItem elements.\n
Each screen must be loaded from an XML resource file, described in the next section\n

### StbxEngine XML Reference

<table>
  <tr>
    <th>Type</th><th>Option</th><th>XML</th><th>Description</th><th>Default Value</th><th>Accepted Value</th>
  </tr>
  <tr>
    <td colspan="2" rowspan="5">All Elements</td>
    <td>id</td><td>Attribute</td><td>Sets the entity ID</td><td>""</td><td>Any String</td>
  </tr>
  <tr><td>color</td><td>Element</td><td>Sets element color [DEPRECATED]</td><td>#255255255255</td><td>#RRRGGGBBBAAA</td></tr>
  <tr><td>x</td><td>Attribute</td><td>Sets screen horizontal coordinates of Element</td><td>Parent's x value</td><td>Integer</td></tr>
  <tr><td>y</td><td>Attribute</td><td>Sets screen vertical coordinates of Element</td><td>Ordered by parent</td><td>Integer</td></tr>
  <tr><td>padding</td><td>Element</td><td>Sets left offset. [DEPRECATED]</td><td>0</td><td>Integer</td></tr>
  <tr>
    <td colspan="2" rowspan="3">Button</td>
    <td>target</td><td>Attribute</td><td>Set target screen to go to on click</td><td>None</td><td>String (Screen ID)</td>
  </tr>
  <tr><td>action</td><td>Attribute</td><td>Set custom function identifier to call on click</td><td>None</td><td>String (Functor ID)</td></tr>
  <tr><td>command</td><td>Attribute</td><td>Set console command to run on click</td><td>None</td><td>String (Command)</td></tr>
  <tr>
    <td colspan="2" rowspan="1">ButtonBar</td>
    <td>N/A</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Checkbox</td>
    <td>checked</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="2">Edit</td>
    <td>maxLength</td><td>Attribute</td><td>Sets the maximum length of input string</td><td>-1</td><td>Integer (-1 for none)</td>
  </tr>
  <tr><td>geometry</td><td>Attribute</td><td></td><td></td><td></td></tr>
  <tr>
    <td colspan="2" rowspan="1">Panel</td>
    <td>geometry</td><td>Attribute</td><td>Sets x, y, width and height of panel</td><td>0,0,0,0</td><td>X,Y,WIDTH,HEIGHT (Integer)</td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Screen</td>
    <td colspan="5">Screen implements every option of Panel</td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Indicator</td>
    <td>N/A</td><td></td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Text</td>
    <td>text</td><td>Element</td><td>Set text of element</td><td>""</td><td>String</td>
  </tr>
  <tr>
    <td colspan="2" rowspan="2">TextArea</td>
    <td>text</td><td>Element</td><td>Set text of element</td><td>""</td><td>String</td>
  </tr>
  <td>lines</td><td>Element</td><td>Set height (in text "lines") of element</td><td>""</td><td>String</td>
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
