import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0
import SingCorrect 0.0

TextField{
	property bool utc: true
	property int bg: 4
	property color bgc: "#FF00C8"
	property int fg: 8
	property color fgc: "#FF00C8"
	property int bgh: 3
	property color bghc: "#FF00C8"
	property int fgh: 7
	property color fghc: "#FF00C8"
	property int bgf: 2
	property color bgfc: "#FF00C8"
	property int fgf: 6
	property color fgfc: "#FF00C8"
	property int bgi: 6
	property color bgic: "#FF00C8"
	property int fgi: 8
	property color fgic: "#FF00C8"
	property int bghi: 5
	property color bghic: "#FF00C8"
	property int fghi: 7
	property color fghic: "#FF00C8"
	property real x1: 0.0
	property real x0: 0.0
	property real y1: 0.0
	property real y0: 0.0
	property real w1: 0.0
	property real w0: 0.0
	property real h1: 0.0
	property real h0: 0.0
	property real f1: 0.0
	property real f0: 0.0
	property real pw1: 0.0
	property real pw0: 0.0
	property real ph1: 0.0
	property real ph0: 0.0
	property string s: ""
	property string f: "SingScript.sg"
	property int ha: 0
	property int va: 0
	property bool inv: false
	property bool vh: hovered
	property bool vf: activeFocus
	property bool canParent: true
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
	width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
    height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	padding: 0
	
	function applySingCorrect(){
		let pos = cursorPosition;
		let newText = SingCorrect.correct(text);
		pos = pos + newText.length - text.length;
		pos = Math.max(0, pos);
		text = newText;
		s = text;
		cursorPosition = Math.min(pos, s.length);
	}
	
	function emitClickedSignal(m){
		if(m == 1){
			applySingCorrect();
			objectName = "textChanged";
		}
		else if(m == 2){
			if(activeFocus == true){objectName = "focusStart";}
			else{objectName = "focusEnd";}
		}
		objectName = "";
	}
	objectName: ""
	onTextChanged: emitClickedSignal(1)
	onActiveFocusChanged: emitClickedSignal(2)
	
	function getBg(vutc, vvh, vvf, vinv, vbg, vbgc, vbgh, vbghc, vbgf, vbgfc, vbgi, vbgic, vbghi, vbghic){
		if(vvf == true){
			if(vutc == true){return ThemeColours.getThemeColour(vbgf);}
			else{return vbgfc;}
		}
		else if(vinv == true){
			if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(vbghi);}
				else{return vbghic;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(vbgi);}
				else{return vbgic;}
			}
		}
		else{
			if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(vbgh);}
				else{return vbghc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(vbg);}
				else{return vbgc;}
			}
		}
	}
	
	function getFg(vutc, vvh, vvf, vinv, vfg, vfgc, vfgh, vfghc, vfgf, vfgfc, vfgi, vfgic, vfghi, vfghic){
		if(vvf == true){
			if(vutc == true){return ThemeColours.getThemeColour(vfgf);}
			else{return vfgfc;}
		}
		else if(vinv == true){
			if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(vfghi);}
				else{return vfghic;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(vfgi);}
				else{return vfgic;}
			}
		}
		else{
			if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(vfgh);}
				else{return vfghc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(vfg);}
				else{return vfgc;}
			}
		}
	}
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: getBg(utc, vh, vf, inv, bg, bgc, bgh, bghc, bgf, bgfc, bgi, bgic, bghi, bghic)
	}
	
	font.pixelSize: f1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + f0 * Resizer.sizeUnit
	font.family: f
	horizontalAlignment: ha
	verticalAlignment: va
	color: getFg(utc, vh, vf, inv, fg, fgc, fgh, fghc, fgf, fgfc, fgi, fgic, fghi, fghic)
	selectionColor: getFg(utc, vh, vf, inv, fg, fgc, fgh, fghc, fgf, fgfc, fgi, fgic, fghi, fghic)
	selectedTextColor: getBg(utc, vh, vf, inv, bg, bgc, bgh, bghc, bgf, bgfc, bgi, bgic, bghi, bghic)
}
