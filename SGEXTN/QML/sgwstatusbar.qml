import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

Button{
	property string s: ""
	property bool notify: false
	
	layer.enabled: true
	x: 0.5 * (Resizer.appWindowWidth - Resizer.renderSpaceWidth)
	y: 0.5 * (Resizer.appWindowHeight - Resizer.renderSpaceHeight)
	width: Resizer.renderSpaceWidth
	height: Resizer.sizeUnit
	property int bgNow: 4
	property int fgNow: 8
	padding: 0
	
	function updateInteraction(){
		if(pressed){
			if(notify == false){
				bgNow = 2;
				fgNow = 6;
			}
			else{
				bgNow = 6;
				fgNow = 2;
			}
		}
		else{
			if(hovered){
				if(notify == false){
					bgNow = 3;
					fgNow = 7;
				}
				else{
					bgNow = 7;
					fgNow = 3;
				}
			}
			else{
				if(notify == false){
					bgNow = 4;
					fgNow = 8;
				}
				else{
					bgNow = 8;
					fgNow = 4;
				}
			}
		}
	}
	
	onPressedChanged: updateInteraction()
	onHoveredChanged: updateInteraction();
	onNotifyChanged: updateInteraction();
	
	function emitClickedSignal(){
		objectName = "clicked";
		objectName = "";
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
		font.family: "SingScript.sg"
		horizontalAlignment: Text.AlignHCenter
		color: ThemeColours.getThemeColour(fgNow);
		clip: true
		elide: Text.ElideRight
		property bool canParent: true
	}
}
