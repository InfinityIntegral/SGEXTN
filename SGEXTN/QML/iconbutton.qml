import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

Button{
	property int widgetType: 0
	property string fontClass: "SingScript.sg"
	property int bg: 4
	property int fg: 8
	property int bgHover: 3
	property int fgHover: 7
	property int bgPress: 2
	property int fgPress: 6
	property int bgUnselected: 5
	property int fgUnselected: 8
	property int bgUnselectedHover: 4
	property int fgUnselectedHover: 7
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property string s: ""
	property bool unselected: false
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
	width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
	height: w1 * Resizer.renderSpaceHeight + w0 * Resizer.sizeUnit
	property int bgNow: bg
	property int fgNow: fg
	padding: 0
	
	function updateInteraction(){
		if(pressed){
			bgNow = bgPress;
			fgNow = fgPress;
		}
		else if(unselected){
			if(hovered){
				bgNow = bgUnselectedHover;
				fgNow = fgUnselectedHover;
			}
			else{
				bgNow = bgUnselected;
				fgNow = fgUnselected;
			}
		}
		else{
			if(hovered){
				bgNow = bgHover;
				fgNow = fgHover;
			}
			else{
				bgNow = bg;
				fgNow = fg;
			}
		}
	}
	
	onPressedChanged: updateInteraction()
	onHoveredChanged: updateInteraction();
	onUnselectedChanged: updateInteraction();
	
	function emitClickedSignal(){
		if(objectName == "0"){objectName = "1";}
		else{objectName = "0";}
	}
	objectName: "0"
	onClicked: emitClickedSignal()
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: ThemeColours.getThemeColour(bgNow)
	}
	
	contentItem: Text{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		text: s
		font.pixelSize: parent.height
		font.family: fontClass
		horizontalAlignment: Text.AlignHCenter
		color: ThemeColours.getThemeColour(fgNow);
		clip: true
	}
}
