## Designing Menus ##

The menu system is handled by the Menu class that acts as a container for MenuItem elements.\n
Each Menu must be loaded from an XML resource file, described in the next section\n

### Create your XML menu

To instanciate a menu in your project, you have to create a valid XML resource to build it from.\n

Here is a valid example menu.xml
     <?xml version="1.0" encoding="UTF-8"?>
     <menu>
          <title>Test Menu</title>
     	  <background>background</background>
	  <spacing>30</spacing>
	  <fontsize>16</fontsize>
	  <item type="Link" target="opt">
	       <label>Link</label>
	  </item>
	  <item type="Setting">
	       <label>Refresh Rate</label>
	       <padding>150</padding>
	       <setting>50Hz</setting>
	       <setting>60Hz</setting>
	  </item>
	  <item type="DynamicSetting" filler="Resolutions">
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
     		<min>0</min>
     		<max>100</max>
     	  </item>
	  <item type="Link">
	       <label>Quit</label>
	       <color>#255255255</color>
	  </item>
     </menu>

### Load your menu

To load a menu, just call the function Menu::loadFromFile(const std::string &file)

   Menu menu();

   menu.loadFromFile("./Data/menu/menu.xml");

