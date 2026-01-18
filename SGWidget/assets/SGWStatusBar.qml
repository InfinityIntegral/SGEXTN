import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property string s: ""
	
	layer.enabled: true
	x: 0
	y: 0
	width: Resizer.renderSpaceWidth
	height: Resizer.sizeUnit
    property int bg: 3
    property int fg: 0
	
	function getBg(bg){
		return ThemeColours.getThemeColour(bg);
	}
	
	function getFg(fg){
		return ThemeColours.getThemeColour(fg);
	}
	
	color: getBg(bg)
	
	Rectangle{
		x: 0.5 * (parent.width - 0.5 * Resizer.sizeUnit * s.length)
		y: 0
		width: 0.5 * Resizer.sizeUnit * s.length
		height: parent.height
		property bool canParent: true
		color: getBg(bg);
		
		Repeater{
			model: s.length
			Text{
				x: index * 0.5 * Resizer.sizeUnit
				y: 0
				width: Resizer.sizeUnit
				height: Resizer.sizeUnit
				text: s.charAt(index);
				font.pixelSize: Resizer.sizeUnit
				font.family: "SingScript.sg"
				horizontalAlignment: Text.AlignHCenter
				color: getFg(fg)
			}
		}
	}
}
