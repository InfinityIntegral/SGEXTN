import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0
import ColourBackground 0.0

Button{
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property real e1: 0.0
	property real e0: 0.0
	property real pw1: 0.0
	property real pw0: 0.0
	property real ph1: 0.0
	property real ph0: 0.0
	property color c: "#FF00C8"
	property bool canParent: true
	property bool utc: true
	property int bg: 4
	property color bgc: "#FF00C8"
	property int bgh: 3
	property color bghc: "#FF00C8"
	property int bgf: 2
	property color bgfc: "#FF00C8"
	property bool vh: hovered
	property bool vf: pressed
	
	function getBg(vutc, vvh, vvf, vbg, vbgc, vbgh, vbghc, vbgf, vbgfc){
		if(vvf == true){
			if(vutc == true){return ThemeColours.getThemeColour(vbgf);}
			else{return vbgfc;}
		}
		else if(vvh == true){
			if(vutc == true){return ThemeColours.getThemeColour(vbgh);}
			else{return vbghc;}
		}
		else{
			if(vutc == true){return ThemeColours.getThemeColour(vbg);}
			else{return vbgc;}
		}
	}
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
	width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
	height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	padding: 0
	
	function emitClickedSignal(m){
		if(m == 1){objectName = "click";}
		else if(m == 2){objectName = "done";}
		objectName = "";
	}
	objectName: ""
	onClicked: emitClickedSignal(1)
	onCChanged: emitClickedSignal(2)
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: getBg(utc, vh, vf, bg, bgc, bgh, bghc, bgf, bgfc)
		
		ColourBackground{
			x: e1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + e0 * Resizer.sizeUnit
			y: e1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + e0 * Resizer.sizeUnit
			width: parent.width - 2.0 * (e1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + e0 * Resizer.sizeUnit)
			height: parent.height - 2.0 * (e1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + e0 * Resizer.sizeUnit)
			layer.enabled: true
		
			Rectangle{
				x: 0
				y: 0
				width: parent.width
				height: parent.height
				color: c
			}
		}
	}
}
