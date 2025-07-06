import QtQuick 6.9
import QtQuick.Controls 6.9
import ThemeColours 0.0
import Resizer 0.0
import ColourBackground 0.0

Button{
	property int widgetType: 0
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property color c: "black"
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
	width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
	padding: 0
	
	function emitClickedSignal(){
		if(objectName == "0"){objectName = "1";}
		else{objectName = "0";}
	}
	objectName: "0"
	onClicked: emitClickedSignal()
	
	background: ColourBackground{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		
		Rectangle{
			x: 0
			y: 0
			width: parent.width
			height: parent.height
			color: c
		}
	}
}
