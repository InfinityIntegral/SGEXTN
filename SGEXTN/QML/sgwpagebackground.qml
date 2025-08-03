import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int bg: -1
	property color bgc: "#FF00C8"
	property bool utc: true
	property bool canParent: true
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
	
	function getBg(vutc, vbg, vbgc){
		if(vutc){return ThemeColours.getThemeColour(vbg);}
		else{return vbgc;}
	}
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
    width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
    height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
    color: getBg(utc, bg, bgc)
	
	MultiPointTouchArea{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
	}
	MouseArea{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		hoverEnabled: true
	}
}
