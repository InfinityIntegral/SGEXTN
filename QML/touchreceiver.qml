import QtQuick 6.9
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
	
	x: x1 * Resizer.renderSpaceWidth + x0 * Resizer.sizeUnit
	y: y1 * Resizer.renderSpaceHeight + y0 * Resizer.sizeUnit
    width: w1 * Resizer.renderSpaceWidth + w0 * Resizer.sizeUnit
    height: h1 * Resizer.renderSpaceHeight + h0 * Resizer.sizeUnit
    color: ThemeColours.getThemeColour(-1)
	
	property bool e1: false // exists
	property bool e2: false
	property bool e3: false
	property bool e4: false
	property bool e5: false
	
	property int functionPointer1: 0
	property int functionPointer2: 0
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
			}
			else{e1 = false;}
			if(tps.length > 1 && tps[1].pressed == true){
				e2 = true;
			}
			else{e2 = false;}
			if(tps.length > 2 && tps[2].pressed == true){
				e3 = true;
			}
			else{e3 = false;}
			if(tps.length > 3 && tps[3].pressed == true){
				e4 = true;
			}
			else{e4 = false;}
			if(tps.length > 4 && tps[4].pressed == true){
				e5 = true;
			}
			else{e5 = false;}
			emitClickedSignal();
		}
		onTouchUpdated: function(tppm){sendTouch(tppm);}
	}
}
