import QtQuick
import QtQuick.Controls
import ThemeColours 0.0
import Resizer 0.0

Button{
	property bool utc: false
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
	property int bgs: 2
	property color bgsc: "#FF00C8"
	property int fgs: 6
	property color fgsc: "#FF00C8"
	property int bghs: 1
	property color bghsc: "#FF00C8"
	property int fghs: 5
	property color fghsc: "#FF00C8"
	property int bgfs: 0
	property color bgfsc: "#FF00C8"
	property int fgfs: 4
	property color fgfsc: "#FF00C8"
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
	property bool sel: false
	
	x: x1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + x0 * Resizer.sizeUnit
	y: y1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + y0 * Resizer.sizeUnit
	width: w1 * (pw1 * Resizer.renderSpaceWidth + pw0 * Resizer.sizeUnit) + w0 * Resizer.sizeUnit
    height: h1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + h0 * Resizer.sizeUnit
	padding: 0
	
	function emitSignal(m){
		if(m == 1){objectName = "click";}
		else if(m == 2){objectName = "press";}
		else if(m == 3){objectName = "release";}
		objectName = "";
	}
	objectName: ""
	onClicked: emitSignal(1)
	onPressed: emitSignal(2)
	onReleased: emitSignal(3)
	
	property bool vh: hovered
	property bool vf: pressed
	
	function getBg(vutc, vvh, vvf, vsel, vbg, vbgc, vbgh, vbghc, vbgf, vbgfc, vbgs, vbgsc, vbghs, vbghsc, vbgfs, vbgfsc){
		if(vsel == false){
			if(vvf == true){
				if(vutc == true){return ThemeColours.getThemeColour(bgf);}
				else{return bgfc;}
			}
			else if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(bgh);}
				else{return bghc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(bg);}
				else{return bgc;}
			}
		}
		else{
			if(vvf == true){
				if(vutc == true){return ThemeColours.getThemeColour(bgfs);}
				else{return bgfsc;}
			}
			else if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(bghs);}
				else{return bghsc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(bgs);}
				else{return bgsc;}
			}
		}
	}
	
	function getFg(vutc, vvh, vvf, vsel, vfg, vfgc, vfgh, vfghc, vfgf, vfgfc, vfgs, vfgsc, vfghs, vfghsc, vfgfs, vfgfsc){
		if(vsel == false){
			if(vvf == true){
				if(vutc == true){return ThemeColours.getThemeColour(fgf);}
				else{return fgfc;}
			}
			else if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(fgh);}
				else{return fghc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(fg);}
				else{return fgc;}
			}
		}
		else{
			if(vvf == true){
				if(vutc == true){return ThemeColours.getThemeColour(fgfs);}
				else{return fgfsc;}
			}
			else if(vvh == true){
				if(vutc == true){return ThemeColours.getThemeColour(fghs);}
				else{return fghsc;}
			}
			else{
				if(vutc == true){return ThemeColours.getThemeColour(fgs);}
				else{return fgsc;}
			}
		}
    }
	
	background: Rectangle{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		color: getBg(utc, vh, vf, sel, bg, bgc, bgh, bghc, bgf, bgfc, bgs, bgsc, bghs, bghsc, bgfs, bgfsc)
        border.width: 0.075 * Resizer.sizeUnit
        border.color: getFg(utc, vh, vf, sel, fg, fgc, fgh, fghc, fgf, fgfc, fgs, fgsc, fghs, fghsc, fgfs, fgfsc)
	}
	
	contentItem: Text{
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		text: s
		font.pixelSize: f1 * (ph1 * Resizer.renderSpaceHeight + ph0 * Resizer.sizeUnit) + f0 * Resizer.sizeUnit
        font.family: f
		horizontalAlignment: ha
		verticalAlignment: va
		color: getFg(utc, vh, vf, sel, fg, fgc, fgh, fghc, fgf, fgfc, fgs, fgsc, fghs, fghsc, fgfs, fgfsc)
		clip: true
		elide: Text.ElideRight
		property bool canParent: true
	}
}
