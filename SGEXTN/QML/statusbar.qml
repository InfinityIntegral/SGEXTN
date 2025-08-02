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
	property string s: ""
	property bool notify: false
	
	layer.enabled: true
	x: 0.5 * (Resizer.appWindowWidth - Resizer.renderSpaceWidth)
	y: 0.5 * (Resizer.appWindowHeight - Resizer.renderSpaceHeight)
	width: Resizer.renderSpaceWidth
	height: Resizer.sizeUnit
	property int bgNow: bg
	property int fgNow: fg
	padding: 0
	
	function updateInteraction(){
		if(pressed){
			if(notify == false){
				bgNow = bgPress;
				fgNow = fgPress;
			}
			else{
				bgNow = fgPress;
				fgNow = bgPress;
			}
		}
		else{
			if(hovered){
				if(notify == false){
					bgNow = bgHover;
					fgNow = fgHover;
				}
				else{
					bgNow = fgHover;
					fgNow = bgHover;
				}
			}
			else{
				if(notify == false){
					bgNow = bg;
					fgNow = fg;
				}
				else{
					bgNow = fg;
					fgNow = bg;
				}
			}
		}
	}
	
	onPressedChanged: updateInteraction()
	onHoveredChanged: updateInteraction();
	onNotifyChanged: updateInteraction();
	
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
		elide: Text.ElideRight
	}
}
