import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

Button{
	property string s: ""
	
	layer.enabled: true
	x: 0
	y: 0
	width: Resizer.renderSpaceWidth
	height: Resizer.sizeUnit
	property int bg: 4
	property int fg: 8
	property int bgh: 3
	property int fgh: 7
	property int bgf: 2
	property int fgf: 6
	property bool vh: hovered
	property bool vf: pressed
	padding: 0
	
	function getBg(vvh, vvf, bg, bgh, bgf){
		if(vvf == true){return ThemeColours.getThemeColour(bgf);}
		else if(vvh == true){return ThemeColours.getThemeColour(bgh);}
		else{return ThemeColours.getThemeColour(bg);}
	}
	
	function getFg(vvh, vvf, fg, fgh, fgf){
		if(vvf == true){return ThemeColours.getThemeColour(fgf);}
		else if(vvh == true){return ThemeColours.getThemeColour(fgh);}
		else{return ThemeColours.getThemeColour(fg);}
	}
	
	function emitClickedSignal(){
		objectName = "clicked";
		objectName = "";
	}
	objectName: ""
	onClicked: emitClickedSignal()
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: getBg(vh, vf, bg, bgh, bgf)
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
		color: getFg(vh, vf, fg, fgh, fgf)
		clip: true
		elide: Text.ElideRight
		property bool canParent: true
	}
}
