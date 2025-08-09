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
	property real pw1: 0.0
	property real pw0: 0.0
	property real ph1: 0.0
	property real ph0: 0.0
	property color c: "#FF00C8"
	property bool canParent: true
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
	width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
	height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	padding: 0
	
	function emitClickedSignal(){
		objectName = "click";
		objectName = "";
	}
	objectName: ""
	onClicked: emitClickedSignal()
	
	background: ColourBackground{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
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
