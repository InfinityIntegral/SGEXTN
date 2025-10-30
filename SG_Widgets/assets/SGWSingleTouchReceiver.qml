import QtQuick
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
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
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
    width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
    height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	color: ThemeColours.getThemeColour(-1)
	
	property bool e1: false // exists
	property real e1x: 0.0 // x coordinate
	property real e1y: 0.0 // y coordinate
	property real e1px: 0.0 // previous x
	property real e1py: 0.0 // previous y
	property real e1sx: 0.0 // start x
	property real e1sy: 0.0 // start y
	property real e1vx: 0.0 // velocity x
	property real e1vy: 0.0 // velocity y
	property real e1rx: 0.0 // radius x
	property real e1ry: 0.0 // radius y
	property real e1f: 0.0 // force
	property bool canParent: true
	
	function emitClickedSignal(){
		objectName = "touched"
		objectName = "";
	}
	objectName: ""
	
	MultiPointTouchArea{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		
		function sendTouch(tps){
			if(tps.length > 0 && tps[0].pressed == true){
				e1 = true;
				e1x = tps[0].x;
				e1y = tps[0].y;
				e1px = tps[0].previousX;
				e1py = tps[0].previousY;
				e1sx = tps[0].startX;
				e1sy = tps[0].startY;
				e1vx = tps[0].velocity.x;
				e1vy = tps[0].velocity.y;
				e1rx = tps[0].ellipseDiameters.width;
				e1ry = tps[0].ellipseDiameters.height;
				e1f = tps[0].pressure;
			}
			else{e1 = false;}
			parent.forceActiveFocus();
			emitClickedSignal();
		}
		onTouchUpdated: function(tppm){sendTouch(tppm);}
	}
}
