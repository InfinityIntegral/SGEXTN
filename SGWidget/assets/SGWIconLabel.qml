import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property bool utc: true
	property int bg: 8
	property color bgc: "#FF00C8"
	property int fg: 4
	property color fgc: "#FF00C8"
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property real pw1: 0.0
	property real pw0: 0.0
	property real ph1: 0.0
	property real ph0: 0.0
	property real f1: 0.0
	property real f0: 0.0
	property string s: ""
	property string f: "AppIcons.sg"
	property int ha: 0
	property int va: 0
	
	function getBg(vutc, vbg, vbgc){
		if(vutc == true){return ThemeColours.getThemeColour(vbg);}
		else{return vbgc;}
	}
	
	function getFg(vutc, vfg, vfgc){
		if(vutc == true){return ThemeColours.getThemeColour(vfg);}
		else{return vfgc;}
	}
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
    width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
    height: h1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
    color: getBg(utc, bg, bgc)
	
	Text{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		text: s
		font.pixelSize: f1 * (ph1 * Resizer.renderSpaceWidth + ph0 * Resizer.sizeUnit) + f0 * Resizer.sizeUnit
		font.family: f
		horizontalAlignment: ha
		verticalAlignment: va
		color: getFg(utc, fg, fgc)
		clip: true
		elide: Text.ElideRight
		property bool canParent: true
	}
}
