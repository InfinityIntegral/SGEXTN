import QtQuick 6.9
import ThemeColours 0.0
import Resizer 0.0

Rectangle{
	property int widgetType: 0
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
    width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
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
	property bool e2: false
	property real e2x: 0.0
	property real e2y: 0.0
	property real e2px: 0.0
	property real e2py: 0.0
	property real e2sx: 0.0
	property real e2sy: 0.0
	property real e2vx: 0.0
	property real e2vy: 0.0
	property real e2rx: 0.0
	property real e2ry: 0.0
	property real e2f: 0.0
	property bool e3: false
	property real e3x: 0.0
	property real e3y: 0.0
	property real e3px: 0.0
	property real e3py: 0.0
	property real e3sx: 0.0
	property real e3sy: 0.0
	property real e3vx: 0.0
	property real e3vy: 0.0
	property real e3rx: 0.0
	property real e3ry: 0.0
	property real e3f: 0.0
	property bool e4: false
	property real e4x: 0.0
	property real e4y: 0.0
	property real e4px: 0.0
	property real e4py: 0.0
	property real e4sx: 0.0
	property real e4sy: 0.0
	property real e4vx: 0.0
	property real e4vy: 0.0
	property real e4rx: 0.0
	property real e4ry: 0.0
	property real e4f: 0.0
	property bool e5: false
	property real e5x: 0.0
	property real e5y: 0.0
	property real e5px: 0.0
	property real e5py: 0.0
	property real e5sx: 0.0
	property real e5sy: 0.0
	property real e5vx: 0.0
	property real e5vy: 0.0
	property real e5rx: 0.0
	property real e5ry: 0.0
	property real e5f: 0.0
	
	property int functionPointer: -1
	property string thisPointer: ""
	function emitClickedSignal(){
		if(state[0] == "0"){state = "1" + thisPointer;}
		else{state = "0" + thisPointer;}
	}
	state: "0"
	
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
			if(tps.length > 1 && tps[1].pressed == true){
				e2 = true;
				e2x = tps[1].x;
				e2y = tps[1].y;
				e2px = tps[1].previousX;
				e2py = tps[1].previousY;
				e2sx = tps[1].startX;
				e2sy = tps[1].startY;
				e2vx = tps[1].velocity.x;
				e2vy = tps[1].velocity.y;
				e2rx = tps[1].ellipseDiameters.width;
				e2ry = tps[1].ellipseDiameters.height;
				e2f = tps[1].pressure;
			}
			else{e2 = false;}
			if(tps.length > 2 && tps[2].pressed == true){
				e3 = true;
				e3x = tps[2].x;
				e3y = tps[2].y;
				e3px = tps[2].previousX;
				e3py = tps[2].previousY;
				e3sx = tps[2].startX;
				e3sy = tps[2].startY;
				e3vx = tps[2].velocity.x;
				e3vy = tps[2].velocity.y;
				e3rx = tps[2].ellipseDiameters.width;
				e3ry = tps[2].ellipseDiameters.height;
				e3f = tps[2].pressure;
			}
			else{e3 = false;}
			if(tps.length > 3 && tps[3].pressed == true){
				e4 = true;
				e4x = tps[3].x;
				e4y = tps[3].y;
				e4px = tps[3].previousX;
				e4py = tps[3].previousY;
				e4sx = tps[3].startX;
				e4sy = tps[3].startY;
				e4vx = tps[3].velocity.x;
				e4vy = tps[3].velocity.y;
				e4rx = tps[3].ellipseDiameters.width;
				e4ry = tps[3].ellipseDiameters.height;
				e4f = tps[3].pressure;
			}
			else{e4 = false;}
			if(tps.length > 4 && tps[4].pressed == true){
				e5 = true;
				e5x = tps[4].x;
				e5y = tps[4].y;
				e5px = tps[4].previousX;
				e5py = tps[4].previousY;
				e5sx = tps[4].startX;
				e5sy = tps[4].startY;
				e5vx = tps[4].velocity.x;
				e5vy = tps[4].velocity.y;
				e5rx = tps[4].ellipseDiameters.width;
				e5ry = tps[4].ellipseDiameters.height;
				e5f = tps[4].pressure;
			}
			else{e5 = false;}
			emitClickedSignal();
		}
		onTouchUpdated: function(tppm){sendTouch(tppm);}
	}
}
