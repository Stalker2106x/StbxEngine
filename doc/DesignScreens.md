## Designing GUI Screens (Menus) ##

The GUIScreen class is the starting point of the engine interfaces. It handles layout on screen of menus, sprites, and various GUIElements together.\n
The GUIMenu class is a GUIElement that can be added to GUIScreen, and represents a clickable menu that handle labels, controls/values and their various interactions.\n
It acts as a container for GUIMenuItem elements.\n
Each screen must be loaded from an XML resource file, described in the next section\n

### StbxEngine XML Reference

<table>
  <tr>
    <th>Style</th><th>Type</th><th>Option</th><th>XML</th><th>Description</th><th>Default Value</th><th>Accepted Value</th>
  </tr>
  <tr>
    <td colspan="2" rowspan="6">All Elements</td>
    <td>id</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr><td>label</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>color</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>x</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>y</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>padding</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr>
    <td colspan="2" rowspan="3">Button</td>
    <td>target</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr><td>action</td><td>Attribute</td><td></td><td></td><td></td></tr>
  <tr><td>command</td><td>Attribute</td><td></td><td></td><td></td></tr>
  <tr>
    <td colspan="2" rowspan="1">ButtonBar</td>
    <td>id</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Checkbox</td>
    <td>checked</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Edit</td>
    <td>maxLength</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr><td>width</td><td>Attribute</td><td></td><td></td><td></td>
  <tr>
    <td colspan="2" rowspan="1">Panel</td>
    <td>geometry</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Screen</td>
    <td>geometry</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Indicator</td>
    <td>reference</td><td>Node</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">Text</td>
    <td>text</td><td>Node</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td colspan="2" rowspan="1">TextArea</td>
    <td>N/A</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
</table>

<table>
  <tr>
    <th>Style</th><th>Type</th><th>Option</th><th>XML</th><th>Description</th><th>Default Value</th><th>Accepted Value</th>
  </tr>
  <tr>
    <td colspan="2" rowspan="6">All Items</td>
    <td>id</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr><td>label</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>color</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>x</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>y</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>padding</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr>
    <td colspan="2" rowspan="3">Menu</td>
    <td>fontsize</td><td>Element</td><td></td><td></td><td></td>
  </tr>
  <tr><td>background</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr><td>spacing</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr>
    <td rowspan="3"></td><td rowspan="3">Link</td>
    <td>target</td><td>Attribute</td><td></td><td></td><td></td>
  </tr>
  <tr><td>action</td><td>Attribute</td><td></td><td></td><td></td></tr>
  <tr><td>command</td><td>Attribute</td><td></td><td></td><td></td></tr>
  <tr>
    <td rowspan="1"></td><td rowspan="1">Setting</td>
    <td>Setting</td><td>Element</td><td></td><td></td><td></td>
  </tr>
  <tr>
    <td rowspan="1"></td><td rowspan="1">DynamicSetting</td>
    <td colspan="5"> DynamicSetting implements every parameter of Setting.</td>
  </tr>
  <tr>
    <td rowspan="2"></td><td rowspan="2">Edit</td>
    <td>inputlength</td><td>Element</td><td></td><td></td><td></td>
  </tr>
  <tr><td>inputcolor</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr>
    <td rowspan="2"></td><td rowspan="2">Slider</td>
    <td>min</td><td>Element</td><td></td><td></td><td></td>
  </tr>
  <tr><td>max</td><td>Element</td><td></td><td></td><td></td></tr>
  <tr>
    <td rowspan="1"></td><td rowspan="1">Checkbox</td><td colspan="5"></td>
    <!--<td>min</td><td>Element</td><td></td><td></td><td></td>-->
  </tr>
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
            </item>
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
